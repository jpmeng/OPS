//
// auto-generated by ops.py on 2014-07-31 17:05
//



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define OPS_3D
#include  "ops_lib_cpp.h"

//
// ops_par_loop declarations
//

void ops_par_loop_reset_field_kernel1(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_reset_field_kernel2(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );



#include "data.h"
#include "definitions.h"

//#include "reset_field_kernel.h"

void reset_field()
{
  error_condition = 0;

  int x_min = field.x_min;
  int x_max = field.x_max;
  int y_min = field.y_min;
  int y_max = field.y_max;
  int z_min = field.z_min;
  int z_max = field.z_max;

  int rangexyz_inner[] = {x_min,x_max,y_min,y_max,z_min,z_max};

  ops_par_loop_reset_field_kernel1("reset_field_kernel1", clover_grid, 3, rangexyz_inner,
               ops_arg_dat(density0, S3D_000, "double", OPS_WRITE),
               ops_arg_dat(density1, S3D_000, "double", OPS_READ),
               ops_arg_dat(energy0, S3D_000, "double", OPS_WRITE),
               ops_arg_dat(energy1, S3D_000, "double", OPS_READ));

  int rangexyz_inner_plus1xyz[] = {x_min,x_max+1,y_min,y_max+1,z_min,z_max+1};

  ops_par_loop_reset_field_kernel2("reset_field_kernel2", clover_grid, 3, rangexyz_inner_plus1xyz,
               ops_arg_dat(xvel0, S3D_000, "double", OPS_WRITE),
               ops_arg_dat(xvel1, S3D_000, "double", OPS_READ),
               ops_arg_dat(yvel0, S3D_000, "double", OPS_WRITE),
               ops_arg_dat(yvel1, S3D_000, "double", OPS_READ),
               ops_arg_dat(zvel0, S3D_000, "double", OPS_WRITE),
               ops_arg_dat(zvel1, S3D_000, "double", OPS_READ));
}
