##
## Copyright (C) by Argonne National Laboratory
##     See COPYRIGHT in top-level directory
##

if BUILD_SHM_XPMEM

noinst_HEADERS += src/mpid/ch4/shm/ipc/shm_inline.h    \
                  src/mpid/ch4/shm/ipc/ipc_noinline.h  \
                  src/mpid/ch4/shm/ipc/ipc_impl.h      \
                  src/mpid/ch4/shm/ipc/ipc_seg.h       \
                  src/mpid/ch4/shm/ipc/ipc_send.h      \
                  src/mpid/ch4/shm/ipc/ipc_recv.h      \
                  src/mpid/ch4/shm/ipc/ipc_control.h   \
                  src/mpid/ch4/shm/ipc/ipc_pre.h

mpi_core_sources += src/mpid/ch4/shm/ipc/globals.c     \
                    src/mpid/ch4/shm/ipc/ipc_init.c    \
                    src/mpid/ch4/shm/ipc/ipc_control.c \
                    src/mpid/ch4/shm/ipc/ipc_win.c

endif
