//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_field_summary_kernel;
int xdim1_field_summary_kernel;
int xdim2_field_summary_kernel;
int xdim3_field_summary_kernel;
int xdim4_field_summary_kernel;
int xdim5_field_summary_kernel;

//user function
inline 
void field_summary_kernel(const ptr_double volume,
  const ptr_double density0,
  const ptr_double energy0,
  const ptr_double pressure,
  const ptr_double xvel0,
  const ptr_double yvel0,
  double *vol,
  double *mass,
  double *ie,
  double *ke,
  double *press) {

  double vsqrd, cell_vol, cell_mass;



  vsqrd = 0.0;
  vsqrd = vsqrd + 0.25 * ( OPS_ACC(xvel0, 0,0) * OPS_ACC(xvel0, 0,0) + OPS_ACC(yvel0, 0,0) * OPS_ACC(yvel0, 0,0));
  vsqrd = vsqrd + 0.25 * ( OPS_ACC(xvel0, 1,0) * OPS_ACC(xvel0, 1,0) + OPS_ACC(yvel0, 1,0) * OPS_ACC(yvel0, 1,0));
  vsqrd = vsqrd + 0.25 * ( OPS_ACC(xvel0, 0,1) * OPS_ACC(xvel0, 0,1) + OPS_ACC(yvel0, 0,1) * OPS_ACC(yvel0, 0,1));
  vsqrd = vsqrd + 0.25 * ( OPS_ACC(xvel0, 1,1) * OPS_ACC(xvel0, 1,1) + OPS_ACC(yvel0, 1,1) * OPS_ACC(yvel0, 1,1));

  cell_vol = OPS_ACC(volume, 0,0);
  cell_mass = cell_vol * OPS_ACC(density0, 0,0);
  *vol = *vol + cell_vol;
  *mass = *mass + cell_mass;
  *ie = *ie + cell_mass * OPS_ACC(energy0, 0,0);
  *ke = *ke + cell_mass * 0.5 * vsqrd;
  *press = *press + cell_vol * OPS_ACC(pressure, 0,0);

}


void field_summary_kernel_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  double *p_a4,
  double *p_a5,
  double *p_a6,
  double *p_a7,
  double *p_a8,
  double *p_a9,
  double *p_a10,
  int x_size, int y_size) {
  double p_a6_0 = p_a6[0];
  double p_a7_0 = p_a7[0];
  double p_a8_0 = p_a8[0];
  double p_a9_0 = p_a9[0];
  double p_a10_0 = p_a10[0];
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2,p_a3,p_a4,p_a5) reduction(+:p_a6_0) reduction(+:p_a7_0) reduction(+:p_a8_0) reduction(+:p_a9_0) reduction(+:p_a10_0)
  #pragma acc loop reduction(+:p_a6_0) reduction(+:p_a7_0) reduction(+:p_a8_0) reduction(+:p_a9_0) reduction(+:p_a10_0)
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop reduction(+:p_a6_0) reduction(+:p_a7_0) reduction(+:p_a8_0) reduction(+:p_a9_0) reduction(+:p_a10_0)
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      const ptr_double ptr0 = {  p_a0 + n_x*1*1 + n_y*xdim0_field_summary_kernel*1*1, xdim0_field_summary_kernel};
      const ptr_double ptr1 = {  p_a1 + n_x*1*1 + n_y*xdim1_field_summary_kernel*1*1, xdim1_field_summary_kernel};
      const ptr_double ptr2 = {  p_a2 + n_x*1*1 + n_y*xdim2_field_summary_kernel*1*1, xdim2_field_summary_kernel};
      const ptr_double ptr3 = {  p_a3 + n_x*1*1 + n_y*xdim3_field_summary_kernel*1*1, xdim3_field_summary_kernel};
      const ptr_double ptr4 = {  p_a4 + n_x*1*1 + n_y*xdim4_field_summary_kernel*1*1, xdim4_field_summary_kernel};
      const ptr_double ptr5 = {  p_a5 + n_x*1*1 + n_y*xdim5_field_summary_kernel*1*1, xdim5_field_summary_kernel};
      field_summary_kernel( ptr0,
          ptr1,ptr2,
          ptr3,ptr4,
          ptr5, &p_a6_0,
           &p_a7_0, &p_a8_0,
           &p_a9_0, &p_a10_0 );

    }
  }
  p_a6[0] = p_a6_0;
  p_a7[0] = p_a7_0;
  p_a8[0] = p_a8_0;
  p_a9[0] = p_a9_0;
  p_a10[0] = p_a10_0;
}
