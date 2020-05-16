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

#ifndef INCLUDED_DRM_RECEIVER_CELL_DEMAPPING_IMPL_H
#define INCLUDED_DRM_RECEIVER_CELL_DEMAPPING_IMPL_H

#include <drm_receiver/cell_demapping.h>

#define QT_FREQUENCY_REF_CELLS    3
#define QT_FAC_CELLS_B            6
#define LAST_SYMBOL_SUPERFRAME    44

namespace gr {
  namespace drm_receiver {

    class cell_demapping_impl : public cell_demapping
    {
     private:
      // Nothing to declare in this block.

     public:
      cell_demapping_impl(size_t ncells, size_t nsymbols);
      ~cell_demapping_impl();

      int ninput_cells, ninput_symbols;
      int cell_index, symbol_index;
      int table_fr_cells[4][QT_FREQUENCY_REF_CELLS] = 
      {
        {18, 54, 72},
        {16, 48, 64},
        {11, 33, 44},
        { 7, 21, 28}
      }; // portadoras que contém frequência. Table 86
      int table_time_reference_cells[16] = 
      {
        // modo A: (TODO mudar a estrutura de dados)
        //{17, 19, 21, 28, 29, 32, 33, 39, 40, 41, 53, 55, 56, 60, 61, 63, 71, 73},
        14, 18, 20, 24, 26, 32, 36, 42, 44, 49, 50, 54, 56, 62, 66, 68,
      };
      int table_fac_cells_B[65][2] = 
      {
        { 2,13}, { 2,25}, { 2,43}, { 2,55}, { 2,67},          //  2
        { 3,15}, { 3,27}, { 3,45}, { 3,57}, { 3,69},          //  3
        { 4,17}, { 4,29}, { 4,47}, { 4,59}, { 4,71},          //  4
        { 5,19}, { 5,31}, { 5,49}, { 5,61}, { 5,73},          //  5
        { 6, 9}, { 6,21}, { 6,33}, { 6,51}, { 6,63}, { 6,75}, //  6
        { 7,11}, { 7,23}, { 7,35}, { 7,53}, { 7,65}, { 7,77}, //  7
        { 8,13}, { 8,25}, { 8,37}, { 8,55}, { 8,67}, { 8,79}, //  8
        { 9,15}, { 9,27}, { 9,39}, { 9,57}, { 9,69}, { 9,81}, //  9
        {10,17}, {10,29}, {10,41}, {10,59}, {10,71}, {10,83}, // 10
        {11,19}, {11,31}, {11,43}, {11,61}, {11,73},          // 11
        {12,21}, {12,33}, {12,45}, {12,63}, {12,75},          // 12
        {13,23}, {13,35}, {13,47}, {13,65}, {13,77}           // 13
      }; // portadoras que contém FAC no modo B. Table 98

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);
      int get_current_cell (void);
      void set_current_cell (int arg);
      int get_current_symbol (void);
      void set_current_symbol (int arg);
      int check_time_reference_cell(int cell_index, int symbol_index);
      int check_fac_cell (int cell_index, int symbol_index);
      int check_freq_cell (int cell_index);
      int check_gain_cell (int cell_index, int symbol_index);
      int cell_demapping(int cell_index, int symbol_index);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace drm_receiver
} // namespace gr

#endif /* INCLUDED_DRM_RECEIVER_CELL_DEMAPPING_IMPL_H */
