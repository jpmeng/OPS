//
// auto-generated by ops.py
//

//user function
inline void accelerate_kernel( const ACC<double> &density0, const ACC<double> &volume,
                ACC<double> &stepbymass, const ACC<double> &xvel0, ACC<double> &xvel1,
                const ACC<double> &xarea, const ACC<double> &pressure,
                const ACC<double> &yvel0, ACC<double> &yvel1,
                const ACC<double> &yarea, const ACC<double> &viscosity) {

  double nodal_mass;

  nodal_mass = ( density0(-1,-1) * volume(-1,-1)
    + density0(0,-1) * volume(0,-1)
    + density0(0,0) * volume(0,0)
    + density0(-1,0) * volume(-1,0) ) * 0.25;

  stepbymass(0,0) = 0.5*dt/ nodal_mass;



  xvel1(0,0) = xvel0(0,0) - stepbymass(0,0) *
            ( xarea(0,0)  * ( pressure(0,0) - pressure(-1,0) ) +
              xarea(0,-1) * ( pressure(0,-1) - pressure(-1,-1) ) );



  yvel1(0,0) = yvel0(0,0) - stepbymass(0,0) *
            ( yarea(0,0)  * ( pressure(0,0) - pressure(0,-1) ) +
              yarea(-1,0) * ( pressure(-1,0) - pressure(-1,-1) ) );



  xvel1(0,0) = xvel1(0,0) - stepbymass(0,0) *
            ( xarea(0,0) * ( viscosity(0,0) - viscosity(-1,0) ) +
              xarea(0,-1) * ( viscosity(0,-1) - viscosity(-1,-1) ) );



  yvel1(0,0) = yvel1(0,0) - stepbymass(0,0) *
            ( yarea(0,0) * ( viscosity(0,0) - viscosity(0,-1) ) +
              yarea(-1,0) * ( viscosity(-1,0) - viscosity(-1,-1) ) );

}





// host stub function
void ops_par_loop_accelerate_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7,
 ops_arg arg8, ops_arg arg9, ops_arg arg10) {

  //Timing
  double t1,t2,c1,c2;

  char *p_a[11];
  int  offs[11][2];
  ops_arg args[11] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10};



  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,11,range,58)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(58,"accelerate_kernel");
    OPS_kernels[58].count++;
    ops_timers_core(&c2,&t2);
  }

  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];

  #ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned) return;
  for ( int n=0; n<2; n++ ){
    start[n] = sb->decomp_disp[n];end[n] = sb->decomp_disp[n]+sb->decomp_size[n];
    if (start[n] >= range[2*n]) {
      start[n] = 0;
    }
    else {
      start[n] = range[2*n] - start[n];
    }
    if (sb->id_m[n]==MPI_PROC_NULL && range[2*n] < 0) start[n] = range[2*n];
    if (end[n] >= range[2*n+1]) {
      end[n] = range[2*n+1] - sb->decomp_disp[n];
    }
    else {
      end[n] = sb->decomp_size[n];
    }
    if (sb->id_p[n]==MPI_PROC_NULL && (range[2*n+1] > sb->decomp_disp[n]+sb->decomp_size[n]))
      end[n] += (range[2*n+1]-sb->decomp_disp[n]-sb->decomp_size[n]);
  }
  #else
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif
  #ifdef OPS_DEBUG
  ops_register_args(args, "accelerate_kernel");
  #endif

  offs[0][0] = args[0].stencil->stride[0]*1;  //unit step in x dimension
  offs[0][1] = off2D(1, &start[0],
      &end[0],args[0].dat->size, args[0].stencil->stride) - offs[0][0];

  offs[1][0] = args[1].stencil->stride[0]*1;  //unit step in x dimension
  offs[1][1] = off2D(1, &start[0],
      &end[0],args[1].dat->size, args[1].stencil->stride) - offs[1][0];

  offs[2][0] = args[2].stencil->stride[0]*1;  //unit step in x dimension
  offs[2][1] = off2D(1, &start[0],
      &end[0],args[2].dat->size, args[2].stencil->stride) - offs[2][0];

  offs[3][0] = args[3].stencil->stride[0]*1;  //unit step in x dimension
  offs[3][1] = off2D(1, &start[0],
      &end[0],args[3].dat->size, args[3].stencil->stride) - offs[3][0];

  offs[4][0] = args[4].stencil->stride[0]*1;  //unit step in x dimension
  offs[4][1] = off2D(1, &start[0],
      &end[0],args[4].dat->size, args[4].stencil->stride) - offs[4][0];

  offs[5][0] = args[5].stencil->stride[0]*1;  //unit step in x dimension
  offs[5][1] = off2D(1, &start[0],
      &end[0],args[5].dat->size, args[5].stencil->stride) - offs[5][0];

  offs[6][0] = args[6].stencil->stride[0]*1;  //unit step in x dimension
  offs[6][1] = off2D(1, &start[0],
      &end[0],args[6].dat->size, args[6].stencil->stride) - offs[6][0];

  offs[7][0] = args[7].stencil->stride[0]*1;  //unit step in x dimension
  offs[7][1] = off2D(1, &start[0],
      &end[0],args[7].dat->size, args[7].stencil->stride) - offs[7][0];

  offs[8][0] = args[8].stencil->stride[0]*1;  //unit step in x dimension
  offs[8][1] = off2D(1, &start[0],
      &end[0],args[8].dat->size, args[8].stencil->stride) - offs[8][0];

  offs[9][0] = args[9].stencil->stride[0]*1;  //unit step in x dimension
  offs[9][1] = off2D(1, &start[0],
      &end[0],args[9].dat->size, args[9].stencil->stride) - offs[9][0];

  offs[10][0] = args[10].stencil->stride[0]*1;  //unit step in x dimension
  offs[10][1] = off2D(1, &start[0],
      &end[0],args[10].dat->size, args[10].stencil->stride) - offs[10][0];



  int off0_0 = offs[0][0];
  int off0_1 = offs[0][1];
  int dat0 = (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);
  int off1_0 = offs[1][0];
  int off1_1 = offs[1][1];
  int dat1 = (OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size);
  int off2_0 = offs[2][0];
  int off2_1 = offs[2][1];
  int dat2 = (OPS_soa ? args[2].dat->type_size : args[2].dat->elem_size);
  int off3_0 = offs[3][0];
  int off3_1 = offs[3][1];
  int dat3 = (OPS_soa ? args[3].dat->type_size : args[3].dat->elem_size);
  int off4_0 = offs[4][0];
  int off4_1 = offs[4][1];
  int dat4 = (OPS_soa ? args[4].dat->type_size : args[4].dat->elem_size);
  int off5_0 = offs[5][0];
  int off5_1 = offs[5][1];
  int dat5 = (OPS_soa ? args[5].dat->type_size : args[5].dat->elem_size);
  int off6_0 = offs[6][0];
  int off6_1 = offs[6][1];
  int dat6 = (OPS_soa ? args[6].dat->type_size : args[6].dat->elem_size);
  int off7_0 = offs[7][0];
  int off7_1 = offs[7][1];
  int dat7 = (OPS_soa ? args[7].dat->type_size : args[7].dat->elem_size);
  int off8_0 = offs[8][0];
  int off8_1 = offs[8][1];
  int dat8 = (OPS_soa ? args[8].dat->type_size : args[8].dat->elem_size);
  int off9_0 = offs[9][0];
  int off9_1 = offs[9][1];
  int dat9 = (OPS_soa ? args[9].dat->type_size : args[9].dat->elem_size);
  int off10_0 = offs[10][0];
  int off10_1 = offs[10][1];
  int dat10 = (OPS_soa ? args[10].dat->type_size : args[10].dat->elem_size);

  //set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset + (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size) * start[0] * args[0].stencil->stride[0];
  base0 = base0+ (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size) *
    args[0].dat->size[0] *
    start[1] * args[0].stencil->stride[1];
  p_a[0] = (char *)args[0].data + base0;

  int base1 = args[1].dat->base_offset + (OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size) * start[0] * args[1].stencil->stride[0];
  base1 = base1+ (OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size) *
    args[1].dat->size[0] *
    start[1] * args[1].stencil->stride[1];
  p_a[1] = (char *)args[1].data + base1;

  int base2 = args[2].dat->base_offset + (OPS_soa ? args[2].dat->type_size : args[2].dat->elem_size) * start[0] * args[2].stencil->stride[0];
  base2 = base2+ (OPS_soa ? args[2].dat->type_size : args[2].dat->elem_size) *
    args[2].dat->size[0] *
    start[1] * args[2].stencil->stride[1];
  p_a[2] = (char *)args[2].data + base2;

  int base3 = args[3].dat->base_offset + (OPS_soa ? args[3].dat->type_size : args[3].dat->elem_size) * start[0] * args[3].stencil->stride[0];
  base3 = base3+ (OPS_soa ? args[3].dat->type_size : args[3].dat->elem_size) *
    args[3].dat->size[0] *
    start[1] * args[3].stencil->stride[1];
  p_a[3] = (char *)args[3].data + base3;

  int base4 = args[4].dat->base_offset + (OPS_soa ? args[4].dat->type_size : args[4].dat->elem_size) * start[0] * args[4].stencil->stride[0];
  base4 = base4+ (OPS_soa ? args[4].dat->type_size : args[4].dat->elem_size) *
    args[4].dat->size[0] *
    start[1] * args[4].stencil->stride[1];
  p_a[4] = (char *)args[4].data + base4;

  int base5 = args[5].dat->base_offset + (OPS_soa ? args[5].dat->type_size : args[5].dat->elem_size) * start[0] * args[5].stencil->stride[0];
  base5 = base5+ (OPS_soa ? args[5].dat->type_size : args[5].dat->elem_size) *
    args[5].dat->size[0] *
    start[1] * args[5].stencil->stride[1];
  p_a[5] = (char *)args[5].data + base5;

  int base6 = args[6].dat->base_offset + (OPS_soa ? args[6].dat->type_size : args[6].dat->elem_size) * start[0] * args[6].stencil->stride[0];
  base6 = base6+ (OPS_soa ? args[6].dat->type_size : args[6].dat->elem_size) *
    args[6].dat->size[0] *
    start[1] * args[6].stencil->stride[1];
  p_a[6] = (char *)args[6].data + base6;

  int base7 = args[7].dat->base_offset + (OPS_soa ? args[7].dat->type_size : args[7].dat->elem_size) * start[0] * args[7].stencil->stride[0];
  base7 = base7+ (OPS_soa ? args[7].dat->type_size : args[7].dat->elem_size) *
    args[7].dat->size[0] *
    start[1] * args[7].stencil->stride[1];
  p_a[7] = (char *)args[7].data + base7;

  int base8 = args[8].dat->base_offset + (OPS_soa ? args[8].dat->type_size : args[8].dat->elem_size) * start[0] * args[8].stencil->stride[0];
  base8 = base8+ (OPS_soa ? args[8].dat->type_size : args[8].dat->elem_size) *
    args[8].dat->size[0] *
    start[1] * args[8].stencil->stride[1];
  p_a[8] = (char *)args[8].data + base8;

  int base9 = args[9].dat->base_offset + (OPS_soa ? args[9].dat->type_size : args[9].dat->elem_size) * start[0] * args[9].stencil->stride[0];
  base9 = base9+ (OPS_soa ? args[9].dat->type_size : args[9].dat->elem_size) *
    args[9].dat->size[0] *
    start[1] * args[9].stencil->stride[1];
  p_a[9] = (char *)args[9].data + base9;

  int base10 = args[10].dat->base_offset + (OPS_soa ? args[10].dat->type_size : args[10].dat->elem_size) * start[0] * args[10].stencil->stride[0];
  base10 = base10+ (OPS_soa ? args[10].dat->type_size : args[10].dat->elem_size) *
    args[10].dat->size[0] *
    start[1] * args[10].stencil->stride[1];
  p_a[10] = (char *)args[10].data + base10;


  //initialize global variable with the dimension of dats
  xdim0 = args[0].dat->size[0];
  xdim1 = args[1].dat->size[0];
  xdim2 = args[2].dat->size[0];
  xdim3 = args[3].dat->size[0];
  xdim4 = args[4].dat->size[0];
  xdim5 = args[5].dat->size[0];
  xdim6 = args[6].dat->size[0];
  xdim7 = args[7].dat->size[0];
  xdim8 = args[8].dat->size[0];
  xdim9 = args[9].dat->size[0];
  xdim10 = args[10].dat->size[0];

  //Halo Exchanges
  ops_H_D_exchanges_host(args, 11);
  ops_halo_exchanges(args,11,range);
  ops_H_D_exchanges_host(args, 11);

  if (OPS_diags > 1) {
    ops_timers_core(&c1,&t1);
    OPS_kernels[58].mpi_time += t1-t2;
  }

  int n_x;
  for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
    #pragma novector
    for( n_x=start[0]; n_x<start[0]+((end[0]-start[0])/SIMD_VEC)*SIMD_VEC; n_x+=SIMD_VEC ) {
      //call kernel function, passing in pointers to data -vectorised
      #pragma simd
      for ( int i=0; i<SIMD_VEC; i++ ){
        accelerate_kernel(  (double *)p_a[0]+ i*1*1, (double *)p_a[1]+ i*1*1, (double *)p_a[2]+ i*1*1,
           (double *)p_a[3]+ i*1*1, (double *)p_a[4]+ i*1*1, (double *)p_a[5]+ i*1*1, (double *)p_a[6]+ i*1*1,
           (double *)p_a[7]+ i*1*1, (double *)p_a[8]+ i*1*1, (double *)p_a[9]+ i*1*1, (double *)p_a[10]+ i*1*1 );

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
      p_a[8]= p_a[8] + (dat8 * off8_0)*SIMD_VEC;
      p_a[9]= p_a[9] + (dat9 * off9_0)*SIMD_VEC;
      p_a[10]= p_a[10] + (dat10 * off10_0)*SIMD_VEC;
    }

    for ( int n_x=start[0]+((end[0]-start[0])/SIMD_VEC)*SIMD_VEC; n_x<end[0]; n_x++ ){
      //call kernel function, passing in pointers to data - remainder
      accelerate_kernel(  (double *)p_a[0], (double *)p_a[1], (double *)p_a[2],
           (double *)p_a[3], (double *)p_a[4], (double *)p_a[5], (double *)p_a[6],
           (double *)p_a[7], (double *)p_a[8], (double *)p_a[9], (double *)p_a[10] );


      //shift pointers to data x direction
      p_a[0]= p_a[0] + (dat0 * off0_0);
      p_a[1]= p_a[1] + (dat1 * off1_0);
      p_a[2]= p_a[2] + (dat2 * off2_0);
      p_a[3]= p_a[3] + (dat3 * off3_0);
      p_a[4]= p_a[4] + (dat4 * off4_0);
      p_a[5]= p_a[5] + (dat5 * off5_0);
      p_a[6]= p_a[6] + (dat6 * off6_0);
      p_a[7]= p_a[7] + (dat7 * off7_0);
      p_a[8]= p_a[8] + (dat8 * off8_0);
      p_a[9]= p_a[9] + (dat9 * off9_0);
      p_a[10]= p_a[10] + (dat10 * off10_0);
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
    p_a[8]= p_a[8] + (dat8 * off8_1);
    p_a[9]= p_a[9] + (dat9 * off9_1);
    p_a[10]= p_a[10] + (dat10 * off10_1);
  }
  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[58].time += t2-t1;
  }
  ops_set_dirtybit_host(args, 11);
  ops_set_halo_dirtybit3(&args[2],range);
  ops_set_halo_dirtybit3(&args[4],range);
  ops_set_halo_dirtybit3(&args[8],range);

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c1,&t1);
    OPS_kernels[58].mpi_time += t1-t2;
    OPS_kernels[58].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[58].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[58].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[58].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_kernels[58].transfer += ops_compute_transfer(dim, start, end, &arg4);
    OPS_kernels[58].transfer += ops_compute_transfer(dim, start, end, &arg5);
    OPS_kernels[58].transfer += ops_compute_transfer(dim, start, end, &arg6);
    OPS_kernels[58].transfer += ops_compute_transfer(dim, start, end, &arg7);
    OPS_kernels[58].transfer += ops_compute_transfer(dim, start, end, &arg8);
    OPS_kernels[58].transfer += ops_compute_transfer(dim, start, end, &arg9);
    OPS_kernels[58].transfer += ops_compute_transfer(dim, start, end, &arg10);
  }
}
