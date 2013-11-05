//
// auto-generated by ops.py on 2013-11-05 14:45
//

#include "ops_lib_openmp.h"
#ifdef _OPENMP
#include <omp.h>
#endif
//user function
#include "update_halo_kernel.h"

// host stub function
void ops_par_loop_update_halo_kernel1_l1(char const *name, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6) {

  int  offs[7][2];
  ops_arg args[7] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6};

  offs[0][0] = 1;  //unit step in x dimension
  offs[0][1] = ops_offs_set(range[0],range[2]+1, args[0]) - ops_offs_set(range[1],range[2], args[0]);
  if (args[0].stencil->stride[0] == 0) {
    offs[0][0] = 0;
    offs[0][1] = args[0].dat->block_size[0];
  }
  //stride in x as y stride is 0
  else if (args[0].stencil->stride[1] == 0) {
    offs[0][0] = 1;
    offs[0][1] = -( range[1] - range[0] );
  }

  offs[1][0] = 1;  //unit step in x dimension
  offs[1][1] = ops_offs_set(range[0],range[2]+1, args[1]) - ops_offs_set(range[1],range[2], args[1]);
  if (args[1].stencil->stride[0] == 0) {
    offs[1][0] = 0;
    offs[1][1] = args[1].dat->block_size[0];
  }
  //stride in x as y stride is 0
  else if (args[1].stencil->stride[1] == 0) {
    offs[1][0] = 1;
    offs[1][1] = -( range[1] - range[0] );
  }

  offs[2][0] = 1;  //unit step in x dimension
  offs[2][1] = ops_offs_set(range[0],range[2]+1, args[2]) - ops_offs_set(range[1],range[2], args[2]);
  if (args[2].stencil->stride[0] == 0) {
    offs[2][0] = 0;
    offs[2][1] = args[2].dat->block_size[0];
  }
  //stride in x as y stride is 0
  else if (args[2].stencil->stride[1] == 0) {
    offs[2][0] = 1;
    offs[2][1] = -( range[1] - range[0] );
  }

  offs[3][0] = 1;  //unit step in x dimension
  offs[3][1] = ops_offs_set(range[0],range[2]+1, args[3]) - ops_offs_set(range[1],range[2], args[3]);
  if (args[3].stencil->stride[0] == 0) {
    offs[3][0] = 0;
    offs[3][1] = args[3].dat->block_size[0];
  }
  //stride in x as y stride is 0
  else if (args[3].stencil->stride[1] == 0) {
    offs[3][0] = 1;
    offs[3][1] = -( range[1] - range[0] );
  }

  offs[4][0] = 1;  //unit step in x dimension
  offs[4][1] = ops_offs_set(range[0],range[2]+1, args[4]) - ops_offs_set(range[1],range[2], args[4]);
  if (args[4].stencil->stride[0] == 0) {
    offs[4][0] = 0;
    offs[4][1] = args[4].dat->block_size[0];
  }
  //stride in x as y stride is 0
  else if (args[4].stencil->stride[1] == 0) {
    offs[4][0] = 1;
    offs[4][1] = -( range[1] - range[0] );
  }

  offs[5][0] = 1;  //unit step in x dimension
  offs[5][1] = ops_offs_set(range[0],range[2]+1, args[5]) - ops_offs_set(range[1],range[2], args[5]);
  if (args[5].stencil->stride[0] == 0) {
    offs[5][0] = 0;
    offs[5][1] = args[5].dat->block_size[0];
  }
  //stride in x as y stride is 0
  else if (args[5].stencil->stride[1] == 0) {
    offs[5][0] = 1;
    offs[5][1] = -( range[1] - range[0] );
  }

  offs[6][0] = 1;  //unit step in x dimension
  offs[6][1] = ops_offs_set(range[0],range[2]+1, args[6]) - ops_offs_set(range[1],range[2], args[6]);
  if (args[6].stencil->stride[0] == 0) {
    offs[6][0] = 0;
    offs[6][1] = args[6].dat->block_size[0];
  }
  //stride in x as y stride is 0
  else if (args[6].stencil->stride[1] == 0) {
    offs[6][0] = 1;
    offs[6][1] = -( range[1] - range[0] );
  }

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


  #ifdef _OPENMP
  int nthreads = omp_get_max_threads( );
  #else
  int nthreads = 1;
  #endif


  int y_size = range[3]-range[2];

  xdim0 = args[0].dat->block_size[0];
  xdim1 = args[1].dat->block_size[0];
  xdim2 = args[2].dat->block_size[0];
  xdim3 = args[3].dat->block_size[0];
  xdim4 = args[4].dat->block_size[0];
  xdim5 = args[5].dat->block_size[0];
  xdim6 = args[6].dat->block_size[0];

  #pragma omp parallel for
  for ( int thr=0; thr<nthreads; thr++ ){

    char *p_a[7];

    int start = range[2] + ((y_size-1)/nthreads+1)*thr;
    int finish = range[2] +  MIN(((y_size-1)/nthreads+1)*(thr+1),y_size);

    //set up initial pointers
    p_a[0] = &args[0].data[
    + args[0].dat->size * args[0].dat->block_size[0] * ( start * 1 - args[0].dat->offset[1] )
    + args[0].dat->size * ( range[0] * 1 - args[0].dat->offset[0] ) ];

    p_a[1] = &args[1].data[
    + args[1].dat->size * args[1].dat->block_size[0] * ( start * 1 - args[1].dat->offset[1] )
    + args[1].dat->size * ( range[0] * 1 - args[1].dat->offset[0] ) ];

    p_a[2] = &args[2].data[
    + args[2].dat->size * args[2].dat->block_size[0] * ( start * 1 - args[2].dat->offset[1] )
    + args[2].dat->size * ( range[0] * 1 - args[2].dat->offset[0] ) ];

    p_a[3] = &args[3].data[
    + args[3].dat->size * args[3].dat->block_size[0] * ( start * 1 - args[3].dat->offset[1] )
    + args[3].dat->size * ( range[0] * 1 - args[3].dat->offset[0] ) ];

    p_a[4] = &args[4].data[
    + args[4].dat->size * args[4].dat->block_size[0] * ( start * 1 - args[4].dat->offset[1] )
    + args[4].dat->size * ( range[0] * 1 - args[4].dat->offset[0] ) ];

    p_a[5] = &args[5].data[
    + args[5].dat->size * args[5].dat->block_size[0] * ( start * 1 - args[5].dat->offset[1] )
    + args[5].dat->size * ( range[0] * 1 - args[5].dat->offset[0] ) ];

    p_a[6] = &args[6].data[
    + args[6].dat->size * args[6].dat->block_size[0] * ( start * 1 - args[6].dat->offset[1] )
    + args[6].dat->size * ( range[0] * 1 - args[6].dat->offset[0] ) ];


    for ( int n_y=start; n_y<finish; n_y++ ){
      for ( int n_x=range[0]; n_x<range[0]+(range[1]-range[0])/4; n_x++ ){
        //call kernel function, passing in pointers to data - vectorised
        #pragma simd
        for ( int i=0; i<4; i++ ){
          update_halo_kernel1_l1(  (double *)p_a[0]+ i*1, (double *)p_a[1]+ i*1,
           (double *)p_a[2]+ i*1, (double *)p_a[3]+ i*1,
           (double *)p_a[4]+ i*1, (double *)p_a[5]+ i*1,
           (double *)p_a[6]+ i*1 );

        }

        //shift pointers to data x direction
        p_a[0]= p_a[0] + (dat0 * off0_1)*4;
        p_a[1]= p_a[1] + (dat1 * off1_1)*4;
        p_a[2]= p_a[2] + (dat2 * off2_1)*4;
        p_a[3]= p_a[3] + (dat3 * off3_1)*4;
        p_a[4]= p_a[4] + (dat4 * off4_1)*4;
        p_a[5]= p_a[5] + (dat5 * off5_1)*4;
        p_a[6]= p_a[6] + (dat6 * off6_1)*4;
      }

      for ( int n_x=range[0]+((range[1]-range[0])/4)*4; n_x<range[1]; n_x++ ){
        //call kernel function, passing in pointers to data - remainder
        update_halo_kernel1_l1(  (double *)p_a[0], (double *)p_a[1],
           (double *)p_a[2], (double *)p_a[3],
           (double *)p_a[4], (double *)p_a[5],
           (double *)p_a[6] );


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

}
