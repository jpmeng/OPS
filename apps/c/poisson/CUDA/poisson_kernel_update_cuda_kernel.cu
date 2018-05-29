//
// auto-generated by ops.py
//
__constant__ int xdim0_poisson_kernel_update;
int xdim0_poisson_kernel_update_h = -1;
__constant__ int xdim1_poisson_kernel_update;
int xdim1_poisson_kernel_update_h = -1;

#undef OPS_ACC0
#undef OPS_ACC1


#define OPS_ACC0(x,y) (x+xdim0_poisson_kernel_update*(y))
#define OPS_ACC1(x,y) (x+xdim1_poisson_kernel_update*(y))

//user function
__device__

void poisson_kernel_update_gpu(const double *u2, double *u) {
  u[OPS_ACC1(0,0)] = u2[OPS_ACC0(0,0)];
}



#undef OPS_ACC0
#undef OPS_ACC1


__global__ void ops_poisson_kernel_update(
const double* __restrict arg0,
double* __restrict arg1,
int size0,
int size1 ){


  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1*1 + idx_y * 1*1 * xdim0_poisson_kernel_update;
  arg1 += idx_x * 1*1 + idx_y * 1*1 * xdim1_poisson_kernel_update;

  if (idx_x < size0 && idx_y < size1) {
    poisson_kernel_update_gpu(arg0, arg1);
  }

}

// host stub function
#ifndef OPS_LAZY
void ops_par_loop_poisson_kernel_update(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {
#else
#ifdef OPS_HYBRID
void ops_par_loop_poisson_kernel_update_execute_gpu(ops_kernel_descriptor *desc) {
#else
void ops_par_loop_poisson_kernel_update_execute(ops_kernel_descriptor *desc) {
#endif
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  #endif

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[2] = { arg0, arg1};


  #if CHECKPOINTING && !OPS_LAZY
  if (!ops_checkpointing_before(args,2,range,1)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(1,"poisson_kernel_update");
    OPS_kernels[1].count++;
    ops_timers_core(&c1,&t1);
  }

  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];
  #if OPS_MPI && !OPS_LAZY
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned) return;
  for ( int n=0; n<2; n++ ){
    start[n] = sb->decomp_disp[n];end[n] = sb->decomp_disp[n]+sb->decomp_size[n];
    if (start[n] >= range[2*n]) {
      start[n] = 0;
    }
    else {
      start[n] = range[2*n] - start[n];
    }
    if (sb->id_m[n]==MPI_PROC_NULL && range[2*n] < 0) start[n] = range[2*n];
    if (end[n] >= range[2*n+1]) {
      end[n] = range[2*n+1] - sb->decomp_disp[n];
    }
    else {
      end[n] = sb->decomp_size[n];
    }
    if (sb->id_p[n]==MPI_PROC_NULL && (range[2*n+1] > sb->decomp_disp[n]+sb->decomp_size[n]))
      end[n] += (range[2*n+1]-sb->decomp_disp[n]-sb->decomp_size[n]);
  }
  #else
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif

  int x_size = MAX(0,end[0]-start[0]);
  int y_size = MAX(0,end[1]-start[1]);

  int xdim0 = args[0].dat->size[0];
  int xdim1 = args[1].dat->size[0];

  if (xdim0 != xdim0_poisson_kernel_update_h || xdim1 != xdim1_poisson_kernel_update_h) {
    cudaMemcpyToSymbol( xdim0_poisson_kernel_update, &xdim0, sizeof(int) );
    xdim0_poisson_kernel_update_h = xdim0;
    cudaMemcpyToSymbol( xdim1_poisson_kernel_update, &xdim1, sizeof(int) );
    xdim1_poisson_kernel_update_h = xdim1;
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, 1);
  dim3 tblock(OPS_block_size_x,OPS_block_size_y,1);



  int dat0 = (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);
  int dat1 = (OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size);

  char *p_a[2];

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


  #ifndef OPS_LAZY
  ops_H_D_exchanges_device(args, 2);
  ops_halo_exchanges(args,2,range);
  #endif

  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[1].mpi_time += t2-t1;
  }


  //call kernel wrapper function, passing in pointers to data
  ops_poisson_kernel_update<<<grid, tblock >>> (  (double *)p_a[0], (double *)p_a[1],x_size, y_size);

  if (OPS_diags>1) {
    cutilSafeCall(cudaDeviceSynchronize());
    ops_timers_core(&c1,&t1);
    OPS_kernels[1].time += t1-t2;
  }

  #ifndef OPS_LAZY
  ops_set_dirtybit_device(args, 2);
  ops_set_halo_dirtybit3(&args[1],range);
  #endif

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    OPS_kernels[1].mpi_time += t2-t1;
    OPS_kernels[1].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[1].transfer += ops_compute_transfer(dim, start, end, &arg1);
  }
}

#ifdef OPS_HYBRID
void ops_par_loop_poisson_kernel_update_execute_cpu(ops_kernel_descriptor *desc);
void ops_par_loop_poisson_kernel_update_execute(ops_kernel_descriptor *desc) {
  if (desc->device == 1) {
    ops_par_loop_poisson_kernel_update_execute_gpu(desc);
  }
  else {
    ops_par_loop_poisson_kernel_update_execute_cpu(desc);
  }
}
#endif


#ifdef OPS_LAZY
void ops_par_loop_poisson_kernel_update(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 1;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 1;
  for ( int i=0; i<4; i++ ){
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 2;
  desc->args = (ops_arg*)malloc(2*sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg0.dat->index;
  desc->args[1] = arg1;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg1.dat->index;
  desc->function = ops_par_loop_poisson_kernel_update_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(1,"poisson_kernel_update");
  }
  ops_enqueue_kernel(desc);
}
#endif
