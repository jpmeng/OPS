//
// auto-generated by ops.py
//
#define OPS_ACC0(x, y, z)                                                      \
  (n_x * 1 + n_y * xdim0_update_halo_kernel2_yvel_minus_2_top * 1 +            \
   n_z * xdim0_update_halo_kernel2_yvel_minus_2_top *                          \
       ydim0_update_halo_kernel2_yvel_minus_2_top * 1 +                        \
   x + xdim0_update_halo_kernel2_yvel_minus_2_top * (y) +                      \
   xdim0_update_halo_kernel2_yvel_minus_2_top *                                \
       ydim0_update_halo_kernel2_yvel_minus_2_top * (z))
#define OPS_ACC1(x, y, z)                                                      \
  (n_x * 1 + n_y * xdim1_update_halo_kernel2_yvel_minus_2_top * 1 +            \
   n_z * xdim1_update_halo_kernel2_yvel_minus_2_top *                          \
       ydim1_update_halo_kernel2_yvel_minus_2_top * 1 +                        \
   x + xdim1_update_halo_kernel2_yvel_minus_2_top * (y) +                      \
   xdim1_update_halo_kernel2_yvel_minus_2_top *                                \
       ydim1_update_halo_kernel2_yvel_minus_2_top * (z))

// user function

// host stub function
void ops_par_loop_update_halo_kernel2_yvel_minus_2_top_execute(
    ops_kernel_descriptor *desc) {
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];

  // Timing
  double t1, t2, c1, c2;

  ops_arg args[3] = {arg0, arg1, arg2};

#ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args, 3, range, 84))
    return;
#endif

  if (OPS_diags > 1) {
    ops_timing_realloc(84, "update_halo_kernel2_yvel_minus_2_top");
    OPS_kernels[84].count++;
    ops_timers_core(&c2, &t2);
  }

  // compute locally allocated range for the sub-block
  int start[3];
  int end[3];

  for (int n = 0; n < 3; n++) {
    start[n] = range[2 * n];
    end[n] = range[2 * n + 1];
  }

#ifdef OPS_DEBUG
  ops_register_args(args, "update_halo_kernel2_yvel_minus_2_top");
#endif

  // set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset;
  double *__restrict__ yvel0 = (double *)(args[0].data + base0);

  int base1 = args[1].dat->base_offset;
  double *__restrict__ yvel1 = (double *)(args[1].data + base1);

  const int *__restrict__ fields = (int *)args[2].data;

  // initialize global variable with the dimension of dats
  int xdim0_update_halo_kernel2_yvel_minus_2_top = args[0].dat->size[0];
  int ydim0_update_halo_kernel2_yvel_minus_2_top = args[0].dat->size[1];
  int xdim1_update_halo_kernel2_yvel_minus_2_top = args[1].dat->size[0];
  int ydim1_update_halo_kernel2_yvel_minus_2_top = args[1].dat->size[1];

  // Halo Exchanges
  ops_H_D_exchanges_host(args, 3);
  ops_halo_exchanges(args, 3, range);
  ops_H_D_exchanges_host(args, 3);

  if (OPS_diags > 1) {
    ops_timers_core(&c1, &t1);
    OPS_kernels[84].mpi_time += t1 - t2;
  }

#pragma omp parallel for collapse(2)
  for (int n_z = start[2]; n_z < end[2]; n_z++) {
    for (int n_y = start[1]; n_y < end[1]; n_y++) {
#pragma simd
      for (int n_x = start[0]; n_x < end[0]; n_x++) {

        if (fields[FIELD_YVEL0] == 1)
          yvel0[OPS_ACC0(0, 0, 0)] = -yvel0[OPS_ACC0(0, -2, 0)];
        if (fields[FIELD_YVEL1] == 1)
          yvel1[OPS_ACC1(0, 0, 0)] = -yvel1[OPS_ACC1(0, -2, 0)];
      }
    }
  }
  if (OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
    OPS_kernels[84].time += t2 - t1;
  }
  ops_set_dirtybit_host(args, 3);
  ops_set_halo_dirtybit3(&args[0], range);
  ops_set_halo_dirtybit3(&args[1], range);

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&c1, &t1);
    OPS_kernels[84].mpi_time += t1 - t2;
    OPS_kernels[84].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[84].transfer += ops_compute_transfer(dim, start, end, &arg1);
  }
}
#undef OPS_ACC0
#undef OPS_ACC1

void ops_par_loop_update_halo_kernel2_yvel_minus_2_top(char const *name,
                                                       ops_block block, int dim,
                                                       int *range, ops_arg arg0,
                                                       ops_arg arg1,
                                                       ops_arg arg2) {
  ops_kernel_descriptor *desc =
      (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->index = 84;
#ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned)
    return;
  for (int n = 0; n < 3; n++) {
    desc->range[2 * n] = sb->decomp_disp[n];
    desc->range[2 * n + 1] = sb->decomp_disp[n] + sb->decomp_size[n];
    if (desc->range[2 * n] >= range[2 * n]) {
      desc->range[2 * n] = 0;
    } else {
      desc->range[2 * n] = range[2 * n] - desc->range[2 * n];
    }
    if (sb->id_m[n] == MPI_PROC_NULL && range[2 * n] < 0)
      desc->range[2 * n] = range[2 * n];
    if (desc->range[2 * n + 1] >= range[2 * n + 1]) {
      desc->range[2 * n + 1] = range[2 * n + 1] - sb->decomp_disp[n];
    } else {
      desc->range[2 * n + 1] = sb->decomp_size[n];
    }
    if (sb->id_p[n] == MPI_PROC_NULL &&
        (range[2 * n + 1] > sb->decomp_disp[n] + sb->decomp_size[n]))
      desc->range[2 * n + 1] +=
          (range[2 * n + 1] - sb->decomp_disp[n] - sb->decomp_size[n]);
  }
#else // OPS_MPI
  for (int i = 0; i < 6; i++) {
    desc->range[i] = range[i];
  }
#endif // OPS_MPI
  desc->nargs = 3;
  desc->args = (ops_arg *)malloc(3 * sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->args[1] = arg1;
  desc->args[2] = arg2;
  char *tmp = (char *)malloc(NUM_FIELDS * sizeof(int));
  memcpy(tmp, arg2.data, NUM_FIELDS * sizeof(int));
  desc->args[2].data = tmp;
  desc->function = ops_par_loop_update_halo_kernel2_yvel_minus_2_top_execute;
  ops_enqueue_kernel(desc);
}
