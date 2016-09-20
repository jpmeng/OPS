//
// auto-generated by ops.py//





#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define OPS_2D
#include  "ops_lib_cpp.h"

//
// ops_par_loop declarations
//

void ops_par_loop_tea_leaf_common_init_u_u0_kernel(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_tea_leaf_recip_kernel(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg );

void ops_par_loop_tea_leaf_yeqx_kernel(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg );

void ops_par_loop_tea_leaf_common_init_Kx_Ky_kernel(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_tea_leaf_init_zero_kernel(char const *, ops_block, int , int*,
  ops_arg );

void ops_par_loop_tea_leaf_init_zero_kernel(char const *, ops_block, int , int*,
  ops_arg );

void ops_par_loop_tea_leaf_init_zero_kernel(char const *, ops_block, int , int*,
  ops_arg );

void ops_par_loop_tea_leaf_init_zero_kernel(char const *, ops_block, int , int*,
  ops_arg );

void ops_par_loop_tea_leaf_common_init_kernel(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_tea_leaf_recip2_kernel(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_tea_leaf_common_residual_kernel(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_tea_leaf_norm2_kernel(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg );

void ops_par_loop_tea_leaf_common_init_diag_init_kernel(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_tea_leaf_zeqxty_kernel(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg );



#include "tea_leaf.h"

#include "data.h"
#include "definitions.h"

#include "tea_leaf_common_kernels.h"
#include "tea_leaf_kernels.h"

void tea_leaf_common_init(
  int halo_depth,
  int* zero_boundary,
  int reflective_boundary,
  ops_dat density,
  ops_dat energy,
  ops_dat u,
	ops_dat u0,
	ops_dat r,
  ops_dat w,
	ops_dat Kx,
	ops_dat Ky,
	ops_dat cp,
	ops_dat bfp,
  ops_dat Mi,
	double *rx, double *ry,
	int preconditioner_type, int coef)
{

  int t;

  double dx = (grid.xmax - grid.xmin)/(double)grid.x_cells;
  double dy = (grid.xmax - grid.xmin)/(double)grid.x_cells;
  *rx = dt/(dx*dx);
  *ry = dt/(dy*dy);




  int x_min = field.x_min;
  int x_max = field.x_max;
  int y_min = field.y_min;
  int y_max = field.y_max;

  int rangexy[] = {x_min,x_max,y_min,y_max};
  int rangexy_ext[] = {x_min-halo_depth+1,x_max+halo_depth,y_min-halo_depth+1,y_max+halo_depth};
	int rangexy_ext2[] = {x_min-halo_depth,x_max+halo_depth,y_min-halo_depth,y_max+halo_depth};

  ops_par_loop_tea_leaf_common_init_u_u0_kernel("tea_leaf_common_init_u_u0_kernel", tea_grid, 2, rangexy,
               ops_arg_dat(u, 1, S2D_00, "double", OPS_WRITE),
               ops_arg_dat(u0, 1, S2D_00, "double", OPS_WRITE),
               ops_arg_dat(energy, 1, S2D_00, "double", OPS_READ),
               ops_arg_dat(density, 1, S2D_00, "double", OPS_READ));

  if (coef == RECIP_CONDUCTIVITY) {
    ops_par_loop_tea_leaf_recip_kernel("tea_leaf_recip_kernel", tea_grid, 2, rangexy_ext2,
                 ops_arg_dat(w, 1, S2D_00, "double", OPS_WRITE),
                 ops_arg_dat(density, 1, S2D_00, "double", OPS_READ));
  } else if (coef == CONDUCTIVITY) {
    double one = 1.0;
    ops_par_loop_tea_leaf_yeqx_kernel("tea_leaf_yeqx_kernel", tea_grid, 2, rangexy_ext2,
                 ops_arg_dat(w, 1, S2D_00, "double", OPS_WRITE),
                 ops_arg_dat(density, 1, S2D_00, "double", OPS_READ));
  }

  ops_par_loop_tea_leaf_common_init_Kx_Ky_kernel("tea_leaf_common_init_Kx_Ky_kernel", tea_grid, 2, rangexy_ext,
               ops_arg_dat(Kx, 1, S2D_00, "double", OPS_WRITE),
               ops_arg_dat(Ky, 1, S2D_00, "double", OPS_WRITE),
               ops_arg_dat(w, 1, S2D_00_M10_0M1, "double", OPS_READ));


  if (reflective_boundary == 0) {
    if (zero_boundary[CHUNK_LEFT]==EXTERNAL_FACE) {
      int range_left[] = {x_min-halo_depth,x_min+1,y_min-halo_depth,y_max+halo_depth};
      ops_par_loop_tea_leaf_init_zero_kernel("tea_leaf_init_zero_kernel", tea_grid, 2, range_left,
                   ops_arg_dat(Kx, 1, S2D_00, "double", OPS_WRITE));
    }
    if (zero_boundary[CHUNK_RIGHT]==EXTERNAL_FACE) {
      int range_right[] = {x_max,x_max+halo_depth,y_min-halo_depth,y_max+halo_depth};
      ops_par_loop_tea_leaf_init_zero_kernel("tea_leaf_init_zero_kernel", tea_grid, 2, range_right,
                   ops_arg_dat(Kx, 1, S2D_00, "double", OPS_WRITE));
    }
    if (zero_boundary[CHUNK_BOTTOM]==EXTERNAL_FACE) {
      int range_bottom[] = {x_min-halo_depth,x_max+halo_depth,y_min-halo_depth,y_min+1};
      ops_par_loop_tea_leaf_init_zero_kernel("tea_leaf_init_zero_kernel", tea_grid, 2, range_bottom,
                   ops_arg_dat(Ky, 1, S2D_00, "double", OPS_WRITE));
    }
    if (zero_boundary[CHUNK_TOP]==EXTERNAL_FACE) {
      int range_top[] = {x_min-halo_depth,x_max+halo_depth,y_max,y_max+halo_depth};
      ops_par_loop_tea_leaf_init_zero_kernel("tea_leaf_init_zero_kernel", tea_grid, 2, range_top,
                   ops_arg_dat(Ky, 1, S2D_00, "double", OPS_WRITE));
		}
  }

    if (preconditioner_type == TL_PREC_JAC_BLOCK)
      tea_block_init(cp, bfp, Kx, Ky, *rx, *ry);
    else if (preconditioner_type == TL_PREC_JAC_DIAG)
      tea_diag_init(halo_depth, Mi, Kx, Ky, *rx, *ry);

    ops_par_loop_tea_leaf_common_init_kernel("tea_leaf_common_init_kernel", tea_grid, 2, rangexy,
                 ops_arg_dat(w, 1, S2D_00, "double", OPS_WRITE),
                 ops_arg_dat(r, 1, S2D_00, "double", OPS_WRITE),
                 ops_arg_dat(Kx, 1, S2D_00_P10, "double", OPS_READ),
                 ops_arg_dat(Ky, 1, S2D_00_0P1, "double", OPS_READ),
                 ops_arg_dat(u, 1, S2D_00_0M1_M10_P10_0P1, "double", OPS_READ),
                 ops_arg_gbl(rx, 1, "double", OPS_READ),
                 ops_arg_gbl(ry, 1, "double", OPS_READ));

}

void tea_leaf_finalise(
  ops_dat energy,
  ops_dat density,
  ops_dat u)
{
  int x_min = field.x_min;
  int x_max = field.x_max;
  int y_min = field.y_min;
  int y_max = field.y_max;
  int rangexy[] = {x_min,x_max,y_min,y_max};

  ops_par_loop_tea_leaf_recip2_kernel("tea_leaf_recip2_kernel", tea_grid, 2, rangexy,
               ops_arg_dat(energy, 1, S2D_00, "double", OPS_WRITE),
               ops_arg_dat(u, 1, S2D_00, "double", OPS_READ),
               ops_arg_dat(density, 1, S2D_00, "double", OPS_READ));

}

void tea_leaf_calc_residual(
  ops_dat u,
  ops_dat u0,
  ops_dat r,
  ops_dat Kx,
  ops_dat Ky,
  double rx, double ry)
{
  int x_min = field.x_min;
  int x_max = field.x_max;
  int y_min = field.y_min;
  int y_max = field.y_max;
  int rangexy[] = {x_min,x_max,y_min,y_max};
    ops_par_loop_tea_leaf_common_residual_kernel("tea_leaf_common_residual_kernel", tea_grid, 2, rangexy,
                 ops_arg_dat(r, 1, S2D_00, "double", OPS_WRITE),
                 ops_arg_dat(Kx, 1, S2D_00_P10, "double", OPS_READ),
                 ops_arg_dat(Ky, 1, S2D_00_0P1, "double", OPS_READ),
                 ops_arg_dat(u, 1, S2D_00_0M1_M10_P10_0P1, "double", OPS_READ),
                 ops_arg_dat(u0, 1, S2D_00, "double", OPS_READ),
                 ops_arg_gbl(&rx, 1, "double", OPS_READ),
                 ops_arg_gbl(&ry, 1, "double", OPS_READ));
}

void tea_leaf_calc_2norm_kernel(
  ops_dat arr,
  double *norm)
{
  int x_min = field.x_min;
  int x_max = field.x_max;
  int y_min = field.y_min;
  int y_max = field.y_max;
  int rangexy[] = {x_min,x_max,y_min,y_max};

  *norm = 0.0;

  ops_par_loop_tea_leaf_norm2_kernel("tea_leaf_norm2_kernel", tea_grid, 2, rangexy,
               ops_arg_dat(arr, 1, S2D_00, "double", OPS_READ),
               ops_arg_reduce(red_temp, 1, "double", OPS_INC));

  ops_reduction_result(red_temp,norm);
}

void tea_leaf_calc_2norm(int norm_array, double *norm) {
  *norm = 0.0;
  if (norm_array == 0) {
    tea_leaf_calc_2norm_kernel(u0,norm);
  } else if (norm_array == 1) {
    tea_leaf_calc_2norm_kernel(vector_r,norm);
  } else {
    ops_printf("Invalid value for norm_array\n");
    exit(-1);
  }
}

void tea_diag_init(
	int halo_depth,
  ops_dat Mi,
  ops_dat Kx,
  ops_dat Ky,
  double rx, double ry)
{
  int x_min = field.x_min;
  int x_max = field.x_max;
  int y_min = field.y_min;
  int y_max = field.y_max;
  int rangexy_ext[] = {x_min-halo_depth+1,x_max+halo_depth-1,y_min-halo_depth+1,y_max+halo_depth-1};

  ops_par_loop_tea_leaf_common_init_diag_init_kernel("tea_leaf_common_init_diag_init_kernel", tea_grid, 2, rangexy_ext,
               ops_arg_dat(Mi, 1, S2D_00, "double", OPS_WRITE),
               ops_arg_dat(Kx, 1, S2D_00_P10, "double", OPS_READ),
               ops_arg_dat(Ky, 1, S2D_00_0P1, "double", OPS_READ),
               ops_arg_gbl(&rx, 1, "double", OPS_READ),
               ops_arg_gbl(&ry, 1, "double", OPS_READ));
}

void tea_diag_solve(

  ops_dat r,
  ops_dat z,
  ops_dat Mi,
  ops_dat Kx,
  ops_dat Ky,
  double rx, double ry)
{
  int x_min = field.x_min;
  int x_max = field.x_max;
  int y_min = field.y_min;
  int y_max = field.y_max;
	int halo_depth = 1;
#warning halo depth
  int rangexy_ext[] = {x_min-halo_depth,x_max+halo_depth,y_min-halo_depth,y_max+halo_depth};

  ops_par_loop_tea_leaf_zeqxty_kernel("tea_leaf_zeqxty_kernel", tea_grid, 2, rangexy_ext,
               ops_arg_dat(z, 1, S2D_00, "double", OPS_WRITE),
               ops_arg_dat(Mi, 1, S2D_00, "double", OPS_READ),
               ops_arg_dat(r, 1, S2D_00, "double", OPS_READ));
}

void tea_block_init(
  ops_dat cp,
  ops_dat bfp,
  ops_dat Kx,
  ops_dat Ky,
  double rx, double ry)
{
  ops_printf("Error, block solvers are not supported in OPS TeaLeaf\n");
  exit(-1);
}

void tea_block_solve(
  ops_dat r,
  ops_dat z,
  ops_dat cp,
  ops_dat bfp,
  ops_dat Kx,
  ops_dat Ky,
  double rx, double ry)
{
  ops_printf("Error, block solvers are not supported in OPS TeaLeaf\n");
  exit(-1);
}
