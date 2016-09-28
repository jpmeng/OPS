//
// auto-generated by ops.py
//

// user function
inline void update_halo_kernel2_yvel_plus_4_right(double *yvel0, double *yvel1,
                                                  const int *fields) {
  if (fields[FIELD_YVEL0] == 1)
    yvel0[OPS_ACC0(0, 0, 0)] = yvel0[OPS_ACC0(-4, 0, 0)];
  if (fields[FIELD_YVEL1] == 1)
    yvel1[OPS_ACC1(0, 0, 0)] = yvel1[OPS_ACC1(-4, 0, 0)];
}

// host stub function
void ops_par_loop_update_halo_kernel2_yvel_plus_4_right(
    char const *name, ops_block block, int dim, int *range, ops_arg arg0,
    ops_arg arg1, ops_arg arg2) {

  // Timing
  double t1, t2, c1, c2;

  char *p_a[3];
  int offs[3][3];
  ops_arg args[3] = {arg0, arg1, arg2};

#ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args, 3, range, 87))
    return;
#endif

  if (OPS_diags > 1) {
    ops_timing_realloc(87, "update_halo_kernel2_yvel_plus_4_right");
    OPS_kernels[87].count++;
    ops_timers_core(&c2, &t2);
  }

  // compute locally allocated range for the sub-block
  int start[3];
  int end[3];

#ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned)
    return;
  for (int n = 0; n < 3; n++) {
    start[n] = sb->decomp_disp[n];
    end[n] = sb->decomp_disp[n] + sb->decomp_size[n];
    if (start[n] >= range[2 * n]) {
      start[n] = 0;
    } else {
      start[n] = range[2 * n] - start[n];
    }
    if (sb->id_m[n] == MPI_PROC_NULL && range[2 * n] < 0)
      start[n] = range[2 * n];
    if (end[n] >= range[2 * n + 1]) {
      end[n] = range[2 * n + 1] - sb->decomp_disp[n];
    } else {
      end[n] = sb->decomp_size[n];
    }
    if (sb->id_p[n] == MPI_PROC_NULL &&
        (range[2 * n + 1] > sb->decomp_disp[n] + sb->decomp_size[n]))
      end[n] += (range[2 * n + 1] - sb->decomp_disp[n] - sb->decomp_size[n]);
  }
#else
  for (int n = 0; n < 3; n++) {
    start[n] = range[2 * n];
    end[n] = range[2 * n + 1];
  }
#endif
#ifdef OPS_DEBUG
  ops_register_args(args, "update_halo_kernel2_yvel_plus_4_right");
#endif

  offs[0][0] = args[0].stencil->stride[0] * 1; // unit step in x dimension
  offs[0][1] =
      off3D(1, &start[0], &end[0], args[0].dat->size, args[0].stencil->stride) -
      offs[0][0];
  offs[0][2] =
      off3D(2, &start[0], &end[0], args[0].dat->size, args[0].stencil->stride) -
      offs[0][1] - offs[0][0];

  offs[1][0] = args[1].stencil->stride[0] * 1; // unit step in x dimension
  offs[1][1] =
      off3D(1, &start[0], &end[0], args[1].dat->size, args[1].stencil->stride) -
      offs[1][0];
  offs[1][2] =
      off3D(2, &start[0], &end[0], args[1].dat->size, args[1].stencil->stride) -
      offs[1][1] - offs[1][0];

  int off0_0 = offs[0][0];
  int off0_1 = offs[0][1];
  int off0_2 = offs[0][2];
  int dat0 = args[0].dat->elem_size;
  int off1_0 = offs[1][0];
  int off1_1 = offs[1][1];
  int off1_2 = offs[1][2];
  int dat1 = args[1].dat->elem_size;

  // set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset +
              args[0].dat->elem_size * start[0] * args[0].stencil->stride[0];
  base0 = base0 +
          args[0].dat->elem_size * args[0].dat->size[0] * start[1] *
              args[0].stencil->stride[1];
  base0 = base0 +
          args[0].dat->elem_size * args[0].dat->size[0] * args[0].dat->size[1] *
              start[2] * args[0].stencil->stride[2];
  p_a[0] = (char *)args[0].data + base0;

  int base1 = args[1].dat->base_offset +
              args[1].dat->elem_size * start[0] * args[1].stencil->stride[0];
  base1 = base1 +
          args[1].dat->elem_size * args[1].dat->size[0] * start[1] *
              args[1].stencil->stride[1];
  base1 = base1 +
          args[1].dat->elem_size * args[1].dat->size[0] * args[1].dat->size[1] *
              start[2] * args[1].stencil->stride[2];
  p_a[1] = (char *)args[1].data + base1;

  p_a[2] = args[2].data;

  // initialize global variable with the dimension of dats
  xdim0 = args[0].dat->size[0];
  ydim0 = args[0].dat->size[1];
  xdim1 = args[1].dat->size[0];
  ydim1 = args[1].dat->size[1];

  // Halo Exchanges
  ops_H_D_exchanges_host(args, 3);
  ops_halo_exchanges(args, 3, range);
  ops_H_D_exchanges_host(args, 3);

  if (OPS_diags > 1) {
    ops_timers_core(&c1, &t1);
    OPS_kernels[87].mpi_time += t1 - t2;
  }

  int n_x;
  for (int n_z = start[2]; n_z < end[2]; n_z++) {
    for (int n_y = start[1]; n_y < end[1]; n_y++) {
#pragma novector
      for (n_x = start[0];
           n_x < start[0] + ((end[0] - start[0]) / SIMD_VEC) * SIMD_VEC;
           n_x += SIMD_VEC) {
// call kernel function, passing in pointers to data -vectorised
#pragma simd
        for (int i = 0; i < SIMD_VEC; i++) {
          update_halo_kernel2_yvel_plus_4_right((double *)p_a[0] + i * 1 * 1,
                                                (double *)p_a[1] + i * 1 * 1,
                                                (int *)p_a[2]);
        }

        // shift pointers to data x direction
        p_a[0] = p_a[0] + (dat0 * off0_0) * SIMD_VEC;
        p_a[1] = p_a[1] + (dat1 * off1_0) * SIMD_VEC;
      }

      for (int n_x = start[0] + ((end[0] - start[0]) / SIMD_VEC) * SIMD_VEC;
           n_x < end[0]; n_x++) {
        // call kernel function, passing in pointers to data - remainder
        update_halo_kernel2_yvel_plus_4_right((double *)p_a[0],
                                              (double *)p_a[1], (int *)p_a[2]);

        // shift pointers to data x direction
        p_a[0] = p_a[0] + (dat0 * off0_0);
        p_a[1] = p_a[1] + (dat1 * off1_0);
      }

      // shift pointers to data y direction
      p_a[0] = p_a[0] + (dat0 * off0_1);
      p_a[1] = p_a[1] + (dat1 * off1_1);
    }
    // shift pointers to data z direction
    p_a[0] = p_a[0] + (dat0 * off0_2);
    p_a[1] = p_a[1] + (dat1 * off1_2);
  }
  if (OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
    OPS_kernels[87].time += t2 - t1;
  }
  ops_set_dirtybit_host(args, 3);
  ops_set_halo_dirtybit3(&args[0], range);
  ops_set_halo_dirtybit3(&args[1], range);

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&c1, &t1);
    OPS_kernels[87].mpi_time += t1 - t2;
    OPS_kernels[87].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[87].transfer += ops_compute_transfer(dim, start, end, &arg1);
  }
}
