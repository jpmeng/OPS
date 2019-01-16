//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_calc_dt_kernel_min;

//user function
inline 
void calc_dt_kernel_min(const ptr_double dt_min,
  double* dt_min_val) {
  *dt_min_val = MIN(*dt_min_val, OPS_ACC(dt_min, 0,0));

}


void calc_dt_kernel_min_c_wrapper(
  double *p_a0,
  double *p_a1,
  int x_size, int y_size) {
  double p_a1_0 = p_a1[0];
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0) reduction(min:p_a1_0)
  #pragma acc loop reduction(min:p_a1_0)
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop reduction(min:p_a1_0)
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      const ptr_double ptr0 = {  p_a0 + n_x*1*1 + n_y*xdim0_calc_dt_kernel_min*1*1, xdim0_calc_dt_kernel_min};
      calc_dt_kernel_min( ptr0,
           &p_a1_0 );

    }
  }
  p_a1[0] = p_a1_0;
}
