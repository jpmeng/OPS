//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_update_halo_kernel1_b2;
int xdim1_update_halo_kernel1_b2;
int xdim2_update_halo_kernel1_b2;
int xdim3_update_halo_kernel1_b2;
int xdim4_update_halo_kernel1_b2;
int xdim5_update_halo_kernel1_b2;
int xdim6_update_halo_kernel1_b2;


#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6


#define OPS_ACC0(x,y) (x+xdim0_update_halo_kernel1_b2*(y))
#define OPS_ACC1(x,y) (x+xdim1_update_halo_kernel1_b2*(y))
#define OPS_ACC2(x,y) (x+xdim2_update_halo_kernel1_b2*(y))
#define OPS_ACC3(x,y) (x+xdim3_update_halo_kernel1_b2*(y))
#define OPS_ACC4(x,y) (x+xdim4_update_halo_kernel1_b2*(y))
#define OPS_ACC5(x,y) (x+xdim5_update_halo_kernel1_b2*(y))
#define OPS_ACC6(x,y) (x+xdim6_update_halo_kernel1_b2*(y))

//user function

inline void update_halo_kernel1_b2(ACC<double> &density0, ACC<double> &density1,
                          ACC<double> &energy0, ACC<double> &energy1,
                          ACC<double> &pressure, ACC<double> &viscosity,
                          ACC<double> &soundspeed, const int* fields) {
  if(fields[FIELD_DENSITY0] == 1) density0(0,0) = density0(0,3);
  if(fields[FIELD_DENSITY1] == 1) density1(0,0) = density1(0,3);
  if(fields[FIELD_ENERGY0] == 1) energy0(0,0) = energy0(0,3);
  if(fields[FIELD_ENERGY1] == 1) energy1(0,0) = energy1(0,3);
  if(fields[FIELD_PRESSURE] == 1) pressure(0,0) = pressure(0,3);
  if(fields[FIELD_VISCOSITY] == 1) viscosity(0,0) = viscosity(0,3);
  if(fields[FIELD_SOUNDSPEED] == 1) soundspeed(0,0) = soundspeed(0,3);

}


#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6



void update_halo_kernel1_b2_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  double *p_a4,
  double *p_a5,
  double *p_a6,
  int *p_a7,
  int x_size, int y_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2,p_a3,p_a4,p_a5,p_a6,p_a7)
  #pragma acc loop
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      update_halo_kernel1_b2(  p_a0 + n_x*1*1 + n_y*xdim0_update_halo_kernel1_b2*1*1,
           p_a1 + n_x*1*1 + n_y*xdim1_update_halo_kernel1_b2*1*1, p_a2 + n_x*1*1 + n_y*xdim2_update_halo_kernel1_b2*1*1,
           p_a3 + n_x*1*1 + n_y*xdim3_update_halo_kernel1_b2*1*1, p_a4 + n_x*1*1 + n_y*xdim4_update_halo_kernel1_b2*1*1,
           p_a5 + n_x*1*1 + n_y*xdim5_update_halo_kernel1_b2*1*1, p_a6 + n_x*1*1 + n_y*xdim6_update_halo_kernel1_b2*1*1,
           p_a7 );

    }
  }
}
