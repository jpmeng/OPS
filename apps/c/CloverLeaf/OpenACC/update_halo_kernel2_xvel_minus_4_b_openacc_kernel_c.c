//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_update_halo_kernel2_xvel_minus_4_b;
int xdim1_update_halo_kernel2_xvel_minus_4_b;

//user function

inline void update_halo_kernel2_xvel_minus_4_b(ptr_double xvel0,
  ptr_double xvel1,
  const int* fields)
{
  if(fields[FIELD_XVEL0] == 1) OPS_ACC(xvel0, 0,0) = -OPS_ACC(xvel0, -4,0);
  if(fields[FIELD_XVEL1] == 1) OPS_ACC(xvel1, 0,0) = -OPS_ACC(xvel1, -4,0);
}


void update_halo_kernel2_xvel_minus_4_b_c_wrapper(
  double *p_a0,
  double *p_a1,
  int *p_a2,
  int x_size, int y_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2)
  #pragma acc loop
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      ptr_double ptr0 = {  p_a0 + n_x*1*1 + n_y*xdim0_update_halo_kernel2_xvel_minus_4_b*1*1, xdim0_update_halo_kernel2_xvel_minus_4_b};
      ptr_double ptr1 = {  p_a1 + n_x*1*1 + n_y*xdim1_update_halo_kernel2_xvel_minus_4_b*1*1, xdim1_update_halo_kernel2_xvel_minus_4_b};
      update_halo_kernel2_xvel_minus_4_b( ptr0,
          ptr1, p_a2 );

    }
  }
}
