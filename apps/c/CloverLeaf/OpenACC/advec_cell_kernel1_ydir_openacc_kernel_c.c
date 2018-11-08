//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_advec_cell_kernel1_ydir;
int xdim1_advec_cell_kernel1_ydir;
int xdim2_advec_cell_kernel1_ydir;
int xdim3_advec_cell_kernel1_ydir;
int xdim4_advec_cell_kernel1_ydir;


#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4


#define OPS_ACC0(x,y) (x+xdim0_advec_cell_kernel1_ydir*(y))
#define OPS_ACC1(x,y) (x+xdim1_advec_cell_kernel1_ydir*(y))
#define OPS_ACC2(x,y) (x+xdim2_advec_cell_kernel1_ydir*(y))
#define OPS_ACC3(x,y) (x+xdim3_advec_cell_kernel1_ydir*(y))
#define OPS_ACC4(x,y) (x+xdim4_advec_cell_kernel1_ydir*(y))

//user function

inline void advec_cell_kernel1_ydir( ACC<double> &pre_vol, ACC<double> &post_vol, const ACC<double> &volume,
                        const ACC<double> &vol_flux_x, const ACC<double> &vol_flux_y) {

  pre_vol(0,0) = volume(0,0) + ( vol_flux_y(0,1) - vol_flux_y(0,0) +
                           vol_flux_x(1,0) - vol_flux_x(0,0));
  post_vol(0,0) = pre_vol(0,0) - ( vol_flux_y(0,1) - vol_flux_y(0,0));

}


#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4



void advec_cell_kernel1_ydir_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  double *p_a4,
  int x_size, int y_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2,p_a3,p_a4)
  #pragma acc loop
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      advec_cell_kernel1_ydir(  p_a0 + n_x*1*1 + n_y*xdim0_advec_cell_kernel1_ydir*1*1,
           p_a1 + n_x*1*1 + n_y*xdim1_advec_cell_kernel1_ydir*1*1, p_a2 + n_x*1*1 + n_y*xdim2_advec_cell_kernel1_ydir*1*1,
           p_a3 + n_x*1*1 + n_y*xdim3_advec_cell_kernel1_ydir*1*1, p_a4 + n_x*1*1 + n_y*xdim4_advec_cell_kernel1_ydir*1*1 );

    }
  }
}
