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


#ifndef INCLUDED_DRM_RECEIVER_ZERO_UNPAD_H
#define INCLUDED_DRM_RECEIVER_ZERO_UNPAD_H

#include <drm_receiver/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace drm_receiver {

    /*!
     * \brief <+description of block+>
     * \ingroup drm_receiver
     *
     */
    class DRM_RECEIVER_API zero_unpad : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<zero_unpad> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of drm_receiver::zero_unpad.
       *
       * To avoid accidental use of raw pointers, drm_receiver::zero_unpad's
       * constructor is in a private implementation
       * class. drm_receiver::zero_unpad::make is the public interface for
       * creating new instances.
       */
      static sptr make(size_t nfft, size_t vector_len);
    };

  } // namespace drm_receiver
} // namespace gr

#endif /* INCLUDED_DRM_RECEIVER_ZERO_UNPAD_H */

