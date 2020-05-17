/* -*- c++ -*- */
/* 
 * Copyright 2020 Vinicius Barragam.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "cell_demapping_impl.h"

namespace gr {
  namespace drm_receiver {

    cell_demapping::sptr
    cell_demapping::make(size_t ifft_length)
    {
      return gnuradio::get_initial_sptr
        (new cell_demapping_impl(ifft_length));
    }

    /*
     * The private constructor
     */
    cell_demapping_impl::cell_demapping_impl(size_t ifft_length)
      : gr::block("cell_demapping",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {
      // o tamanho da fft é o número de portadoras
      ninput_cells = ifft_length;
      cell_index = 0;
    }

    /*
     * Our virtual destructor.
     */
    cell_demapping_impl::~cell_demapping_impl()
    {
    }

    void
    cell_demapping_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    /*
     * @brief: Ignora células de time reference.
     *
     * @return:  0, é portadora de time reference
     *          -1, não é portadora de time reference
     *
     * TODO: implementar para todos os modos de robustez
     */
    int
    cell_demapping_impl::check_time_reference_cell (int cell_index, int symbol_index)
    {
      int ret = -1;

      if (!(symbol_index % 15))
      {
        for (int time_ref_row = 0; time_ref_row < 16; time_ref_row++)
        {
          if (cell_index - 1024 / 2 == table_time_reference_cells[time_ref_row])
          {
            ret = 0;
            break;
          }
        }
      }
      return ret;
    }

    /*
     * @brief: Ignora células de FAC.
     *
     * @return:  0, é portadora de FAC
     *          -1, não é portadora de FAC
     *
     * TODO: implementar para todos os modos de robustez
     */
    int
    cell_demapping_impl::check_fac_cell (int cell_index, int symbol_index)
    {
      int ret = -1;

      for (int fac_row = 0; fac_row < 65; fac_row++)
      {
        if ((symbol_index % 15) == table_fac_cells_B[fac_row][0])
        {
          if (cell_index - 1024 / 2 == table_fac_cells_B[fac_row][1])
          {
            ret = 0;
            break;
          }
        }
      }
      return ret;
    }

    /*
     * @brief: Ignora células de referência de frequência.
     *
     * @return:  0, é portadora de frequência
     *          -1, não é portadora de frequência
     *
     * TODO: implementar para todos os modos de robustez
     */
    int
    cell_demapping_impl::check_freq_cell (int cell_index)
    {
      int ret = -1;

      for (int fr_count = 0; fr_count < QT_FREQUENCY_REF_CELLS; fr_count++)
      {
        if (table_fr_cells[1][fr_count] == cell_index - 1024 / 2)
        {
          ret = 0;
          break;
        }
      }
      return ret;
    }

    /*
     * @brief: Checa se uma portadora contém valor de ganho. Ref: Table 93.
     * Os nomes das variáveis são os mesmos que os da norma.
     *
     * @return:  0, é portadora de ganho
     *          -1, não é portadora de ganho
     *
     * TODO: implementar para todos os modos de robustez
     */
    int
    cell_demapping_impl::check_gain_cell (int cell_index, int symbol_index)
    {
      int ret = -1;
      int offset = 103; // offset no modo B
      int cell_offset = cell_index - ninput_cells / 2;
      int k = 0;
      int p = -18;

      do
      {
          k = 1 + 2 * (symbol_index % 3) + 6 * p;
          p++;
      } while (k < cell_offset);

      if (k == cell_offset)
      {
          ret = 0;
      }
      return ret;
    }

    int
    cell_demapping_impl::cell_demapping (int cell_index, int symbol_index)
    {
      int ret = -1;
      int k_off = ninput_cells / 2;
      int ncells = ninput_cells;

      switch (symbol_index)
      {
      // os dois primeiros símbolos alocam SDC e FAC
      case 0:
      case 1:
        break;

      default:
        // ignora células de ganho
        if (!check_gain_cell(cell_index, symbol_index))
        {
          ret = -1;
        }
        // ignora células de frequência
        else if (!check_freq_cell(cell_index))
        {
          ret = -1;
        }
        // ignora células de FAC
        else if (!check_fac_cell(cell_index, symbol_index))
        {
          // TODO: salvar FAC em um vetor
          ret = -1;
        }
        // ignora time reference cells
        else if (!check_time_reference_cell(cell_index, symbol_index))
        {
          ret = -1;
        }
        // ignora termo DC
        else if (cell_index == ncells / 2 || cell_index % (ncells / 2) == 0)
        {
          ret = -1;
        }
        // ignora termos não utilizados na última portadora
        else if (symbol_index == LAST_SYMBOL_SUPERFRAME && (cell_index == 614 || cell_index == 615))
        {
          ret = -1;
        }
        else
        {
          ret = 0;
        }
      }
      return ret;
    }

    int
    cell_demapping_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];
      static int symbol_index = 0; // indexa o símbolo atual do super frame
      int nconsumed_items = 0;
      int nreturned_items = 0;

      // Do <+signal processing+>
      for (int out_count = 0; out_count < noutput_items; out_count++)
      {
        if (cell_index >= (ninput_cells / 2) - 103 && cell_index <= (ninput_cells / 2) + 103)
        {
          if (!cell_demapping(cell_index, symbol_index))
          {
            out[nreturned_items] = in[cell_index + (out_count / ninput_cells) * ninput_cells];
            nreturned_items++;
          }
        }

        if (++cell_index >= ninput_cells)
        {
            cell_index = 0;
            if (++symbol_index == 45)
                symbol_index = 0;
        }

        nconsumed_items++;
      }

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (nconsumed_items);

      // Tell runtime system how many output items we produced.
      return nreturned_items;
    }

  } /* namespace drm_receiver */
} /* namespace gr */

