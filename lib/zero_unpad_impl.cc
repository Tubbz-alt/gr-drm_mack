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
#include "zero_unpad_impl.h"

namespace gr {
namespace drm_receiver {

zero_unpad::sptr
zero_unpad::make(size_t nfft, size_t vector_len)
{
	return gnuradio::get_initial_sptr
			(new zero_unpad_impl(nfft, vector_len));
}

/*
 * The private constructor
 */
zero_unpad_impl::zero_unpad_impl(size_t nfft, size_t vector_len)
: gr::block("zero_unpad",
		gr::io_signature::make(1, 1, sizeof(gr_complex) * nfft),
		gr::io_signature::make(1, 1, sizeof(gr_complex) * vector_len))
{
	input_length = nfft;
	output_length = vector_len;
}

/*
 * Our virtual destructor.
 */
zero_unpad_impl::~zero_unpad_impl()
{
}

void
zero_unpad_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
{
	ninput_items_required[0] = noutput_items;
}

void
zero_unpad_impl::zero_unpad (const gr_complex *in, gr_complex *out)
{
	for (int i = 0, j = 409; j < 616; i++, j++)
	{
		out[i] = in[j];
	}
}

int
zero_unpad_impl::general_work (int noutput_items,
		gr_vector_int &ninput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items)
{
	const gr_complex *in = (const gr_complex *) input_items[0];
	gr_complex *out = (gr_complex *) output_items[0];

	// Do <+signal processing+>
	for (int k = 0; k < noutput_items; k++)
	{
		zero_unpad(in, &*out);

		in += input_length;
		out += output_length;
	}

	// Tell runtime system how many input items we consumed on
	// each input stream.
	consume_each (noutput_items);

	// Tell runtime system how many output items we produced.
	return noutput_items;
}

} /* namespace drm_receiver */
} /* namespace gr */

