//
// auto-generated by ops.py
//

int xdim0_advec_mom_kernel_y2;
int xdim1_advec_mom_kernel_y2;
int xdim2_advec_mom_kernel_y2;
int xdim3_advec_mom_kernel_y2;


//user function



void advec_mom_kernel_y2_c_wrapper(
  double * restrict pre_vol_p,
  double * restrict post_vol_p,
  double * restrict volume_p,
  double * restrict vol_flux_x_p,
  int x_size, int y_size) {
  #pragma omp parallel for
  for ( int n_y=0; n_y<y_size; n_y++ ){
    for ( int n_x=0; n_x<x_size; n_x++ ){
      ptr_double pre_vol = { pre_vol_p + n_x*1 + n_y * xdim0_advec_mom_kernel_y2*1, xdim0_advec_mom_kernel_y2};
      ptr_double post_vol = { post_vol_p + n_x*1 + n_y * xdim1_advec_mom_kernel_y2*1, xdim1_advec_mom_kernel_y2};
      const ptr_double volume = { volume_p + n_x*1 + n_y * xdim2_advec_mom_kernel_y2*1, xdim2_advec_mom_kernel_y2};
      const ptr_double vol_flux_x = { vol_flux_x_p + n_x*1 + n_y * xdim3_advec_mom_kernel_y2*1, xdim3_advec_mom_kernel_y2};
      

  OPS_ACC(post_vol, 0,0)  = OPS_ACC(volume, 0,0) ;
  OPS_ACC(pre_vol, 0,0)   = OPS_ACC(post_vol, 0,0)  + OPS_ACC(vol_flux_x, 1,0) - OPS_ACC(vol_flux_x, 0,0);


    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3

