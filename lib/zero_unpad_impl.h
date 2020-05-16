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

#ifndef INCLUDED_DRM_RECEIVER_ZERO_UNPAD_IMPL_H
#define INCLUDED_DRM_RECEIVER_ZERO_UNPAD_IMPL_H

#include <drm_receiver/zero_unpad.h>

namespace gr {
namespace drm_receiver {

class zero_unpad_impl : public zero_unpad
{
private:
	// Nothing to declare in this block.

public:
	zero_unpad_impl(size_t nfft, size_t vector_len);
	~zero_unpad_impl();
	int input_length, output_length;

	// Where all the action really happens
	void forecast (int noutput_items, gr_vector_int &ninput_items_required);
	void zero_unpad (const gr_complex *in, gr_complex *out);

	int general_work(int noutput_items,
			gr_vector_int &ninput_items,
			gr_vector_const_void_star &input_items,
			gr_vector_void_star &output_items);
};

} // namespace drm_receiver
} // namespace gr

#endif /* INCLUDED_DRM_RECEIVER_ZERO_UNPAD_IMPL_H */

