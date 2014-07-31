//
// auto-generated by ops.py on 2014-07-31 17:05
//

#include "./OpenACC/clover_leaf_common.h"

#define OPS_GPU

int xdim0_calc_dt_kernel_get;
int ydim0_calc_dt_kernel_get;
int xdim1_calc_dt_kernel_get;
int ydim1_calc_dt_kernel_get;
int xdim4_calc_dt_kernel_get;
int ydim4_calc_dt_kernel_get;

#define OPS_ACC0(x,y,z) (x+xdim0_calc_dt_kernel_get*(y)+xdim0_calc_dt_kernel_get*ydim0_calc_dt_kernel_get*(z))
#define OPS_ACC1(x,y,z) (x+xdim1_calc_dt_kernel_get*(y)+xdim1_calc_dt_kernel_get*ydim1_calc_dt_kernel_get*(z))
#define OPS_ACC4(x,y,z) (x+xdim4_calc_dt_kernel_get*(y)+xdim4_calc_dt_kernel_get*ydim4_calc_dt_kernel_get*(z))

//user function
inline 
void calc_dt_kernel_get(const double* cellx, const double* celly, double* xl_pos, double* yl_pos, const double *cellz, double *zl_pos) {
  *xl_pos = cellx[OPS_ACC0(0,0,0)];
  *yl_pos = celly[OPS_ACC1(0,0,0)];
  *zl_pos = cellz[OPS_ACC4(0,0,0)];
}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC4


void calc_dt_kernel_get_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  double *p_a4,
  double *p_a5,
  int x_size, int y_size, int z_size) {
  double p_a2_l = *p_a2;
  double p_a3_l = *p_a3;
  double p_a5_l = *p_a5;
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a4) reduction(+:p_a2_l) reduction(+:p_a3_l) reduction(+:p_a5_l)
  #pragma acc loop reduction(+:p_a2_l) reduction(+:p_a3_l) reduction(+:p_a5_l)
  #endif
  for ( int n_z=0; n_z<z_size; n_z++ ){
    #ifdef OPS_GPU
    #pragma acc loop reduction(+:p_a2_l) reduction(+:p_a3_l) reduction(+:p_a5_l)
    #endif
    for ( int n_y=0; n_y<y_size; n_y++ ){
      #ifdef OPS_GPU
      #pragma acc loop reduction(+:p_a2_l) reduction(+:p_a3_l) reduction(+:p_a5_l)
      #endif
      for ( int n_x=0; n_x<x_size; n_x++ ){
        calc_dt_kernel_get(  p_a0 + n_x*1 + n_y*xdim0_calc_dt_kernel_get*0 + n_z*xdim0_calc_dt_kernel_get*ydim0_calc_dt_kernel_get*0,
           p_a1 + n_x*0 + n_y*xdim1_calc_dt_kernel_get*1 + n_z*xdim1_calc_dt_kernel_get*ydim1_calc_dt_kernel_get*0,
           &p_a2_l,
           &p_a3_l,
           p_a4 + n_x*0 + n_y*xdim4_calc_dt_kernel_get*0 + n_z*xdim4_calc_dt_kernel_get*ydim4_calc_dt_kernel_get*1,
           &p_a5_l );

      }
    }
  }
  *p_a2 = p_a2_l;
  *p_a3 = p_a3_l;
  *p_a5 = p_a5_l;
}
