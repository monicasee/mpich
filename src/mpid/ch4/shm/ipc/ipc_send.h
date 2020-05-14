/*
 * Copyright (C) by Argonne National Laboratory
 *     See COPYRIGHT in top-level directory
 */

#ifndef IPC_SEND_H_INCLUDED
#define IPC_SEND_H_INCLUDED

#include "ch4_impl.h"
#include "shm_control.h"
#include "ipc_pre.h"
#include "ipc_impl.h"

MPL_STATIC_INLINE_PREFIX int MPIDI_IPC_lmt_isend(const void *buf, MPI_Aint count,
                                                 MPI_Datatype datatype, int rank, int tag,
                                                 MPIR_Comm * comm, int context_offset,
                                                 MPIDI_av_entry_t * addr, MPIR_Request ** request)
{
    int mpi_errno = MPI_SUCCESS;
    MPIR_Request *sreq = NULL;
    size_t data_sz;
    MPI_Aint true_lb;
    bool is_contig ATTRIBUTE((unused)) = 0;
    MPIDI_SHM_ctrl_hdr_t ctrl_hdr;
    MPL_pointer_attr_t attr;

    MPIR_FUNC_VERBOSE_STATE_DECL(MPID_STATE_MPIDI_IPC_LMT_ISEND);
    MPIR_FUNC_VERBOSE_ENTER(MPID_STATE_MPIDI_IPC_LMT_ISEND);

    MPIR_Datatype_add_ref_if_not_builtin(datatype);
    sreq = MPIDIG_request_create(MPIR_REQUEST_KIND__SEND, 2);
    MPIR_ERR_CHKANDSTMT((sreq) == NULL, mpi_errno, MPIX_ERR_NOREQ, goto fn_fail, "**nomemreq");
    *request = sreq;
    MPIDIG_REQUEST(sreq, buffer) = (void *) buf;
    MPIDIG_REQUEST(sreq, datatype) = datatype;
    MPIDIG_REQUEST(sreq, rank) = rank;
    MPIDIG_REQUEST(sreq, count) = count;
    MPIDIG_REQUEST(sreq, context_id) = comm->context_id + context_offset;

    MPIDI_Datatype_check_contig_size_lb(datatype, count, is_contig, data_sz, true_lb);

    MPIR_Assert(is_contig && data_sz > 0);

    MPL_gpu_query_pointer_attr(buf, &attr);

#ifdef MPIDI_CH4_SHM_ENABLE_XPMEM
    if (attr.type != MPL_GPU_POINTER_DEV) {
        /* XPMEM internal info */
        ctrl_hdr.ipc_type = MPIDI_SHM_CTRL_IPC_TYPE__XPMEM;
        MPIDI_SHM_ctrl_xpmem_send_lmt_rts_t *slmt_req_hdr = &ctrl_hdr.u.xpmem_slmt_rts;
        slmt_req_hdr->src_offset = (uint64_t) buf + true_lb;
        slmt_req_hdr->data_sz = data_sz;
        slmt_req_hdr->sreq_ptr = (uint64_t) sreq;
        slmt_req_hdr->src_lrank = MPIR_Process.local_rank;

        /* message matching info */
        slmt_req_hdr->src_rank = comm->rank;
        slmt_req_hdr->tag = tag;
        slmt_req_hdr->context_id = comm->context_id + context_offset;

        IPC_TRACE("lmt_isend: shm ctrl_id %d, src_offset 0x%lx, data_sz 0x%lx, sreq_ptr 0x%lx, "
                  "src_lrank %d, match info[dest %d, src_rank %d, tag %d, context_id 0x%x]\n",
                  MPIDI_SHM_IPC_SEND_LMT_RTS, slmt_req_hdr->src_offset,
                  slmt_req_hdr->data_sz, slmt_req_hdr->sreq_ptr, slmt_req_hdr->src_lrank,
                  rank, slmt_req_hdr->src_rank, slmt_req_hdr->tag, slmt_req_hdr->context_id);

        MPIDI_XPMEM_REQUEST(sreq, counter_ptr) = NULL;
    }
#endif

    mpi_errno = MPIDI_SHM_do_ctrl_send(rank, comm, MPIDI_SHM_IPC_SEND_LMT_RTS, &ctrl_hdr);
    MPIR_ERR_CHECK(mpi_errno);

  fn_exit:
    MPIR_FUNC_VERBOSE_EXIT(MPID_STATE_MPIDI_IPC_LMT_ISEND);
    return mpi_errno;
  fn_fail:
    goto fn_exit;
}

#endif /* IPC_SEND_H_INCLUDED */