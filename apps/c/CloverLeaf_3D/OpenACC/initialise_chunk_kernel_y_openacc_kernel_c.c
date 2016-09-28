//
// auto-generated by ops.py
//
#include "./OpenACC/clover_leaf_common.h"

#undef OPS_GPU

int xdim0_initialise_chunk_kernel_y;
int ydim0_initialise_chunk_kernel_y;
int xdim1_initialise_chunk_kernel_y;
int ydim1_initialise_chunk_kernel_y;
int xdim2_initialise_chunk_kernel_y;
int ydim2_initialise_chunk_kernel_y;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2

#define OPS_ACC0(x, y, z)                                                      \
  (x + xdim0_initialise_chunk_kernel_y * (y) +                                 \
   xdim0_initialise_chunk_kernel_y * ydim0_initialise_chunk_kernel_y * (z))
#define OPS_ACC1(x, y, z)                                                      \
  (x + xdim1_initialise_chunk_kernel_y * (y) +                                 \
   xdim1_initialise_chunk_kernel_y * ydim1_initialise_chunk_kernel_y * (z))
#define OPS_ACC2(x, y, z)                                                      \
  (x + xdim2_initialise_chunk_kernel_y * (y) +                                 \
   xdim2_initialise_chunk_kernel_y * ydim2_initialise_chunk_kernel_y * (z))

// user function
inline void initialise_chunk_kernel_y(double *vertexy, const int *yy,
                                      double *vertexdy) {
  int y_min = field.y_min - 2;

  double min_y, d_y;
  d_y = (grid.ymax - grid.ymin) / (double)grid.y_cells;
  min_y = grid.ymin + d_y * field.bottom;

  vertexy[OPS_ACC0(0, 0, 0)] = min_y + d_y * (yy[OPS_ACC1(0, 0, 0)] - y_min);
  vertexdy[OPS_ACC2(0, 0, 0)] = (double)d_y;
}

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2

void initialise_chunk_kernel_y_c_wrapper(double *p_a0, int *p_a1, double *p_a2,
                                         int x_size, int y_size, int z_size) {
#ifdef OPS_GPU
#pragma acc parallel deviceptr(p_a0, p_a1, p_a2)
#pragma acc loop
#endif
  for (int n_z = 0; n_z < z_size; n_z++) {
#ifdef OPS_GPU
#pragma acc loop
#endif
    for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#pragma acc loop
#endif
      for (int n_x = 0; n_x < x_size; n_x++) {
        initialise_chunk_kernel_y(
            p_a0 + n_x * 0 * 1 + n_y * xdim0_initialise_chunk_kernel_y * 1 * 1 +
                n_z * xdim0_initialise_chunk_kernel_y *
                    ydim0_initialise_chunk_kernel_y * 0,
            p_a1 + n_x * 0 * 1 + n_y * xdim1_initialise_chunk_kernel_y * 1 * 1 +
                n_z * xdim1_initialise_chunk_kernel_y *
                    ydim1_initialise_chunk_kernel_y * 0,
            p_a2 + n_x * 0 * 1 + n_y * xdim2_initialise_chunk_kernel_y * 1 * 1 +
                n_z * xdim2_initialise_chunk_kernel_y *
                    ydim2_initialise_chunk_kernel_y * 0);
      }
    }
  }
}
