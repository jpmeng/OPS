//
// auto-generated by ops.py
//
//user function
#include "mgrid_populate_kernel.h"

// host stub function
void ops_par_loop_mgrid_populate_kernel_1(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {

  char *p_a[2];
  int  offs[2][2];
  ops_arg args[2] = { arg0, arg1};

  ops_timing_realloc(0,"mgrid_populate_kernel_1");
  OPS_kernels[0].count++;

  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];
  int arg_idx[2];

  #ifdef OPS_MPI
  if (compute_ranges(args, block, range, start, end, arg_idx) < 0) return;
  #else
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif

  #ifdef OPS_DEBUG
  ops_register_args(args, "mgrid_populate_kernel_1");
  #endif

  offs[0][0] = args[0].stencil->stride[0]*1;  //unit step in x dimension
  offs[0][1] = off2D(1, &start[0],
      &end[0],args[0].dat->size, args[0].stencil->stride) - offs[0][0];

  #ifdef OPS_MPI
  int arg_idx_0 = arg_idx[0];
  int arg_idx_1 = arg_idx[0];
  #else //OPS_MPI
  int arg_idx_0 = start[0];
  int arg_idx_1 = start[1];
  #endif //OPS_MPI

  printf("start[0] = %d end[0] = %d, arg_idx[0] = %d\n",start[0],end[0],arg_idx[0]);
  printf("start[1] = %d end[1] = %d, arg_idx[1] = %d\n",start[1],end[1],arg_idx[1]);

  //Timing
  double t1,t2,c1,c2;
  ops_timers_core(&c2,&t2);

  int off0_0 = offs[0][0];
  int off0_1 = offs[0][1];
  int dat0 = args[0].dat->elem_size;

  //set up initial pointers and exchange halos if necessary
  int d_m[OPS_MAX_DIM];
  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d] + OPS_sub_dat_list[args[0].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d];
  #endif //OPS_MPI
  int base0 = dat0 * 1 *
    (start[0] * args[0].stencil->stride[0] - args[0].dat->base[0] - d_m[0]);
  base0 = base0+ dat0 *
    args[0].dat->size[0] *
    (start[1] * args[0].stencil->stride[1] - args[0].dat->base[1] - d_m[1]);
  p_a[0] = (char *)args[0].data + base0;

  p_a[1] = (char *)arg_idx;

  ops_H_D_exchanges_host(args, 2);
  ops_halo_exchanges(args,2,range);
  ops_H_D_exchanges_host(args, 2);

  ops_timers_core(&c1,&t1);
  OPS_kernels[0].mpi_time += t1-t2;

  xdim0 = args[0].dat->size[0]*args[0].dat->dim;

  int n_x;
  for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
    #pragma novector
    for( n_x=start[0]; n_x<start[0]+((end[0]-start[0])/SIMD_VEC)*SIMD_VEC; n_x+=SIMD_VEC ) {
      //call kernel function, passing in pointers to data -vectorised
      for ( int i=0; i<SIMD_VEC; i++ ){
        mgrid_populate_kernel_1(  (double *)p_a[0]+ i*1, (int *)p_a[1] );

        arg_idx[0]++;
      }

      //shift pointers to data x direction
      p_a[0]= p_a[0] + (dat0 * off0_0)*SIMD_VEC;
    }

    for ( int n_x=start[0]+((end[0]-start[0])/SIMD_VEC)*SIMD_VEC; n_x<end[0]; n_x++ ){
      //call kernel function, passing in pointers to data - remainder
      mgrid_populate_kernel_1(  (double *)p_a[0], (int *)p_a[1] );


      //shift pointers to data x direction
      p_a[0]= p_a[0] + (dat0 * off0_0);
      arg_idx[0]++;
    }

    //shift pointers to data y direction
    p_a[0]= p_a[0] + (dat0 * off0_1);
    #ifdef OPS_MPI
    arg_idx[0] = arg_idx_0;
    #else //OPS_MPI
    arg_idx[0] = start[0];
    #endif //OPS_MPI
    arg_idx[1]++;
  }
  ops_timers_core(&c2,&t2);
  OPS_kernels[0].time += t2-t1;
  ops_set_dirtybit_host(args, 2);
  ops_set_halo_dirtybit3(&args[0],range);

  //Update kernel record
  OPS_kernels[0].transfer += ops_compute_transfer(dim, range, &arg0);
}
