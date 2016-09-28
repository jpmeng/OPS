//
// auto-generated by ops.py
//
#include "./MPI_inline/clover_leaf_common.h"

int xdim0_update_halo_kernel5_plus_2_a;
int ydim0_update_halo_kernel5_plus_2_a;
int xdim1_update_halo_kernel5_plus_2_a;
int ydim1_update_halo_kernel5_plus_2_a;

#define OPS_ACC0(x, y, z)                                                      \
  (n_x * 1 + n_y * xdim0_update_halo_kernel5_plus_2_a * 1 +                    \
   n_z * xdim0_update_halo_kernel5_plus_2_a *                                  \
       ydim0_update_halo_kernel5_plus_2_a * 1 +                                \
   x + xdim0_update_halo_kernel5_plus_2_a * (y) +                              \
   xdim0_update_halo_kernel5_plus_2_a * ydim0_update_halo_kernel5_plus_2_a *   \
       (z))
#define OPS_ACC1(x, y, z)                                                      \
  (n_x * 1 + n_y * xdim1_update_halo_kernel5_plus_2_a * 1 +                    \
   n_z * xdim1_update_halo_kernel5_plus_2_a *                                  \
       ydim1_update_halo_kernel5_plus_2_a * 1 +                                \
   x + xdim1_update_halo_kernel5_plus_2_a * (y) +                              \
   xdim1_update_halo_kernel5_plus_2_a * ydim1_update_halo_kernel5_plus_2_a *   \
       (z))

// user function

void update_halo_kernel5_plus_2_a_c_wrapper(double *restrict vol_flux_z,
                                            double *restrict mass_flux_z,
                                            const int *restrict fields,
                                            int x_size, int y_size,
                                            int z_size) {
#pragma omp parallel for
  for (int n_z = 0; n_z < z_size; n_z++) {
    for (int n_y = 0; n_y < y_size; n_y++) {
      for (int n_x = 0; n_x < x_size; n_x++) {

        if (fields[FIELD_VOL_FLUX_Z] == 1)
          vol_flux_z[OPS_ACC0(0, 0, 0)] = vol_flux_z[OPS_ACC0(0, 2, 0)];
        if (fields[FIELD_MASS_FLUX_Z] == 1)
          mass_flux_z[OPS_ACC1(0, 0, 0)] = mass_flux_z[OPS_ACC1(0, 2, 0)];
      }
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
