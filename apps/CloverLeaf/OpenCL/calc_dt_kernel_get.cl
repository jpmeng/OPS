//
// auto-generated by ops.py on 2014-06-05 14:25
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
#define OPS_ACC0(x,y) (x+xdim0_calc_dt_kernel_get*(y))
#define OPS_ACC1(x,y) (x+xdim1_calc_dt_kernel_get*(y))


//user function
void calc_dt_kernel_get( __global double* cellx, __global double* celly,  double* xl_pos,
 double* yl_pos,
  int xdim0_calc_dt_kernel_get,
int xdim1_calc_dt_kernel_get)

  {
  *xl_pos = cellx[OPS_ACC0(0,0)];
  *yl_pos = celly[OPS_ACC1(0,0)];
}



 #undef OPS_ACC0
 #undef OPS_ACC1


 __kernel void ops_calc_dt_kernel_get(
 __global double* arg0,
 __global double* arg1,
 __global double* arg2,
 __local double* scratch2,
 int r_bytes2,
 __global double* arg3,
 __local double* scratch3,
 int r_bytes3,
 int xdim0_calc_dt_kernel_get,
 int xdim1_calc_dt_kernel_get,
 const int base0,
 const int base1,
 int size0,
 int size1 ){

   arg2 += r_bytes2;
   double arg2_l[1];
   arg3 += r_bytes3;
   double arg3_l[1];
   for (int d=0; d<1; d++) arg2_l[d] = ZERO_double;
   for (int d=0; d<1; d++) arg3_l[d] = ZERO_double;

   int idx_y = get_global_id(1);
   int idx_x = get_global_id(0);

   if (idx_x < size0 && idx_y < size1) {
     calc_dt_kernel_get(&arg0[base0 + idx_x * 1 + idx_y * 0 * xdim0_calc_dt_kernel_get],
                    &arg1[base1 + idx_x * 0 + idx_y * 1 * xdim1_calc_dt_kernel_get],
                    arg2_l,
                    arg3_l,
                    
                    xdim0_calc_dt_kernel_get,
                    xdim1_calc_dt_kernel_get);
   }
   reduce_double(arg2_l[0], scratch2, arg2, OPS_INC);
   reduce_double(arg3_l[0], scratch3, arg3, OPS_INC);

 }
