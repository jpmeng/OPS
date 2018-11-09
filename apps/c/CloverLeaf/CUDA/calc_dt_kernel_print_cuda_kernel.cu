//
// auto-generated by ops.py
//
__constant__ int dims_calc_dt_kernel_print [7][1];
static int dims_calc_dt_kernel_print_h [7][1] = {0};

//user function
__device__

void calc_dt_kernel_print_gpu(const ACC<double> &xvel0, const ACC<double> &yvel0,
                        const ACC<double> &density0, const ACC<double> &energy0,
                        const ACC<double> &pressure, const ACC<double> &soundspeed, double *output) {
  output[0] = xvel0(1,0);
  output[1] = yvel0(1,0);
  output[2] = xvel0(-1,0);
  output[3] = yvel0(-1,0);
  output[4] = xvel0(0,1);
  output[5] = yvel0(0,1);
  output[6] = xvel0(0,-1);
  output[7] = yvel0(0,-1);
  output[8] = density0(0,0);
  output[9] = energy0(0,0);
  output[10]= pressure(0,0);
  output[11]= soundspeed(0,0);

}



__global__ void ops_calc_dt_kernel_print(
double* __restrict arg0,
double* __restrict arg1,
double* __restrict arg2,
double* __restrict arg3,
double* __restrict arg4,
double* __restrict arg5,
double* __restrict arg6,
int size0,
int size1 ){

  double arg6_l[12];
  for (int d=0; d<12; d++) arg6_l[d] = ZERO_double;

  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1*1 + idx_y * 1*1 * dims_calc_dt_kernel_print[0][0];
  arg1 += idx_x * 1*1 + idx_y * 1*1 * dims_calc_dt_kernel_print[1][0];
  arg2 += idx_x * 1*1 + idx_y * 1*1 * dims_calc_dt_kernel_print[2][0];
  arg3 += idx_x * 1*1 + idx_y * 1*1 * dims_calc_dt_kernel_print[3][0];
  arg4 += idx_x * 1*1 + idx_y * 1*1 * dims_calc_dt_kernel_print[4][0];
  arg5 += idx_x * 1*1 + idx_y * 1*1 * dims_calc_dt_kernel_print[5][0];

  if (idx_x < size0 && idx_y < size1) {
    const ACC<double> argp0(dims_calc_dt_kernel_print[0][0], arg0);
    const ACC<double> argp1(dims_calc_dt_kernel_print[1][0], arg1);
    const ACC<double> argp2(dims_calc_dt_kernel_print[2][0], arg2);
    const ACC<double> argp3(dims_calc_dt_kernel_print[3][0], arg3);
    const ACC<double> argp4(dims_calc_dt_kernel_print[4][0], arg4);
    const ACC<double> argp5(dims_calc_dt_kernel_print[5][0], arg5);
    calc_dt_kernel_print_gpu(argp0,
                   argp1,
                   argp2,
                   argp3,
                   argp4,
                   argp5,
                   arg6_l);
  }
  for (int d=0; d<12; d++)
    ops_reduction_cuda<OPS_INC>(&arg6[d+(blockIdx.x + blockIdx.y*gridDim.x)*12],arg6_l[d]);

}

// host stub function
#ifndef OPS_LAZY
void ops_par_loop_calc_dt_kernel_print(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6) {
#else
void ops_par_loop_calc_dt_kernel_print_execute(ops_kernel_descriptor *desc) {
  int dim = desc->dim;
  int *range = desc->range;
  #ifdef OPS_MPI
  ops_block block = desc->block;
  #endif
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];
  ops_arg arg3 = desc->args[3];
  ops_arg arg4 = desc->args[4];
  ops_arg arg5 = desc->args[5];
  ops_arg arg6 = desc->args[6];
  #endif

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[7] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6};


  #if CHECKPOINTING && !OPS_LAZY
  if (!ops_checkpointing_before(args,7,range,54)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(54,"calc_dt_kernel_print");
    OPS_kernels[54].count++;
    ops_timers_core(&c1,&t1);
  }

  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];

  #ifdef OPS_MPI
  int arg_idx[2];
  #endif
  #ifdef OPS_MPI
  #ifdef OPS_LAZY
  sub_block_list sb = OPS_sub_block_list[block->index];
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
    arg_idx[n] = sb->decomp_disp[n]+start[n];
  }
  #else
  if (compute_ranges(args, 7,block, range, start, end, arg_idx) < 0) return;
  #endif
  #else
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif
  int xdim0 = args[0].dat->size[0];
  int xdim1 = args[1].dat->size[0];
  int xdim2 = args[2].dat->size[0];
  int xdim3 = args[3].dat->size[0];
  int xdim4 = args[4].dat->size[0];
  int xdim5 = args[5].dat->size[0];

  if (xdim0 != dims_calc_dt_kernel_print_h[0][0] || xdim1 != dims_calc_dt_kernel_print_h[1][0] || xdim2 != dims_calc_dt_kernel_print_h[2][0] || xdim3 != dims_calc_dt_kernel_print_h[3][0] || xdim4 != dims_calc_dt_kernel_print_h[4][0] || xdim5 != dims_calc_dt_kernel_print_h[5][0]) {
    dims_calc_dt_kernel_print_h[0][0] = xdim0;
    dims_calc_dt_kernel_print_h[1][0] = xdim1;
    dims_calc_dt_kernel_print_h[2][0] = xdim2;
    dims_calc_dt_kernel_print_h[3][0] = xdim3;
    dims_calc_dt_kernel_print_h[4][0] = xdim4;
    dims_calc_dt_kernel_print_h[5][0] = xdim5;
    cutilSafeCall(cudaMemcpyToSymbol( dims_calc_dt_kernel_print, dims_calc_dt_kernel_print_h, sizeof(dims_calc_dt_kernel_print)));
  }


  #ifdef OPS_MPI
  double *arg6h = (double *)(((ops_reduction)args[6].data)->data + ((ops_reduction)args[6].data)->size * block->index);
  #else
  double *arg6h = (double *)(((ops_reduction)args[6].data)->data);
  #endif

  int x_size = MAX(0,end[0]-start[0]);
  int y_size = MAX(0,end[1]-start[1]);

  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, 1);
  dim3 tblock(OPS_block_size_x,OPS_block_size_y,OPS_block_size_z);

  int nblocks = ((x_size-1)/OPS_block_size_x+ 1)*((y_size-1)/OPS_block_size_y + 1);
  int maxblocks = nblocks;
  int reduct_bytes = 0;
  int reduct_size = 0;

  reduct_bytes += ROUND_UP(maxblocks*12*sizeof(double));
  reduct_size = MAX(reduct_size,sizeof(double)*12);

  reallocReductArrays(reduct_bytes);
  reduct_bytes = 0;

  arg6.data = OPS_reduct_h + reduct_bytes;
  arg6.data_d = OPS_reduct_d + reduct_bytes;
  for (int b=0; b<maxblocks; b++)
  for (int d=0; d<12; d++) ((double *)arg6.data)[d+b*12] = ZERO_double;
  reduct_bytes += ROUND_UP(maxblocks*12*sizeof(double));


  mvReductArraysToDevice(reduct_bytes);
  int dat0 = (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);
  int dat1 = (OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size);
  int dat2 = (OPS_soa ? args[2].dat->type_size : args[2].dat->elem_size);
  int dat3 = (OPS_soa ? args[3].dat->type_size : args[3].dat->elem_size);
  int dat4 = (OPS_soa ? args[4].dat->type_size : args[4].dat->elem_size);
  int dat5 = (OPS_soa ? args[5].dat->type_size : args[5].dat->elem_size);

  char *p_a[7];

  //set up initial pointers
  int base0 = args[0].dat->base_offset + 
           dat0 * 1 * (start[0] * args[0].stencil->stride[0]);
  base0 = base0+ dat0 *
    args[0].dat->size[0] *
    (start[1] * args[0].stencil->stride[1]);
  p_a[0] = (char *)args[0].data_d + base0;

  int base1 = args[1].dat->base_offset + 
           dat1 * 1 * (start[0] * args[1].stencil->stride[0]);
  base1 = base1+ dat1 *
    args[1].dat->size[0] *
    (start[1] * args[1].stencil->stride[1]);
  p_a[1] = (char *)args[1].data_d + base1;

  int base2 = args[2].dat->base_offset + 
           dat2 * 1 * (start[0] * args[2].stencil->stride[0]);
  base2 = base2+ dat2 *
    args[2].dat->size[0] *
    (start[1] * args[2].stencil->stride[1]);
  p_a[2] = (char *)args[2].data_d + base2;

  int base3 = args[3].dat->base_offset + 
           dat3 * 1 * (start[0] * args[3].stencil->stride[0]);
  base3 = base3+ dat3 *
    args[3].dat->size[0] *
    (start[1] * args[3].stencil->stride[1]);
  p_a[3] = (char *)args[3].data_d + base3;

  int base4 = args[4].dat->base_offset + 
           dat4 * 1 * (start[0] * args[4].stencil->stride[0]);
  base4 = base4+ dat4 *
    args[4].dat->size[0] *
    (start[1] * args[4].stencil->stride[1]);
  p_a[4] = (char *)args[4].data_d + base4;

  int base5 = args[5].dat->base_offset + 
           dat5 * 1 * (start[0] * args[5].stencil->stride[0]);
  base5 = base5+ dat5 *
    args[5].dat->size[0] *
    (start[1] * args[5].stencil->stride[1]);
  p_a[5] = (char *)args[5].data_d + base5;


  #ifndef OPS_LAZY
  ops_H_D_exchanges_device(args, 7);
  ops_halo_exchanges(args,7,range);
  #endif

  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[54].mpi_time += t2-t1;
  }

  int nshared = 0;
  int nthread = OPS_block_size_x*OPS_block_size_y*OPS_block_size_z;

  nshared = MAX(nshared,sizeof(double)*12);

  nshared = MAX(nshared*nthread,reduct_size*nthread);

  //call kernel wrapper function, passing in pointers to data
  if (x_size > 0 && y_size > 0)
    ops_calc_dt_kernel_print<<<grid, tblock, nshared >>> (  (double *)p_a[0], (double *)p_a[1],
         (double *)p_a[2], (double *)p_a[3],
         (double *)p_a[4], (double *)p_a[5],
         (double *)arg6.data_d,x_size, y_size);

  cutilSafeCall(cudaGetLastError());

  mvReductArraysToHost(reduct_bytes);
  for ( int b=0; b<maxblocks; b++ ){
    for ( int d=0; d<12; d++ ){
      arg6h[d] = arg6h[d] + ((double *)arg6.data)[d+b*12];
    }
  }
  arg6.data = (char *)arg6h;

  if (OPS_diags>1) {
    cutilSafeCall(cudaDeviceSynchronize());
    ops_timers_core(&c1,&t1);
    OPS_kernels[54].time += t1-t2;
  }

  #ifndef OPS_LAZY
  ops_set_dirtybit_device(args, 7);
  #endif

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    OPS_kernels[54].mpi_time += t2-t1;
    OPS_kernels[54].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[54].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[54].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[54].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_kernels[54].transfer += ops_compute_transfer(dim, start, end, &arg4);
    OPS_kernels[54].transfer += ops_compute_transfer(dim, start, end, &arg5);
  }
}

#ifdef OPS_LAZY
void ops_par_loop_calc_dt_kernel_print(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3, ops_arg arg4, ops_arg arg5, ops_arg arg6) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 54;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 54;
  for ( int i=0; i<4; i++ ){
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 7;
  desc->args = (ops_arg*)malloc(7*sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg0.dat->index;
  desc->args[1] = arg1;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg1.dat->index;
  desc->args[2] = arg2;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg2.dat->index;
  desc->args[3] = arg3;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg3.dat->index;
  desc->args[4] = arg4;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg4.dat->index;
  desc->args[5] = arg5;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg5.dat->index;
  desc->args[6] = arg6;
  desc->function = ops_par_loop_calc_dt_kernel_print_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(54,"calc_dt_kernel_print");
  }
  ops_enqueue_kernel(desc);
}
#endif
