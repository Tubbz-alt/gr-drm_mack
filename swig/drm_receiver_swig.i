/* -*- c++ -*- */

#define DRM_RECEIVER_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "drm_receiver_swig_doc.i"

%{
#include "drm_receiver/cell_demapping.h"
%}


%include "drm_receiver/cell_demapping.h"
GR_SWIG_BLOCK_MAGIC2(drm_receiver, cell_demapping);
