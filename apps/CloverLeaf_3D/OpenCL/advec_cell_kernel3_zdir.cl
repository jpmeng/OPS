//
// auto-generated by ops.py on 2014-07-31 17:05
//


#pragma OPENCL EXTENSION cl_khr_fp64:enable

#include "user_types.h"
#include "ops_opencl_reduction.h"

#ifndef MIN
#define MIN(a,b) ((a<b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) ((a>b) ? (a) : (b))
#endif
#ifndef SIGN
#define SIGN(a,b) ((b<0.0) ? (a*(-1)) : (a))
#endif
#define OPS_READ 0
#define OPS_WRITE 1
#define OPS_RW 2
#define OPS_INC 3
#define OPS_MIN 4
#define OPS_MAX 5
#define ZERO_double 0.0;
#define INFINITY_double INFINITY;
#define ZERO_float 0.0f;
#define INFINITY_float INFINITY;
#define ZERO_int 0;
#define INFINITY_int INFINITY;
#define ZERO_uint 0;
#define INFINITY_uint INFINITY;
#define ZERO_ll 0;
#define INFINITY_ll INFINITY;
#define ZERO_ull 0;
#define INFINITY_ull INFINITY;
#define ZERO_bool 0;
#define OPS_ACC0(x,y,z) (x+xdim0_advec_cell_kernel3_zdir*(y)+xdim0_advec_cell_kernel3_zdir*ydim0_advec_cell_kernel3_zdir*(z))
#define OPS_ACC1(x,y,z) (x+xdim1_advec_cell_kernel3_zdir*(y)+xdim1_advec_cell_kernel3_zdir*ydim1_advec_cell_kernel3_zdir*(z))
#define OPS_ACC2(x,y,z) (x+xdim2_advec_cell_kernel3_zdir*(y)+xdim2_advec_cell_kernel3_zdir*ydim2_advec_cell_kernel3_zdir*(z))
#define OPS_ACC3(x,y,z) (x+xdim3_advec_cell_kernel3_zdir*(y)+xdim3_advec_cell_kernel3_zdir*ydim3_advec_cell_kernel3_zdir*(z))
#define OPS_ACC4(x,y,z) (x+xdim4_advec_cell_kernel3_zdir*(y)+xdim4_advec_cell_kernel3_zdir*ydim4_advec_cell_kernel3_zdir*(z))
#define OPS_ACC5(x,y,z) (x+xdim5_advec_cell_kernel3_zdir*(y)+xdim5_advec_cell_kernel3_zdir*ydim5_advec_cell_kernel3_zdir*(z))
#define OPS_ACC6(x,y,z) (x+xdim6_advec_cell_kernel3_zdir*(y)+xdim6_advec_cell_kernel3_zdir*ydim6_advec_cell_kernel3_zdir*(z))
#define OPS_ACC7(x,y,z) (x+xdim7_advec_cell_kernel3_zdir*(y)+xdim7_advec_cell_kernel3_zdir*ydim7_advec_cell_kernel3_zdir*(z))


//user function
inline void advec_cell_kernel3_zdir( const __global double * restrict vol_flux_z, const __global double * restrict pre_vol, const __global int * restrict zz, 
const __global double * restrict vertexdz, const __global double * restrict density1, const __global double * restrict energy1, __global double * restrict mass_flux_z, 
__global double * restrict ener_flux, 
  const field_type field)

  {

  double sigma, sigmat, sigmav, sigmam, sigma3, sigma4;
  double diffuw, diffdw, limiter;
  double one_by_six = 1.0/6.0;

  int z_max=field.z_max;

  int upwind,donor,downwind,dif;

  if(vol_flux_z[OPS_ACC0(0,0,0)] > 0.0) {
    upwind   = -2;
    donor    = -1;
    downwind = 0;
    dif      = donor;
  }
  else if (zz[OPS_ACC2(0,0,1)] < z_max+2-2) {
    upwind   = 1;
    donor    = 0;
    downwind = -1;
    dif      = upwind;
  } else {
    upwind   = 0;
    donor    = 0;
    downwind = -1;
    dif      = upwind;
  }

  sigmat = fabs(vol_flux_z[OPS_ACC0(0,0,0)])/pre_vol[OPS_ACC1(0,0,donor)];
  sigma3 = (1.0 + sigmat)*(vertexdz[OPS_ACC3(0,0,0)]/vertexdz[OPS_ACC3(0,0,dif)]);
  sigma4 = 2.0 - sigmat;

  sigma = sigmat;
  sigmav = sigmat;

  diffuw = density1[OPS_ACC4(0,0,donor)] - density1[OPS_ACC4(0,0,upwind)];
  diffdw = density1[OPS_ACC4(0,0,downwind)] - density1[OPS_ACC4(0,0,donor)];

  if( (diffuw*diffdw) > 0.0)
    limiter=(1.0 - sigmav) * SIGN(1.0 , diffdw) *
    MIN( MIN(fabs(diffuw), fabs(diffdw)),
    one_by_six * (sigma3*fabs(diffuw) + sigma4 * fabs(diffdw)));
  else
    limiter=0.0;

  mass_flux_z[OPS_ACC6(0,0,0)] = vol_flux_z[OPS_ACC0(0,0,0)] * ( density1[OPS_ACC4(0,0,donor)] + limiter );

  sigmam = fabs(mass_flux_z[OPS_ACC6(0,0,0)])/( density1[OPS_ACC4(0,0,donor)] * pre_vol[OPS_ACC1(0,0,donor)]);
  diffuw = energy1[OPS_ACC5(0,0,donor)] - energy1[OPS_ACC5(0,0,upwind)];
  diffdw = energy1[OPS_ACC5(0,0,downwind)] - energy1[OPS_ACC5(0,0,donor)];

  if( (diffuw*diffdw) > 0.0)
    limiter = (1.0 - sigmam) * SIGN(1.0,diffdw) *
    MIN( MIN(fabs(diffuw), fabs(diffdw)),
    one_by_six * (sigma3 * fabs(diffuw) + sigma4 * fabs(diffdw)));
  else
    limiter=0.0;

  ener_flux[OPS_ACC7(0,0,0)] = mass_flux_z[OPS_ACC6(0,0,0)] * ( energy1[OPS_ACC5(0,0,donor)] + limiter );
}



 #undef OPS_ACC0
 #undef OPS_ACC1
 #undef OPS_ACC2
 #undef OPS_ACC3
 #undef OPS_ACC4
 #undef OPS_ACC5
 #undef OPS_ACC6
 #undef OPS_ACC7


 __kernel void ops_advec_cell_kernel3_zdir(
 __global const double* restrict arg0,
 __global const double* restrict arg1,
 __global const int* restrict arg2,
 __global const double* restrict arg3,
 __global const double* restrict arg4,
 __global const double* restrict arg5,
 __global double* restrict arg6,
 __global double* restrict arg7,
 __constant const struct field_type * restrict field,
 const int base0,
 const int base1,
 const int base2,
 const int base3,
 const int base4,
 const int base5,
 const int base6,
 const int base7,
 const int size0,
 const int size1,
 const int size2 ){


   int idx_z = get_global_id(2);
   int idx_y = get_global_id(1);
   int idx_x = get_global_id(0);

   if (idx_x < size0 && idx_y < size1 && idx_z < size2) {
     advec_cell_kernel3_zdir(&arg0[base0 + idx_x * 1 + idx_y * 1 * xdim0_advec_cell_kernel3_zdir + idx_z * 1 * xdim0_advec_cell_kernel3_zdir * ydim0_advec_cell_kernel3_zdir],
                       &arg1[base1 + idx_x * 1 + idx_y * 1 * xdim1_advec_cell_kernel3_zdir + idx_z * 1 * xdim1_advec_cell_kernel3_zdir * ydim1_advec_cell_kernel3_zdir],
                       &arg2[base2 + idx_x * 0 + idx_y * 0 * xdim2_advec_cell_kernel3_zdir + idx_z * 1 * xdim2_advec_cell_kernel3_zdir * ydim2_advec_cell_kernel3_zdir],
                       &arg3[base3 + idx_x * 0 + idx_y * 0 * xdim3_advec_cell_kernel3_zdir + idx_z * 1 * xdim3_advec_cell_kernel3_zdir * ydim3_advec_cell_kernel3_zdir],
                       &arg4[base4 + idx_x * 1 + idx_y * 1 * xdim4_advec_cell_kernel3_zdir + idx_z * 1 * xdim4_advec_cell_kernel3_zdir * ydim4_advec_cell_kernel3_zdir],
                       &arg5[base5 + idx_x * 1 + idx_y * 1 * xdim5_advec_cell_kernel3_zdir + idx_z * 1 * xdim5_advec_cell_kernel3_zdir * ydim5_advec_cell_kernel3_zdir],
                       &arg6[base6 + idx_x * 1 + idx_y * 1 * xdim6_advec_cell_kernel3_zdir + idx_z * 1 * xdim6_advec_cell_kernel3_zdir * ydim6_advec_cell_kernel3_zdir],
                       &arg7[base7 + idx_x * 1 + idx_y * 1 * xdim7_advec_cell_kernel3_zdir + idx_z * 1 * xdim7_advec_cell_kernel3_zdir * ydim7_advec_cell_kernel3_zdir],
                       *field);
   }

 }
