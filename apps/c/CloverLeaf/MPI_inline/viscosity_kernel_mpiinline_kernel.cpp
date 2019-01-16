//
// auto-generated by ops.py
//

extern int xdim0_viscosity_kernel;
int xdim0_viscosity_kernel_h = -1;
extern int xdim1_viscosity_kernel;
int xdim1_viscosity_kernel_h = -1;
extern int xdim2_viscosity_kernel;
int xdim2_viscosity_kernel_h = -1;
extern int xdim3_viscosity_kernel;
int xdim3_viscosity_kernel_h = -1;
extern int xdim4_viscosity_kernel;
int xdim4_viscosity_kernel_h = -1;
extern int xdim5_viscosity_kernel;
int xdim5_viscosity_kernel_h = -1;
extern int xdim6_viscosity_kernel;
int xdim6_viscosity_kernel_h = -1;

#ifdef __cplusplus
extern "C" {
#endif
void viscosity_kernel_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  double *p_a4,
  double *p_a5,
  double *p_a6,
  int x_size, int y_size);

#ifdef __cplusplus
}
#endif

// host stub function
void ops_par_loop_viscosity_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3, ops_arg arg4, ops_arg arg5, ops_arg arg6) {

  ops_arg args[7] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6};


  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,7,range,50)) return;
  #endif

  if (OPS_instance::getOPSInstance()->OPS_diags > 1) {
    ops_timing_realloc(50,"viscosity_kernel");
    OPS_instance::getOPSInstance()->OPS_kernels[50].count++;
  }

  //compute localy allocated range for the sub-block
  int start[2];
  int end[2];
  int arg_idx[2];

  #ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (compute_ranges(args, 7,block, range, start, end, arg_idx) < 0) return;
  #else
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
    arg_idx[n] = start[n];
  }
  #endif

  int x_size = MAX(0,end[0]-start[0]);
  int y_size = MAX(0,end[1]-start[1]);

  int xdim0 = args[0].dat->size[0];
  int xdim1 = args[1].dat->size[0];
  int xdim2 = args[2].dat->size[0];
  int xdim3 = args[3].dat->size[0];
  int xdim4 = args[4].dat->size[0];
  int xdim5 = args[5].dat->size[0];
  int xdim6 = args[6].dat->size[0];

  //Timing
  double t1,t2,c1,c2;
  if (OPS_instance::getOPSInstance()->OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
  }

  if (xdim0 != xdim0_viscosity_kernel_h || xdim1 != xdim1_viscosity_kernel_h || xdim2 != xdim2_viscosity_kernel_h || xdim3 != xdim3_viscosity_kernel_h || xdim4 != xdim4_viscosity_kernel_h || xdim5 != xdim5_viscosity_kernel_h || xdim6 != xdim6_viscosity_kernel_h) {
    xdim0_viscosity_kernel = xdim0;
    xdim0_viscosity_kernel_h = xdim0;
    xdim1_viscosity_kernel = xdim1;
    xdim1_viscosity_kernel_h = xdim1;
    xdim2_viscosity_kernel = xdim2;
    xdim2_viscosity_kernel_h = xdim2;
    xdim3_viscosity_kernel = xdim3;
    xdim3_viscosity_kernel_h = xdim3;
    xdim4_viscosity_kernel = xdim4;
    xdim4_viscosity_kernel_h = xdim4;
    xdim5_viscosity_kernel = xdim5;
    xdim5_viscosity_kernel_h = xdim5;
    xdim6_viscosity_kernel = xdim6;
    xdim6_viscosity_kernel_h = xdim6;
  }


  int dat0 = (OPS_instance::getOPSInstance()->OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);
  int dat1 = (OPS_instance::getOPSInstance()->OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size);
  int dat2 = (OPS_instance::getOPSInstance()->OPS_soa ? args[2].dat->type_size : args[2].dat->elem_size);
  int dat3 = (OPS_instance::getOPSInstance()->OPS_soa ? args[3].dat->type_size : args[3].dat->elem_size);
  int dat4 = (OPS_instance::getOPSInstance()->OPS_soa ? args[4].dat->type_size : args[4].dat->elem_size);
  int dat5 = (OPS_instance::getOPSInstance()->OPS_soa ? args[5].dat->type_size : args[5].dat->elem_size);
  int dat6 = (OPS_instance::getOPSInstance()->OPS_soa ? args[6].dat->type_size : args[6].dat->elem_size);

  //set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset + (OPS_instance::getOPSInstance()->OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size) * start[0] * args[0].stencil->stride[0];
  base0 = base0+ (OPS_instance::getOPSInstance()->OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size) *
    args[0].dat->size[0] *
    start[1] * args[0].stencil->stride[1];
  double *p_a0 = (double *)(args[0].data + base0);

  int base1 = args[1].dat->base_offset + (OPS_instance::getOPSInstance()->OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size) * start[0] * args[1].stencil->stride[0];
  base1 = base1+ (OPS_instance::getOPSInstance()->OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size) *
    args[1].dat->size[0] *
    start[1] * args[1].stencil->stride[1];
  double *p_a1 = (double *)(args[1].data + base1);

  int base2 = args[2].dat->base_offset + (OPS_instance::getOPSInstance()->OPS_soa ? args[2].dat->type_size : args[2].dat->elem_size) * start[0] * args[2].stencil->stride[0];
  base2 = base2+ (OPS_instance::getOPSInstance()->OPS_soa ? args[2].dat->type_size : args[2].dat->elem_size) *
    args[2].dat->size[0] *
    start[1] * args[2].stencil->stride[1];
  double *p_a2 = (double *)(args[2].data + base2);

  int base3 = args[3].dat->base_offset + (OPS_instance::getOPSInstance()->OPS_soa ? args[3].dat->type_size : args[3].dat->elem_size) * start[0] * args[3].stencil->stride[0];
  base3 = base3+ (OPS_instance::getOPSInstance()->OPS_soa ? args[3].dat->type_size : args[3].dat->elem_size) *
    args[3].dat->size[0] *
    start[1] * args[3].stencil->stride[1];
  double *p_a3 = (double *)(args[3].data + base3);

  int base4 = args[4].dat->base_offset + (OPS_instance::getOPSInstance()->OPS_soa ? args[4].dat->type_size : args[4].dat->elem_size) * start[0] * args[4].stencil->stride[0];
  base4 = base4+ (OPS_instance::getOPSInstance()->OPS_soa ? args[4].dat->type_size : args[4].dat->elem_size) *
    args[4].dat->size[0] *
    start[1] * args[4].stencil->stride[1];
  double *p_a4 = (double *)(args[4].data + base4);

  int base5 = args[5].dat->base_offset + (OPS_instance::getOPSInstance()->OPS_soa ? args[5].dat->type_size : args[5].dat->elem_size) * start[0] * args[5].stencil->stride[0];
  base5 = base5+ (OPS_instance::getOPSInstance()->OPS_soa ? args[5].dat->type_size : args[5].dat->elem_size) *
    args[5].dat->size[0] *
    start[1] * args[5].stencil->stride[1];
  double *p_a5 = (double *)(args[5].data + base5);

  int base6 = args[6].dat->base_offset + (OPS_instance::getOPSInstance()->OPS_soa ? args[6].dat->type_size : args[6].dat->elem_size) * start[0] * args[6].stencil->stride[0];
  base6 = base6+ (OPS_instance::getOPSInstance()->OPS_soa ? args[6].dat->type_size : args[6].dat->elem_size) *
    args[6].dat->size[0] *
    start[1] * args[6].stencil->stride[1];
  double *p_a6 = (double *)(args[6].data + base6);



  ops_H_D_exchanges_host(args, 7);
  ops_halo_exchanges(args,7,range);

  if (OPS_instance::getOPSInstance()->OPS_diags > 1) {
    ops_timers_core(&c1,&t1);
    OPS_instance::getOPSInstance()->OPS_kernels[50].mpi_time += t1-t2;
  }

  viscosity_kernel_c_wrapper(
    p_a0,
    p_a1,
    p_a2,
    p_a3,
    p_a4,
    p_a5,
    p_a6,
    x_size, y_size);

  if (OPS_instance::getOPSInstance()->OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_instance::getOPSInstance()->OPS_kernels[50].time += t2-t1;
  }
  ops_set_dirtybit_host(args, 7);
  ops_set_halo_dirtybit3(&args[6],range);

  //Update kernel record
  if (OPS_instance::getOPSInstance()->OPS_diags > 1) {
    OPS_instance::getOPSInstance()->OPS_kernels[50].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_instance::getOPSInstance()->OPS_kernels[50].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_instance::getOPSInstance()->OPS_kernels[50].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_instance::getOPSInstance()->OPS_kernels[50].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_instance::getOPSInstance()->OPS_kernels[50].transfer += ops_compute_transfer(dim, start, end, &arg4);
    OPS_instance::getOPSInstance()->OPS_kernels[50].transfer += ops_compute_transfer(dim, start, end, &arg5);
    OPS_instance::getOPSInstance()->OPS_kernels[50].transfer += ops_compute_transfer(dim, start, end, &arg6);
  }
}
