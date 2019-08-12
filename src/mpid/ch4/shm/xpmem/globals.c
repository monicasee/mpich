/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/*
 *  (C) 2006 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 *
 *  Portions of this code were written by Intel Corporation.
 *  Copyright (C) 2011-2017 Intel Corporation.  Intel provides this material
 *  to Argonne National Laboratory subject to Software Grant and Corporate
 *  Contributor License Agreement dated February 8, 2012.
 */

#include "mpidimpl.h"
#include "xpmem_pre.h"
#include "xpmem_impl.h"

MPIDI_XPMEM_global_t MPIDI_XPMEM_global = { 0 };

/* Preallocated segment objects */
MPIDI_XPMEM_seg_t MPIDI_XPMEM_seg_mem_direct[MPIDI_XPMEM_SEG_PREALLOC] = { {0}
};

MPIR_Object_alloc_t MPIDI_XPMEM_seg_mem = { 0, 0, 0, 0, MPIR_XPMEM_SEG,
    sizeof(MPIDI_XPMEM_seg_t), MPIDI_XPMEM_seg_mem_direct,
    MPIDI_XPMEM_SEG_PREALLOC
};