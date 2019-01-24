//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_reset_field_kernel2;
int ydim0_reset_field_kernel2;
int xdim1_reset_field_kernel2;
int ydim1_reset_field_kernel2;
int xdim2_reset_field_kernel2;
int ydim2_reset_field_kernel2;
int xdim3_reset_field_kernel2;
int ydim3_reset_field_kernel2;
int xdim4_reset_field_kernel2;
int ydim4_reset_field_kernel2;
int xdim5_reset_field_kernel2;
int ydim5_reset_field_kernel2;

//user function
#pragma acc routine
inline 
void reset_field_kernel2(ptr_double xvel0,
  const ptr_double xvel1,
  ptr_double yvel0,
  const ptr_double yvel1,
  ptr_double zvel0,
  const ptr_double zvel1) {

  OPS_ACC(xvel0, 0,0,0)  = OPS_ACC(xvel1, 0,0,0) ;
  OPS_ACC(yvel0, 0,0,0)  = OPS_ACC(yvel1, 0,0,0) ;
  OPS_ACC(zvel0, 0,0,0)  = OPS_ACC(zvel1, 0,0,0) ;
}


void reset_field_kernel2_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  double *p_a4,
  double *p_a5,
  int x_size, int y_size, int z_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2,p_a3,p_a4,p_a5)
  #pragma acc loop
  #endif
  for ( int n_z=0; n_z<z_size; n_z++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_y=0; n_y<y_size; n_y++ ){
      #ifdef OPS_GPU
      #pragma acc loop
      #endif
      for ( int n_x=0; n_x<x_size; n_x++ ){
        ptr_double ptr0 = {  p_a0 + n_x*1*1 + n_y*xdim0_reset_field_kernel2*1*1 + n_z*xdim0_reset_field_kernel2*ydim0_reset_field_kernel2*1*1, xdim0_reset_field_kernel2, ydim0_reset_field_kernel2};
        const ptr_double ptr1 = {  p_a1 + n_x*1*1 + n_y*xdim1_reset_field_kernel2*1*1 + n_z*xdim1_reset_field_kernel2*ydim1_reset_field_kernel2*1*1, xdim1_reset_field_kernel2, ydim1_reset_field_kernel2};
        ptr_double ptr2 = {  p_a2 + n_x*1*1 + n_y*xdim2_reset_field_kernel2*1*1 + n_z*xdim2_reset_field_kernel2*ydim2_reset_field_kernel2*1*1, xdim2_reset_field_kernel2, ydim2_reset_field_kernel2};
        const ptr_double ptr3 = {  p_a3 + n_x*1*1 + n_y*xdim3_reset_field_kernel2*1*1 + n_z*xdim3_reset_field_kernel2*ydim3_reset_field_kernel2*1*1, xdim3_reset_field_kernel2, ydim3_reset_field_kernel2};
        ptr_double ptr4 = {  p_a4 + n_x*1*1 + n_y*xdim4_reset_field_kernel2*1*1 + n_z*xdim4_reset_field_kernel2*ydim4_reset_field_kernel2*1*1, xdim4_reset_field_kernel2, ydim4_reset_field_kernel2};
        const ptr_double ptr5 = {  p_a5 + n_x*1*1 + n_y*xdim5_reset_field_kernel2*1*1 + n_z*xdim5_reset_field_kernel2*ydim5_reset_field_kernel2*1*1, xdim5_reset_field_kernel2, ydim5_reset_field_kernel2};
        reset_field_kernel2( ptr0,
          ptr1,
          ptr2,
          ptr3,
          ptr4,
          ptr5 );

      }
    }
  }
}
