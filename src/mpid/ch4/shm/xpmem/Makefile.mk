## -*- Mode: Makefile; -*-
## vim: set ft=automake :
##
## (C) 2016 by Argonne National Laboratory.
##     See COPYRIGHT in top-level directory.
##
##  Portions of this code were written by Intel Corporation.
##  Copyright (C) 2011-2016 Intel Corporation.  Intel provides this material
##  to Argonne National Laboratory subject to Software Grant and Corporate
##  Contributor License Agreement dated February 8, 2012.
##

if BUILD_SHM_XPMEM

noinst_HEADERS += src/mpid/ch4/shm/xpmem/shm_inline.h      \
                  src/mpid/ch4/shm/xpmem/xpmem_noinline.h  \
                  src/mpid/ch4/shm/xpmem/xpmem_impl.h      \
                  src/mpid/ch4/shm/xpmem/xpmem_seg.h       \
                  src/mpid/ch4/shm/xpmem/xpmem_send.h      \
                  src/mpid/ch4/shm/xpmem/xpmem_recv.h      \
                  src/mpid/ch4/shm/xpmem/xpmem_control.h   \
                  src/mpid/ch4/shm/xpmem/xpmem_pre.h

mpi_core_sources += src/mpid/ch4/shm/xpmem/globals.c       \
                    src/mpid/ch4/shm/xpmem/xpmem_init.c    \
                    src/mpid/ch4/shm/xpmem/xpmem_control.c \
                    src/mpid/ch4/shm/xpmem/xpmem_win.c
endif