//
// auto-generated by ops.py on 2014-07-31 17:05
//

#ifdef _OPENMP
#include <omp.h>
#endif

//user function

inline void advec_cell_kernel3_zdir( const double *vol_flux_z, const double *pre_vol, const int *zz,
                              const double *vertexdz,
                              const double *density1, const double *energy1 ,
                              double *mass_flux_z, double *ener_flux) {

  double sigma, sigmat, sigmav, sigmam, sigma3, sigma4;
  double diffuw, diffdw, limiter;
  double one_by_six = 1.0/6.0;

  int z_max=field.z_max;

  int upwind,donor,downwind,dif;

  if(vol_flux_z[OPS_ACC0(0,0,0)] > 0.0) {
    upwind   = -2;
    donor    = -1;
    downwind = 0;
    dif      = donor;
  }
  else if (zz[OPS_ACC2(0,0,1)] < z_max+2-2) {
    upwind   = 1;
    donor    = 0;
    downwind = -1;
    dif      = upwind;
  } else {
    upwind   = 0;
    donor    = 0;
    downwind = -1;
    dif      = upwind;
  }

  sigmat = fabs(vol_flux_z[OPS_ACC0(0,0,0)])/pre_vol[OPS_ACC1(0,0,donor)];
  sigma3 = (1.0 + sigmat)*(vertexdz[OPS_ACC3(0,0,0)]/vertexdz[OPS_ACC3(0,0,dif)]);
  sigma4 = 2.0 - sigmat;

  sigma = sigmat;
  sigmav = sigmat;

  diffuw = density1[OPS_ACC4(0,0,donor)] - density1[OPS_ACC4(0,0,upwind)];
  diffdw = density1[OPS_ACC4(0,0,downwind)] - density1[OPS_ACC4(0,0,donor)];

  if( (diffuw*diffdw) > 0.0)
    limiter=(1.0 - sigmav) * SIGN(1.0 , diffdw) *
    MIN( MIN(fabs(diffuw), fabs(diffdw)),
    one_by_six * (sigma3*fabs(diffuw) + sigma4 * fabs(diffdw)));
  else
    limiter=0.0;

  mass_flux_z[OPS_ACC6(0,0,0)] = vol_flux_z[OPS_ACC0(0,0,0)] * ( density1[OPS_ACC4(0,0,donor)] + limiter );

  sigmam = fabs(mass_flux_z[OPS_ACC6(0,0,0)])/( density1[OPS_ACC4(0,0,donor)] * pre_vol[OPS_ACC1(0,0,donor)]);
  diffuw = energy1[OPS_ACC5(0,0,donor)] - energy1[OPS_ACC5(0,0,upwind)];
  diffdw = energy1[OPS_ACC5(0,0,downwind)] - energy1[OPS_ACC5(0,0,donor)];

  if( (diffuw*diffdw) > 0.0)
    limiter = (1.0 - sigmam) * SIGN(1.0,diffdw) *
    MIN( MIN(fabs(diffuw), fabs(diffdw)),
    one_by_six * (sigma3 * fabs(diffuw) + sigma4 * fabs(diffdw)));
  else
    limiter=0.0;

  ener_flux[OPS_ACC7(0,0,0)] = mass_flux_z[OPS_ACC6(0,0,0)] * ( energy1[OPS_ACC5(0,0,donor)] + limiter );
}



// host stub function
void ops_par_loop_advec_cell_kernel3_zdir(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7) {

  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(39,"advec_cell_kernel3_zdir");
  ops_timers_core(&c1,&t1);


  int  offs[8][3];
  ops_arg args[8] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7};


  sub_block_list sb = OPS_sub_block_list[block->index];
  //compute localy allocated range for the sub-block

  int start[3];
  int end[3];

  for ( int n=0; n<3; n++ ){
    start[n] = sb->istart[n];end[n] = sb->iend[n]+1;
    if (start[n] >= range[2*n]) {
      start[n] = 0;
    }
    else {
      start[n] = range[2*n] - start[n];
    }
    if (end[n] >= range[2*n+1]) {
      end[n] = range[2*n+1] - sb->istart[n];
    }
    else {
      end[n] = sb->sizes[n];
    }
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "advec_cell_kernel3_zdir");
  #endif

  offs[0][0] = args[0].stencil->stride[0]*1;  //unit step in x dimension
  offs[0][1] = off3D(1, &start[0],
      &end[0],args[0].dat->block_size, args[0].stencil->stride) - offs[0][0];
  offs[0][2] = off3D(2, &start[0],
      &end[0],args[0].dat->block_size, args[0].stencil->stride) - offs[0][1] - offs[0][0];

  offs[1][0] = args[1].stencil->stride[0]*1;  //unit step in x dimension
  offs[1][1] = off3D(1, &start[0],
      &end[0],args[1].dat->block_size, args[1].stencil->stride) - offs[1][0];
  offs[1][2] = off3D(2, &start[0],
      &end[0],args[1].dat->block_size, args[1].stencil->stride) - offs[1][1] - offs[1][0];

  offs[2][0] = args[2].stencil->stride[0]*1;  //unit step in x dimension
  offs[2][1] = off3D(1, &start[0],
      &end[0],args[2].dat->block_size, args[2].stencil->stride) - offs[2][0];
  offs[2][2] = off3D(2, &start[0],
      &end[0],args[2].dat->block_size, args[2].stencil->stride) - offs[2][1] - offs[2][0];

  offs[3][0] = args[3].stencil->stride[0]*1;  //unit step in x dimension
  offs[3][1] = off3D(1, &start[0],
      &end[0],args[3].dat->block_size, args[3].stencil->stride) - offs[3][0];
  offs[3][2] = off3D(2, &start[0],
      &end[0],args[3].dat->block_size, args[3].stencil->stride) - offs[3][1] - offs[3][0];

  offs[4][0] = args[4].stencil->stride[0]*1;  //unit step in x dimension
  offs[4][1] = off3D(1, &start[0],
      &end[0],args[4].dat->block_size, args[4].stencil->stride) - offs[4][0];
  offs[4][2] = off3D(2, &start[0],
      &end[0],args[4].dat->block_size, args[4].stencil->stride) - offs[4][1] - offs[4][0];

  offs[5][0] = args[5].stencil->stride[0]*1;  //unit step in x dimension
  offs[5][1] = off3D(1, &start[0],
      &end[0],args[5].dat->block_size, args[5].stencil->stride) - offs[5][0];
  offs[5][2] = off3D(2, &start[0],
      &end[0],args[5].dat->block_size, args[5].stencil->stride) - offs[5][1] - offs[5][0];

  offs[6][0] = args[6].stencil->stride[0]*1;  //unit step in x dimension
  offs[6][1] = off3D(1, &start[0],
      &end[0],args[6].dat->block_size, args[6].stencil->stride) - offs[6][0];
  offs[6][2] = off3D(2, &start[0],
      &end[0],args[6].dat->block_size, args[6].stencil->stride) - offs[6][1] - offs[6][0];

  offs[7][0] = args[7].stencil->stride[0]*1;  //unit step in x dimension
  offs[7][1] = off3D(1, &start[0],
      &end[0],args[7].dat->block_size, args[7].stencil->stride) - offs[7][0];
  offs[7][2] = off3D(2, &start[0],
      &end[0],args[7].dat->block_size, args[7].stencil->stride) - offs[7][1] - offs[7][0];



  int off0_0 = offs[0][0];
  int off0_1 = offs[0][1];
  int off0_2 = offs[0][2];
  int dat0 = args[0].dat->size;
  int off1_0 = offs[1][0];
  int off1_1 = offs[1][1];
  int off1_2 = offs[1][2];
  int dat1 = args[1].dat->size;
  int off2_0 = offs[2][0];
  int off2_1 = offs[2][1];
  int off2_2 = offs[2][2];
  int dat2 = args[2].dat->size;
  int off3_0 = offs[3][0];
  int off3_1 = offs[3][1];
  int off3_2 = offs[3][2];
  int dat3 = args[3].dat->size;
  int off4_0 = offs[4][0];
  int off4_1 = offs[4][1];
  int off4_2 = offs[4][2];
  int dat4 = args[4].dat->size;
  int off5_0 = offs[5][0];
  int off5_1 = offs[5][1];
  int off5_2 = offs[5][2];
  int dat5 = args[5].dat->size;
  int off6_0 = offs[6][0];
  int off6_1 = offs[6][1];
  int off6_2 = offs[6][2];
  int dat6 = args[6].dat->size;
  int off7_0 = offs[7][0];
  int off7_1 = offs[7][1];
  int off7_2 = offs[7][2];
  int dat7 = args[7].dat->size;


  #ifdef _OPENMP
  int nthreads = omp_get_max_threads( );
  #else
  int nthreads = 1;
  #endif
  xdim0 = args[0].dat->block_size[0]*args[0].dat->dim;
  ydim0 = args[0].dat->block_size[1];
  xdim1 = args[1].dat->block_size[0]*args[1].dat->dim;
  ydim1 = args[1].dat->block_size[1];
  xdim2 = args[2].dat->block_size[0]*args[2].dat->dim;
  ydim2 = args[2].dat->block_size[1];
  xdim3 = args[3].dat->block_size[0]*args[3].dat->dim;
  ydim3 = args[3].dat->block_size[1];
  xdim4 = args[4].dat->block_size[0]*args[4].dat->dim;
  ydim4 = args[4].dat->block_size[1];
  xdim5 = args[5].dat->block_size[0]*args[5].dat->dim;
  ydim5 = args[5].dat->block_size[1];
  xdim6 = args[6].dat->block_size[0]*args[6].dat->dim;
  ydim6 = args[6].dat->block_size[1];
  xdim7 = args[7].dat->block_size[0]*args[7].dat->dim;
  ydim7 = args[7].dat->block_size[1];

  ops_H_D_exchanges(args, 8);

  //Halo Exchanges
  ops_halo_exchanges(args,8,range);


  ops_timers_core(&c2,&t2);
  OPS_kernels[39].mpi_time += t2-t1;


  #pragma omp parallel for
  for ( int thr=0; thr<nthreads; thr++ ){

    int z_size = end[2]-start[2];
    char *p_a[8];

    int start_i = start[2] + ((z_size-1)/nthreads+1)*thr;
    int finish_i = start[2] + MIN(((z_size-1)/nthreads+1)*(thr+1),z_size);

    //get address per thread
    int start0 = start[0];
    int start1 = start[1];
    int start2 = start_i;

    //set up initial pointers 
    int base0 = dat0 * 1 * 
    (start0 * args[0].stencil->stride[0] - args[0].dat->offset[0]);
    base0 = base0+ dat0 *
      args[0].dat->block_size[0] *
      (start1 * args[0].stencil->stride[1] - args[0].dat->offset[1]);
    base0 = base0+ dat0 *
      args[0].dat->block_size[0] *
      args[0].dat->block_size[1] *
      (start2 * args[0].stencil->stride[2] - args[0].dat->offset[2]);
    p_a[0] = (char *)args[0].data + base0;

    int base1 = dat1 * 1 * 
    (start0 * args[1].stencil->stride[0] - args[1].dat->offset[0]);
    base1 = base1+ dat1 *
      args[1].dat->block_size[0] *
      (start1 * args[1].stencil->stride[1] - args[1].dat->offset[1]);
    base1 = base1+ dat1 *
      args[1].dat->block_size[0] *
      args[1].dat->block_size[1] *
      (start2 * args[1].stencil->stride[2] - args[1].dat->offset[2]);
    p_a[1] = (char *)args[1].data + base1;

    int base2 = dat2 * 1 * 
    (start0 * args[2].stencil->stride[0] - args[2].dat->offset[0]);
    base2 = base2+ dat2 *
      args[2].dat->block_size[0] *
      (start1 * args[2].stencil->stride[1] - args[2].dat->offset[1]);
    base2 = base2+ dat2 *
      args[2].dat->block_size[0] *
      args[2].dat->block_size[1] *
      (start2 * args[2].stencil->stride[2] - args[2].dat->offset[2]);
    p_a[2] = (char *)args[2].data + base2;

    int base3 = dat3 * 1 * 
    (start0 * args[3].stencil->stride[0] - args[3].dat->offset[0]);
    base3 = base3+ dat3 *
      args[3].dat->block_size[0] *
      (start1 * args[3].stencil->stride[1] - args[3].dat->offset[1]);
    base3 = base3+ dat3 *
      args[3].dat->block_size[0] *
      args[3].dat->block_size[1] *
      (start2 * args[3].stencil->stride[2] - args[3].dat->offset[2]);
    p_a[3] = (char *)args[3].data + base3;

    int base4 = dat4 * 1 * 
    (start0 * args[4].stencil->stride[0] - args[4].dat->offset[0]);
    base4 = base4+ dat4 *
      args[4].dat->block_size[0] *
      (start1 * args[4].stencil->stride[1] - args[4].dat->offset[1]);
    base4 = base4+ dat4 *
      args[4].dat->block_size[0] *
      args[4].dat->block_size[1] *
      (start2 * args[4].stencil->stride[2] - args[4].dat->offset[2]);
    p_a[4] = (char *)args[4].data + base4;

    int base5 = dat5 * 1 * 
    (start0 * args[5].stencil->stride[0] - args[5].dat->offset[0]);
    base5 = base5+ dat5 *
      args[5].dat->block_size[0] *
      (start1 * args[5].stencil->stride[1] - args[5].dat->offset[1]);
    base5 = base5+ dat5 *
      args[5].dat->block_size[0] *
      args[5].dat->block_size[1] *
      (start2 * args[5].stencil->stride[2] - args[5].dat->offset[2]);
    p_a[5] = (char *)args[5].data + base5;

    int base6 = dat6 * 1 * 
    (start0 * args[6].stencil->stride[0] - args[6].dat->offset[0]);
    base6 = base6+ dat6 *
      args[6].dat->block_size[0] *
      (start1 * args[6].stencil->stride[1] - args[6].dat->offset[1]);
    base6 = base6+ dat6 *
      args[6].dat->block_size[0] *
      args[6].dat->block_size[1] *
      (start2 * args[6].stencil->stride[2] - args[6].dat->offset[2]);
    p_a[6] = (char *)args[6].data + base6;

    int base7 = dat7 * 1 * 
    (start0 * args[7].stencil->stride[0] - args[7].dat->offset[0]);
    base7 = base7+ dat7 *
      args[7].dat->block_size[0] *
      (start1 * args[7].stencil->stride[1] - args[7].dat->offset[1]);
    base7 = base7+ dat7 *
      args[7].dat->block_size[0] *
      args[7].dat->block_size[1] *
      (start2 * args[7].stencil->stride[2] - args[7].dat->offset[2]);
    p_a[7] = (char *)args[7].data + base7;


    for ( int n_z=start_i; n_z<finish_i; n_z++ ){
      for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
        for ( int n_x=start[0]; n_x<start[0]+(end[0]-start[0])/SIMD_VEC; n_x++ ){
          //call kernel function, passing in pointers to data -vectorised
          #pragma simd
          for ( int i=0; i<SIMD_VEC; i++ ){
            advec_cell_kernel3_zdir(  (const double * restrict)p_a[0]+ i*1, (const double * restrict)p_a[1]+ i*1, (const int * restrict)p_a[2]+ i*0,
           (const double * restrict)p_a[3]+ i*0, (const double * restrict)p_a[4]+ i*1, (const double * restrict)p_a[5]+ i*1, (double * restrict)p_a[6]+ i*1,
           (double * restrict)p_a[7]+ i*1 );

          }

          //shift pointers to data x direction
          p_a[0]= p_a[0] + (dat0 * off0_0)*SIMD_VEC;
          p_a[1]= p_a[1] + (dat1 * off1_0)*SIMD_VEC;
          p_a[2]= p_a[2] + (dat2 * off2_0)*SIMD_VEC;
          p_a[3]= p_a[3] + (dat3 * off3_0)*SIMD_VEC;
          p_a[4]= p_a[4] + (dat4 * off4_0)*SIMD_VEC;
          p_a[5]= p_a[5] + (dat5 * off5_0)*SIMD_VEC;
          p_a[6]= p_a[6] + (dat6 * off6_0)*SIMD_VEC;
          p_a[7]= p_a[7] + (dat7 * off7_0)*SIMD_VEC;
        }

        for ( int n_x=start[0]+((end[0]-start[0])/SIMD_VEC)*SIMD_VEC; n_x<end[0]; n_x++ ){
          //call kernel function, passing in pointers to data - remainder
          advec_cell_kernel3_zdir(  (const double * restrict)p_a[0], (const double * restrict)p_a[1], (const int * restrict)p_a[2],
           (const double * restrict)p_a[3], (const double * restrict)p_a[4], (const double * restrict)p_a[5], (double * restrict)p_a[6],
           (double * restrict)p_a[7] );


          //shift pointers to data x direction
          p_a[0]= p_a[0] + (dat0 * off0_0);
          p_a[1]= p_a[1] + (dat1 * off1_0);
          p_a[2]= p_a[2] + (dat2 * off2_0);
          p_a[3]= p_a[3] + (dat3 * off3_0);
          p_a[4]= p_a[4] + (dat4 * off4_0);
          p_a[5]= p_a[5] + (dat5 * off5_0);
          p_a[6]= p_a[6] + (dat6 * off6_0);
          p_a[7]= p_a[7] + (dat7 * off7_0);
        }

        //shift pointers to data y direction
        p_a[0]= p_a[0] + (dat0 * off0_1);
        p_a[1]= p_a[1] + (dat1 * off1_1);
        p_a[2]= p_a[2] + (dat2 * off2_1);
        p_a[3]= p_a[3] + (dat3 * off3_1);
        p_a[4]= p_a[4] + (dat4 * off4_1);
        p_a[5]= p_a[5] + (dat5 * off5_1);
        p_a[6]= p_a[6] + (dat6 * off6_1);
        p_a[7]= p_a[7] + (dat7 * off7_1);
      }
      //shift pointers to data z direction
      p_a[0]= p_a[0] + (dat0 * off0_2);
      p_a[1]= p_a[1] + (dat1 * off1_2);
      p_a[2]= p_a[2] + (dat2 * off2_2);
      p_a[3]= p_a[3] + (dat3 * off3_2);
      p_a[4]= p_a[4] + (dat4 * off4_2);
      p_a[5]= p_a[5] + (dat5 * off5_2);
      p_a[6]= p_a[6] + (dat6 * off6_2);
      p_a[7]= p_a[7] + (dat7 * off7_2);
    }
  }

  ops_timers_core(&c1,&t1);
  OPS_kernels[39].time += t1-t2;

  ops_set_dirtybit_host(args, 8);

  ops_set_halo_dirtybit3(&args[6],range);
  ops_set_halo_dirtybit3(&args[7],range);

  #ifdef OPS_DEBUG
  ops_dump3(arg6.dat,"advec_cell_kernel3_zdir");
  ops_dump3(arg7.dat,"advec_cell_kernel3_zdir");
  #endif

  //Update kernel record
  ops_timers_core(&c2,&t2);
  OPS_kernels[39].count++;
  OPS_kernels[39].mpi_time += t2-t1;
  OPS_kernels[39].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[39].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[39].transfer += ops_compute_transfer(dim, range, &arg2);
  OPS_kernels[39].transfer += ops_compute_transfer(dim, range, &arg3);
  OPS_kernels[39].transfer += ops_compute_transfer(dim, range, &arg4);
  OPS_kernels[39].transfer += ops_compute_transfer(dim, range, &arg5);
  OPS_kernels[39].transfer += ops_compute_transfer(dim, range, &arg6);
  OPS_kernels[39].transfer += ops_compute_transfer(dim, range, &arg7);
}
