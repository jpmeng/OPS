//
// auto-generated by ops.py
//

int xdim0_calc_dt_kernel_print;
int xdim1_calc_dt_kernel_print;
int xdim2_calc_dt_kernel_print;
int xdim3_calc_dt_kernel_print;
int xdim4_calc_dt_kernel_print;
int xdim5_calc_dt_kernel_print;


//user function



void calc_dt_kernel_print_c_wrapper(
  double * restrict xvel0_p,
  double * restrict yvel0_p,
  double * restrict density0_p,
  double * restrict energy0_p,
  double * restrict pressure_p,
  double * restrict soundspeed_p,
  double * restrict output_g,
  int x_size, int y_size) {
  double output_0 = output_g[0];
  double output_1 = output_g[1];
  double output_2 = output_g[2];
  double output_3 = output_g[3];
  double output_4 = output_g[4];
  double output_5 = output_g[5];
  double output_6 = output_g[6];
  double output_7 = output_g[7];
  double output_8 = output_g[8];
  double output_9 = output_g[9];
  double output_10 = output_g[10];
  double output_11 = output_g[11];
  #pragma omp parallel for reduction(+:output_0) reduction(+:output_1) reduction(+:output_2) reduction(+:output_3) reduction(+:output_4) reduction(+:output_5) reduction(+:output_6) reduction(+:output_7) reduction(+:output_8) reduction(+:output_9) reduction(+:output_10) reduction(+:output_11)
  for ( int n_y=0; n_y<y_size; n_y++ ){
    for ( int n_x=0; n_x<x_size; n_x++ ){
      double output[12];
      output[0] = ZERO_double;
      output[1] = ZERO_double;
      output[2] = ZERO_double;
      output[3] = ZERO_double;
      output[4] = ZERO_double;
      output[5] = ZERO_double;
      output[6] = ZERO_double;
      output[7] = ZERO_double;
      output[8] = ZERO_double;
      output[9] = ZERO_double;
      output[10] = ZERO_double;
      output[11] = ZERO_double;
      const ptr_double xvel0 = { xvel0_p + n_x*1 + n_y * xdim0_calc_dt_kernel_print*1, xdim0_calc_dt_kernel_print};
      const ptr_double yvel0 = { yvel0_p + n_x*1 + n_y * xdim1_calc_dt_kernel_print*1, xdim1_calc_dt_kernel_print};
      const ptr_double density0 = { density0_p + n_x*1 + n_y * xdim2_calc_dt_kernel_print*1, xdim2_calc_dt_kernel_print};
      const ptr_double energy0 = { energy0_p + n_x*1 + n_y * xdim3_calc_dt_kernel_print*1, xdim3_calc_dt_kernel_print};
      const ptr_double pressure = { pressure_p + n_x*1 + n_y * xdim4_calc_dt_kernel_print*1, xdim4_calc_dt_kernel_print};
      const ptr_double soundspeed = { soundspeed_p + n_x*1 + n_y * xdim5_calc_dt_kernel_print*1, xdim5_calc_dt_kernel_print};
      
  output[0] = OPS_ACC(xvel0, 1,0);
  output[1] = OPS_ACC(yvel0, 1,0);
  output[2] = OPS_ACC(xvel0, -1,0);
  output[3] = OPS_ACC(yvel0, -1,0);
  output[4] = OPS_ACC(xvel0, 0,1);
  output[5] = OPS_ACC(yvel0, 0,1);
  output[6] = OPS_ACC(xvel0, 0,-1);
  output[7] = OPS_ACC(yvel0, 0,-1);
  output[8] = OPS_ACC(density0, 0,0);
  output[9] = OPS_ACC(energy0, 0,0);
  output[10]= OPS_ACC(pressure, 0,0);
  output[11]= OPS_ACC(soundspeed, 0,0);


      output_0 +=output[0];
      output_1 +=output[1];
      output_2 +=output[2];
      output_3 +=output[3];
      output_4 +=output[4];
      output_5 +=output[5];
      output_6 +=output[6];
      output_7 +=output[7];
      output_8 +=output[8];
      output_9 +=output[9];
      output_10 +=output[10];
      output_11 +=output[11];
    }
  }
  output_g[0] = output_0;
  output_g[1] = output_1;
  output_g[2] = output_2;
  output_g[3] = output_3;
  output_g[4] = output_4;
  output_g[5] = output_5;
  output_g[6] = output_6;
  output_g[7] = output_7;
  output_g[8] = output_8;
  output_g[9] = output_9;
  output_g[10] = output_10;
  output_g[11] = output_11;
}
