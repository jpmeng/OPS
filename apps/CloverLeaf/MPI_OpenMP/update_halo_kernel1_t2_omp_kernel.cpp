//
// auto-generated by ops.py on 2014-03-10 13:05
//

#ifdef _OPENMP
#include <omp.h>
#endif
//user function
#include "update_halo_kernel.h"

// host stub function
void ops_par_loop_update_halo_kernel1_t2(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7) {

  int  offs[8][2];
  ops_arg args[8] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7};


  sub_block_list sb = OPS_sub_block_list[block->index];
  //compute localy allocated range for the sub-block
  int ndim = sb->ndim;
  int start_add[ndim*8];
  int end_add[ndim*8];

  int s[ndim];
  int e[ndim];

  for ( int n=0; n<ndim; n++ ){
    s[n] = sb->istart[n];e[n] = sb->iend[n]+1;
    if (s[n] >= range[2*n]) {
      s[n] = 0;
    }
    else {
      s[n] = range[2*n] - s[n];
    }
    if (e[n] >= range[2*n+1]) {
      e[n] = range[2*n+1] - sb->istart[n];
    }
    else {
      e[n] = sb->sizes[n];
    }
  }

  for ( int i=0; i<8; i++ ){
    for ( int n=0; n<ndim; n++ ){
      start_add[i*ndim+n] = s[n];
      end_add[i*ndim+n]   = e[n];
    }
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "update_halo_kernel1_t2");
  #endif

  offs[0][0] = args[0].stencil->stride[0]*1;  //unit step in x dimension
  offs[0][1] = off2D(1, &start_add[0*2],
  &end_add[0*2],args[0].dat->block_size, args[0].stencil->stride);

  offs[1][0] = args[1].stencil->stride[0]*1;  //unit step in x dimension
  offs[1][1] = off2D(1, &start_add[1*2],
  &end_add[1*2],args[1].dat->block_size, args[1].stencil->stride);

  offs[2][0] = args[2].stencil->stride[0]*1;  //unit step in x dimension
  offs[2][1] = off2D(1, &start_add[2*2],
  &end_add[2*2],args[2].dat->block_size, args[2].stencil->stride);

  offs[3][0] = args[3].stencil->stride[0]*1;  //unit step in x dimension
  offs[3][1] = off2D(1, &start_add[3*2],
  &end_add[3*2],args[3].dat->block_size, args[3].stencil->stride);

  offs[4][0] = args[4].stencil->stride[0]*1;  //unit step in x dimension
  offs[4][1] = off2D(1, &start_add[4*2],
  &end_add[4*2],args[4].dat->block_size, args[4].stencil->stride);

  offs[5][0] = args[5].stencil->stride[0]*1;  //unit step in x dimension
  offs[5][1] = off2D(1, &start_add[5*2],
  &end_add[5*2],args[5].dat->block_size, args[5].stencil->stride);

  offs[6][0] = args[6].stencil->stride[0]*1;  //unit step in x dimension
  offs[6][1] = off2D(1, &start_add[6*2],
  &end_add[6*2],args[6].dat->block_size, args[6].stencil->stride);



  int off0_1 = offs[0][0];
  int off0_2 = offs[0][1];
  int dat0 = args[0].dat->size;
  int off1_1 = offs[1][0];
  int off1_2 = offs[1][1];
  int dat1 = args[1].dat->size;
  int off2_1 = offs[2][0];
  int off2_2 = offs[2][1];
  int dat2 = args[2].dat->size;
  int off3_1 = offs[3][0];
  int off3_2 = offs[3][1];
  int dat3 = args[3].dat->size;
  int off4_1 = offs[4][0];
  int off4_2 = offs[4][1];
  int dat4 = args[4].dat->size;
  int off5_1 = offs[5][0];
  int off5_2 = offs[5][1];
  int dat5 = args[5].dat->size;
  int off6_1 = offs[6][0];
  int off6_2 = offs[6][1];
  int dat6 = args[6].dat->size;

  int*arg7h = (int *)arg7.data;

  #ifdef _OPENMP
  int nthreads = omp_get_max_threads( );
  #else
  int nthreads = 1;
  #endif
  //allocate and initialise arrays for global reduction
  //assumes a max of 64 threads with a cacche line size of 64 bytes
  int arg_gbl7[NUM_FIELDS * 64 * 64];
  for ( int thr=0; thr<nthreads; thr++ ){
    for ( int d=0; d<NUM_FIELDS; d++ ){
      arg_gbl7[d+64*thr] = arg7h[d];
    }
  }
  xdim0 = args[0].dat->block_size[0];
  xdim1 = args[1].dat->block_size[0];
  xdim2 = args[2].dat->block_size[0];
  xdim3 = args[3].dat->block_size[0];
  xdim4 = args[4].dat->block_size[0];
  xdim5 = args[5].dat->block_size[0];
  xdim6 = args[6].dat->block_size[0];

  //Halo Exchanges
  ops_exchange_halo(&args[0],2);
  ops_exchange_halo(&args[1],2);
  ops_exchange_halo(&args[2],2);
  ops_exchange_halo(&args[3],2);
  ops_exchange_halo(&args[4],2);
  ops_exchange_halo(&args[5],2);
  ops_exchange_halo(&args[6],2);

  ops_H_D_exchanges(args, 8);


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(38,"update_halo_kernel1_t2");
  ops_timers_core(&c1,&t1);

  int start_thread_add[ndim*nthreads*64];

  #pragma omp parallel for
  for ( int thr=0; thr<nthreads; thr++ ){

    int y_size = e[1]-s[1];
    char *p_a[8];

    int start = s[1] + ((y_size-1)/nthreads+1)*thr;
    int finish = s[1] + MIN(((y_size-1)/nthreads+1)*(thr+1),y_size);

    //get addresss per thread
    start_thread_add[64*ndim*thr+0] = s[0];
    start_thread_add[64*ndim*thr+1] = s[1] + ((y_size-1)/nthreads+1)*thr;

    //set up initial pointers 
    int base0 = dat0 * 1 * 
    (start_thread_add[64*ndim*thr+0] * args[0].stencil->stride[0] - args[0].dat->offset[0]);
    base0 = base0  + dat0 * args[0].dat->block_size[0] * 
    (start_thread_add[64*ndim*thr+1] * args[0].stencil->stride[1] - args[0].dat->offset[1]);
    p_a[0] = (char *)args[0].data + base0;

    //set up initial pointers 
    int base1 = dat1 * 1 * 
    (start_thread_add[64*ndim*thr+0] * args[1].stencil->stride[0] - args[1].dat->offset[0]);
    base1 = base1  + dat1 * args[1].dat->block_size[0] * 
    (start_thread_add[64*ndim*thr+1] * args[1].stencil->stride[1] - args[1].dat->offset[1]);
    p_a[1] = (char *)args[1].data + base1;

    //set up initial pointers 
    int base2 = dat2 * 1 * 
    (start_thread_add[64*ndim*thr+0] * args[2].stencil->stride[0] - args[2].dat->offset[0]);
    base2 = base2  + dat2 * args[2].dat->block_size[0] * 
    (start_thread_add[64*ndim*thr+1] * args[2].stencil->stride[1] - args[2].dat->offset[1]);
    p_a[2] = (char *)args[2].data + base2;

    //set up initial pointers 
    int base3 = dat3 * 1 * 
    (start_thread_add[64*ndim*thr+0] * args[3].stencil->stride[0] - args[3].dat->offset[0]);
    base3 = base3  + dat3 * args[3].dat->block_size[0] * 
    (start_thread_add[64*ndim*thr+1] * args[3].stencil->stride[1] - args[3].dat->offset[1]);
    p_a[3] = (char *)args[3].data + base3;

    //set up initial pointers 
    int base4 = dat4 * 1 * 
    (start_thread_add[64*ndim*thr+0] * args[4].stencil->stride[0] - args[4].dat->offset[0]);
    base4 = base4  + dat4 * args[4].dat->block_size[0] * 
    (start_thread_add[64*ndim*thr+1] * args[4].stencil->stride[1] - args[4].dat->offset[1]);
    p_a[4] = (char *)args[4].data + base4;

    //set up initial pointers 
    int base5 = dat5 * 1 * 
    (start_thread_add[64*ndim*thr+0] * args[5].stencil->stride[0] - args[5].dat->offset[0]);
    base5 = base5  + dat5 * args[5].dat->block_size[0] * 
    (start_thread_add[64*ndim*thr+1] * args[5].stencil->stride[1] - args[5].dat->offset[1]);
    p_a[5] = (char *)args[5].data + base5;

    //set up initial pointers 
    int base6 = dat6 * 1 * 
    (start_thread_add[64*ndim*thr+0] * args[6].stencil->stride[0] - args[6].dat->offset[0]);
    base6 = base6  + dat6 * args[6].dat->block_size[0] * 
    (start_thread_add[64*ndim*thr+1] * args[6].stencil->stride[1] - args[6].dat->offset[1]);
    p_a[6] = (char *)args[6].data + base6;

    p_a[7] = (char *)args[7].data;


    for ( int n_y=start; n_y<finish; n_y++ ){
      for ( int n_x=s[0]; n_x<s[0]+(e[0]-s[0])/SIMD_VEC; n_x++ ){
        //call kernel function, passing in pointers to data -vectorised
        for ( int i=0; i<SIMD_VEC; i++ ){
          update_halo_kernel1_t2(  (double *)p_a[0]+ i*1, (double *)p_a[1]+ i*1, (double *)p_a[2]+ i*1,
           (double *)p_a[3]+ i*1, (double *)p_a[4]+ i*1, (double *)p_a[5]+ i*1, (double *)p_a[6]+ i*1,
           &arg_gbl7[64*thr] );

        }

        //shift pointers to data x direction
        p_a[0]= p_a[0] + (dat0 * off0_1)*SIMD_VEC;
        p_a[1]= p_a[1] + (dat1 * off1_1)*SIMD_VEC;
        p_a[2]= p_a[2] + (dat2 * off2_1)*SIMD_VEC;
        p_a[3]= p_a[3] + (dat3 * off3_1)*SIMD_VEC;
        p_a[4]= p_a[4] + (dat4 * off4_1)*SIMD_VEC;
        p_a[5]= p_a[5] + (dat5 * off5_1)*SIMD_VEC;
        p_a[6]= p_a[6] + (dat6 * off6_1)*SIMD_VEC;
      }

      for ( int n_x=s[0]+((e[0]-s[0])/SIMD_VEC)*SIMD_VEC; n_x<e[0]; n_x++ ){
        //call kernel function, passing in pointers to data - remainder
        update_halo_kernel1_t2(  (double *)p_a[0], (double *)p_a[1], (double *)p_a[2],
           (double *)p_a[3], (double *)p_a[4], (double *)p_a[5], (double *)p_a[6],
           &arg_gbl7[64*thr] );


        //shift pointers to data x direction
        p_a[0]= p_a[0] + (dat0 * off0_1);
        p_a[1]= p_a[1] + (dat1 * off1_1);
        p_a[2]= p_a[2] + (dat2 * off2_1);
        p_a[3]= p_a[3] + (dat3 * off3_1);
        p_a[4]= p_a[4] + (dat4 * off4_1);
        p_a[5]= p_a[5] + (dat5 * off5_1);
        p_a[6]= p_a[6] + (dat6 * off6_1);
      }

      //shift pointers to data y direction
      p_a[0]= p_a[0] + (dat0 * off0_2);
      p_a[1]= p_a[1] + (dat1 * off1_2);
      p_a[2]= p_a[2] + (dat2 * off2_2);
      p_a[3]= p_a[3] + (dat3 * off3_2);
      p_a[4]= p_a[4] + (dat4 * off4_2);
      p_a[5]= p_a[5] + (dat5 * off5_2);
      p_a[6]= p_a[6] + (dat6 * off6_2);
    }
  }

  // combine reduction data
  for ( int thr=0; thr<nthreads; thr++ ){
    for ( int d=0; d<NUM_FIELDS; d++ ){
    }
  }
  ops_set_dirtybit_host(args, 8);

  ops_set_halo_dirtybit(&args[0]);
  ops_set_halo_dirtybit(&args[1]);
  ops_set_halo_dirtybit(&args[2]);
  ops_set_halo_dirtybit(&args[3]);
  ops_set_halo_dirtybit(&args[4]);
  ops_set_halo_dirtybit(&args[5]);
  ops_set_halo_dirtybit(&args[6]);

  //Update kernel record
  ops_timers_core(&c2,&t2);
  OPS_kernels[38].count++;
  OPS_kernels[38].time += t2-t1;
  OPS_kernels[38].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[38].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[38].transfer += ops_compute_transfer(dim, range, &arg2);
  OPS_kernels[38].transfer += ops_compute_transfer(dim, range, &arg3);
  OPS_kernels[38].transfer += ops_compute_transfer(dim, range, &arg4);
  OPS_kernels[38].transfer += ops_compute_transfer(dim, range, &arg5);
  OPS_kernels[38].transfer += ops_compute_transfer(dim, range, &arg6);
}