//
// auto-generated by ops.py on 2014-07-31 17:05
//

#include "./OpenACC/clover_leaf_common.h"

#define OPS_GPU

extern int xdim0_initialise_chunk_kernel_y;
extern int ydim0_initialise_chunk_kernel_y;
extern int xdim1_initialise_chunk_kernel_y;
extern int ydim1_initialise_chunk_kernel_y;
extern int xdim2_initialise_chunk_kernel_y;
extern int ydim2_initialise_chunk_kernel_y;

#ifdef __cplusplus
extern "C" {
#endif
void initialise_chunk_kernel_y_c_wrapper(
  double *p_a0,
  int *p_a1,
  double *p_a2,
  int x_size, int y_size, int z_size);

#ifdef __cplusplus
}
#endif

// host stub function
void ops_par_loop_initialise_chunk_kernel_y(char const *name, ops_block Block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2) {

  ops_arg args[3] = { arg0, arg1, arg2};

  sub_block_list sb = OPS_sub_block_list[Block->index];
  //compute localy allocated range for the sub-block
  int start_add[3];
  int end_add[3];
  for ( int n=0; n<3; n++ ){
    start_add[n] = sb->istart[n];end_add[n] = sb->iend[n]+1;
    if (start_add[n] >= range[2*n]) {
      start_add[n] = 0;
    }
    else {
      start_add[n] = range[2*n] - start_add[n];
    }
    if (end_add[n] >= range[2*n+1]) {
      end_add[n] = range[2*n+1] - sb->istart[n];
    }
    else {
      end_add[n] = sb->sizes[n];
    }
  }


  int x_size = MAX(0,end_add[0]-start_add[0]);
  int y_size = MAX(0,end_add[1]-start_add[1]);
  int z_size = MAX(0,end_add[2]-start_add[2]);


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(131,"initialise_chunk_kernel_y");
  ops_timers_core(&c2,&t2);

  if (OPS_kernels[131].count == 0) {
    xdim0_initialise_chunk_kernel_y = args[0].dat->block_size[0]*args[0].dat->dim;
    ydim0_initialise_chunk_kernel_y = args[0].dat->block_size[1];
    xdim1_initialise_chunk_kernel_y = args[1].dat->block_size[0]*args[1].dat->dim;
    ydim1_initialise_chunk_kernel_y = args[1].dat->block_size[1];
    xdim2_initialise_chunk_kernel_y = args[2].dat->block_size[0]*args[2].dat->dim;
    ydim2_initialise_chunk_kernel_y = args[2].dat->block_size[1];
  }

  int dat0 = args[0].dat->size;
  int dat1 = args[1].dat->size;
  int dat2 = args[2].dat->size;


  //set up initial pointers
  int base0 = dat0 * 1 * 
    (start_add[0] * args[0].stencil->stride[0] - args[0].dat->offset[0]);
  base0 = base0+ dat0 *
    args[0].dat->block_size[0] *
    (start_add[1] * args[0].stencil->stride[1] - args[0].dat->offset[1]);
  base0 = base0+ dat0 *
    args[0].dat->block_size[0] *
    args[0].dat->block_size[1] *
    (start_add[2] * args[0].stencil->stride[2] - args[0].dat->offset[2]);
  #ifdef OPS_GPU
  double *p_a0 = (double *)((char *)args[0].data_d + base0);
  #else
  double *p_a0 = (double *)((char *)args[0].data + base0);
  #endif

  int base1 = dat1 * 1 * 
    (start_add[0] * args[1].stencil->stride[0] - args[1].dat->offset[0]);
  base1 = base1+ dat1 *
    args[1].dat->block_size[0] *
    (start_add[1] * args[1].stencil->stride[1] - args[1].dat->offset[1]);
  base1 = base1+ dat1 *
    args[1].dat->block_size[0] *
    args[1].dat->block_size[1] *
    (start_add[2] * args[1].stencil->stride[2] - args[1].dat->offset[2]);
  #ifdef OPS_GPU
  int *p_a1 = (int *)((char *)args[1].data_d + base1);
  #else
  int *p_a1 = (int *)((char *)args[1].data + base1);
  #endif

  int base2 = dat2 * 1 * 
    (start_add[0] * args[2].stencil->stride[0] - args[2].dat->offset[0]);
  base2 = base2+ dat2 *
    args[2].dat->block_size[0] *
    (start_add[1] * args[2].stencil->stride[1] - args[2].dat->offset[1]);
  base2 = base2+ dat2 *
    args[2].dat->block_size[0] *
    args[2].dat->block_size[1] *
    (start_add[2] * args[2].stencil->stride[2] - args[2].dat->offset[2]);
  #ifdef OPS_GPU
  double *p_a2 = (double *)((char *)args[2].data_d + base2);
  #else
  double *p_a2 = (double *)((char *)args[2].data + base2);
  #endif


  #ifdef OPS_GPU
  ops_H_D_exchanges_cuda(args, 3);
  #else
  ops_H_D_exchanges(args, 3);
  #endif
  ops_halo_exchanges(args,3,range);

  ops_timers_core(&c1,&t1);
  OPS_kernels[131].mpi_time += t1-t2;

  initialise_chunk_kernel_y_c_wrapper(
    p_a0,
    p_a1,
    p_a2,
    x_size, y_size, z_size);

  ops_timers_core(&c2,&t2);
  OPS_kernels[131].time += t2-t1;
  #ifdef OPS_GPU
  ops_set_dirtybit_cuda(args, 3);
  #else
  ops_set_dirtybit_host(args, 3);
  #endif
  ops_set_halo_dirtybit3(&args[0],range);
  ops_set_halo_dirtybit3(&args[2],range);

  //Update kernel record
  OPS_kernels[131].count++;
  OPS_kernels[131].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[131].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[131].transfer += ops_compute_transfer(dim, range, &arg2);
}
