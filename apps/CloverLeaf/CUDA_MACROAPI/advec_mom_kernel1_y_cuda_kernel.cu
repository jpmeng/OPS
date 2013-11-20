//
// auto-generated by ops.py on 2013-11-20 11:42
//

__constant__ int xdim0_advec_mom_kernel1_y;
__constant__ int xdim1_advec_mom_kernel1_y;
__constant__ int xdim2_advec_mom_kernel1_y;
__constant__ int xdim3_advec_mom_kernel1_y;
__constant__ int xdim4_advec_mom_kernel1_y;
__constant__ int xdim5_advec_mom_kernel1_y;

#define OPS_ACC0(x,y) (x+xdim0_advec_mom_kernel1_y*(y))
#define OPS_ACC1(x,y) (x+xdim1_advec_mom_kernel1_y*(y))
#define OPS_ACC2(x,y) (x+xdim2_advec_mom_kernel1_y*(y))
#define OPS_ACC3(x,y) (x+xdim3_advec_mom_kernel1_y*(y))
#define OPS_ACC4(x,y) (x+xdim4_advec_mom_kernel1_y*(y))
#define OPS_ACC5(x,y) (x+xdim5_advec_mom_kernel1_y*(y))

//user function
__device__

inline void advec_mom_kernel1_y( const double *node_flux, const double *node_mass_pre,
                        double *advec_vel, double *mom_flux,
                        const double *celldy, const double *vel1) {

  //node_flux accessed with: {0,0}
  //node_mass_pre accessed with: {0,0, 0,1}
  //celldy is accessed with {0,0, 0,1, 0,-1, 0,-2} striding in y
  //vel1 is accessed with {0,0, 0,1, 0,2, 0,-1}

  double sigma, wind, width;
  double sigma2, wind2;
  double vdiffuw, vdiffdw, auw, adw, limiter;
  double vdiffuw2, vdiffdw2, auw2, limiter2;

  sigma = fabs(node_flux[OPS_ACC0(0,0)])/node_mass_pre[OPS_ACC1(0,1)];
  sigma2 = fabs(node_flux[OPS_ACC0(0,0)])/node_mass_pre[OPS_ACC1(0,0)];

  width = celldy[OPS_ACC4(0,0)];
  vdiffuw = vel1[OPS_ACC5(0,1)] - vel1[OPS_ACC5(0,2)];
  vdiffdw = vel1[OPS_ACC5(0,0)] - vel1[OPS_ACC5(0,1)];
  vdiffuw2 = vel1[OPS_ACC5(0,0)] - vel1[OPS_ACC5(0,-1)];
  vdiffdw2 = -vdiffdw;

  auw = fabs(vdiffuw);
  adw = fabs(vdiffdw);
  auw2 = fabs(vdiffuw2);
  wind = 1.0;
  wind2 = 1.0;

  if(vdiffdw <= 0.0) wind = -1.0;
  if(vdiffdw2 <= 0.0) wind2 = -1.0;

  limiter = wind * MIN( width * ( (2.0 - sigma) * adw/width + (1.0 + sigma) *
                        auw/celldy[OPS_ACC4(0,1)] )/6.0 , MIN(auw, adw) );
  limiter2= wind2* MIN( width * ( (2.0 - sigma2) * adw/width + (1.0 + sigma2) *
                        auw2/celldy[OPS_ACC4(0,-1)] )/6.0, MIN(auw2,adw) );

  if((vdiffuw * vdiffdw) <= 0.0) limiter = 0.0;
  if((vdiffuw2 * vdiffdw2) <= 0.0) limiter2 = 0.0;

  if( (node_flux[OPS_ACC0(0,0)]) < 0.0) {
    advec_vel[OPS_ACC2(0,0)] = vel1[OPS_ACC5(0,1)] + (1.0 - sigma) * limiter;
  }
  else {
    advec_vel[OPS_ACC2(0,0)] = vel1[OPS_ACC5(0,0)] + (1.0 - sigma2) * limiter2;
  }

  mom_flux[OPS_ACC3(0,0)] = advec_vel[OPS_ACC2(0,0)] * node_flux[OPS_ACC0(0,0)];
}


#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5


__global__ void ops_advec_mom_kernel1_y(
const double* __restrict arg0,
const double* __restrict arg1,
double* __restrict arg2,
double* __restrict arg3,
const double* __restrict arg4,
const double* __restrict arg5,
int size0,
int size1 ){


  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 1 * xdim0_advec_mom_kernel1_y;
  arg1 += idx_x * 1 + idx_y * 1 * xdim1_advec_mom_kernel1_y;
  arg2 += idx_x * 1 + idx_y * 1 * xdim2_advec_mom_kernel1_y;
  arg3 += idx_x * 1 + idx_y * 1 * xdim3_advec_mom_kernel1_y;
  arg4 += idx_x * 0 + idx_y * 1 * xdim4_advec_mom_kernel1_y;
  arg5 += idx_x * 1 + idx_y * 1 * xdim5_advec_mom_kernel1_y;

  if (idx_x < size0 && idx_y < size1) {
    advec_mom_kernel1_y(arg0, arg1, arg2, arg3,
                   arg4, arg5);
  }

}

// host stub function
void ops_par_loop_advec_mom_kernel1_y(char const *name, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5) {

  ops_arg args[6] = { arg0, arg1, arg2, arg3, arg4, arg5};


  int x_size = range[1]-range[0];
  int y_size = range[3]-range[2];

  int xdim0 = args[0].dat->block_size[0];
  int xdim1 = args[1].dat->block_size[0];
  int xdim2 = args[2].dat->block_size[0];
  int xdim3 = args[3].dat->block_size[0];
  int xdim4 = args[4].dat->block_size[0];
  int xdim5 = args[5].dat->block_size[0];

  ops_timing_realloc(25);
  if (OPS_kernels[25].count == 0) {
    cudaMemcpyToSymbol( xdim0_advec_mom_kernel1_y, &xdim0, sizeof(int) );
    cudaMemcpyToSymbol( xdim1_advec_mom_kernel1_y, &xdim1, sizeof(int) );
    cudaMemcpyToSymbol( xdim2_advec_mom_kernel1_y, &xdim2, sizeof(int) );
    cudaMemcpyToSymbol( xdim3_advec_mom_kernel1_y, &xdim3, sizeof(int) );
    cudaMemcpyToSymbol( xdim4_advec_mom_kernel1_y, &xdim4, sizeof(int) );
    cudaMemcpyToSymbol( xdim5_advec_mom_kernel1_y, &xdim5, sizeof(int) );
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, 1);
  dim3 block(OPS_block_size_x,OPS_block_size_y,1);




  char *p_a[6];


  //set up initial pointers
  p_a[0] = &args[0].data_d[
  + args[0].dat->size * args[0].dat->block_size[0] * ( range[2] * 1 - args[0].dat->offset[1] )
  + args[0].dat->size * ( range[0] * 1 - args[0].dat->offset[0] ) ];

  p_a[1] = &args[1].data_d[
  + args[1].dat->size * args[1].dat->block_size[0] * ( range[2] * 1 - args[1].dat->offset[1] )
  + args[1].dat->size * ( range[0] * 1 - args[1].dat->offset[0] ) ];

  p_a[2] = &args[2].data_d[
  + args[2].dat->size * args[2].dat->block_size[0] * ( range[2] * 1 - args[2].dat->offset[1] )
  + args[2].dat->size * ( range[0] * 1 - args[2].dat->offset[0] ) ];

  p_a[3] = &args[3].data_d[
  + args[3].dat->size * args[3].dat->block_size[0] * ( range[2] * 1 - args[3].dat->offset[1] )
  + args[3].dat->size * ( range[0] * 1 - args[3].dat->offset[0] ) ];

  p_a[4] = &args[4].data_d[
  + args[4].dat->size * args[4].dat->block_size[0] * ( range[2] * 1 - args[4].dat->offset[1] )
  + args[4].dat->size * ( range[0] * 0 - args[4].dat->offset[0] ) ];

  p_a[5] = &args[5].data_d[
  + args[5].dat->size * args[5].dat->block_size[0] * ( range[2] * 1 - args[5].dat->offset[1] )
  + args[5].dat->size * ( range[0] * 1 - args[5].dat->offset[0] ) ];


  ops_halo_exchanges_cuda(args, 6);


  //call kernel wrapper function, passing in pointers to data
  ops_advec_mom_kernel1_y<<<grid, block >>> (  (double *)p_a[0], (double *)p_a[1],
           (double *)p_a[2], (double *)p_a[3],
           (double *)p_a[4], (double *)p_a[5],x_size, y_size);

  ops_set_dirtybit_cuda(args, 6);
  OPS_kernels[25].count++;
}
