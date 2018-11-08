//
// auto-generated by ops.py
//

int xdim0_update_halo_kernel1_l1;
int xdim1_update_halo_kernel1_l1;
int xdim2_update_halo_kernel1_l1;
int xdim3_update_halo_kernel1_l1;
int xdim4_update_halo_kernel1_l1;
int xdim5_update_halo_kernel1_l1;
int xdim6_update_halo_kernel1_l1;


#define OPS_ACC0(x,y) (n_x*1 + x + (n_y*1+(y))*xdim0_update_halo_kernel1_l1)
#define OPS_ACC1(x,y) (n_x*1 + x + (n_y*1+(y))*xdim1_update_halo_kernel1_l1)
#define OPS_ACC2(x,y) (n_x*1 + x + (n_y*1+(y))*xdim2_update_halo_kernel1_l1)
#define OPS_ACC3(x,y) (n_x*1 + x + (n_y*1+(y))*xdim3_update_halo_kernel1_l1)
#define OPS_ACC4(x,y) (n_x*1 + x + (n_y*1+(y))*xdim4_update_halo_kernel1_l1)
#define OPS_ACC5(x,y) (n_x*1 + x + (n_y*1+(y))*xdim5_update_halo_kernel1_l1)
#define OPS_ACC6(x,y) (n_x*1 + x + (n_y*1+(y))*xdim6_update_halo_kernel1_l1)
//user function



void update_halo_kernel1_l1_c_wrapper(
  double * restrict density0,
  double * restrict density1,
  double * restrict energy0,
  double * restrict energy1,
  double * restrict pressure,
  double * restrict viscosity,
  double * restrict soundspeed,
  const int * restrict fields,
  int x_size, int y_size) {
  #pragma omp parallel for
  for ( int n_y=0; n_y<y_size; n_y++ ){
    for ( int n_x=0; n_x<x_size; n_x++ ){
      
  if(fields[FIELD_DENSITY0] == 1) density0(0,0) = density0(1,0);
  if(fields[FIELD_DENSITY1] == 1) density1(0,0) = density1(1,0);
  if(fields[FIELD_ENERGY0] == 1) energy0(0,0) = energy0(1,0);
  if(fields[FIELD_ENERGY1] == 1) energy1(0,0) = energy1(1,0);
  if(fields[FIELD_PRESSURE] == 1) pressure(0,0) = pressure(1,0);
  if(fields[FIELD_VISCOSITY] == 1) viscosity(0,0) = viscosity(1,0);
  if(fields[FIELD_SOUNDSPEED] == 1) soundspeed(0,0) = soundspeed(1,0);


    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6

