//
// auto-generated by ops.py
//
__constant__ int xdim0_taylor_green_vortex_block0_7_kernel;
int xdim0_taylor_green_vortex_block0_7_kernel_h = -1;
__constant__ int ydim0_taylor_green_vortex_block0_7_kernel;
int ydim0_taylor_green_vortex_block0_7_kernel_h = -1;
__constant__ int xdim1_taylor_green_vortex_block0_7_kernel;
int xdim1_taylor_green_vortex_block0_7_kernel_h = -1;
__constant__ int ydim1_taylor_green_vortex_block0_7_kernel;
int ydim1_taylor_green_vortex_block0_7_kernel_h = -1;

#undef OPS_ACC0
#undef OPS_ACC1


#define OPS_ACC0(x,y,z) (x+xdim0_taylor_green_vortex_block0_7_kernel*(y)+xdim0_taylor_green_vortex_block0_7_kernel*ydim0_taylor_green_vortex_block0_7_kernel*(z))
#define OPS_ACC1(x,y,z) (x+xdim1_taylor_green_vortex_block0_7_kernel*(y)+xdim1_taylor_green_vortex_block0_7_kernel*ydim1_taylor_green_vortex_block0_7_kernel*(z))

//user function
__device__

void taylor_green_vortex_block0_7_kernel_gpu(const double *u0 , double *wk6)
{
    wk6[OPS_ACC1(0,0,0)] = rinv5*((rc2)*u0[OPS_ACC0(-2,0,0)] - rc3*u0[OPS_ACC0(-1,0,0)] + (rc3)*u0[OPS_ACC0(1,0,0)] -
      rc2*u0[OPS_ACC0(2,0,0)]);
}



#undef OPS_ACC0
#undef OPS_ACC1


__global__ void ops_taylor_green_vortex_block0_7_kernel(
const double* __restrict arg0,
double* __restrict arg1,
int size0,
int size1,
int size2 ){


  int idx_z = blockDim.z * blockIdx.z + threadIdx.z;
  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1*1 + idx_y * 1*1 * xdim0_taylor_green_vortex_block0_7_kernel + idx_z * 1*1 * xdim0_taylor_green_vortex_block0_7_kernel * ydim0_taylor_green_vortex_block0_7_kernel;
  arg1 += idx_x * 1*1 + idx_y * 1*1 * xdim1_taylor_green_vortex_block0_7_kernel + idx_z * 1*1 * xdim1_taylor_green_vortex_block0_7_kernel * ydim1_taylor_green_vortex_block0_7_kernel;

  if (idx_x < size0 && idx_y < size1 && idx_z < size2) {
    taylor_green_vortex_block0_7_kernel_gpu(arg0, arg1);
  }

}

// host stub function
// host stub function
void ops_par_loop_taylor_green_vortex_block0_7_kernel_execute(ops_kernel_descriptor *desc) {
  #ifdef OPS_MPI
  ops_block block = desc->block;
  #endif
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[2] = { arg0, arg1};


  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,2,range,15)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(15,"taylor_green_vortex_block0_7_kernel");
    OPS_kernels[15].count++;
    ops_timers_core(&c1,&t1);
  }

  //compute locally allocated range for the sub-block
  int start[3];
  int end[3];

  for ( int n=0; n<3; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }


  int x_size = MAX(0,end[0]-start[0]);
  int y_size = MAX(0,end[1]-start[1]);
  int z_size = MAX(0,end[2]-start[2]);

  int xdim0 = args[0].dat->size[0];
  int ydim0 = args[0].dat->size[1];
  int xdim1 = args[1].dat->size[0];
  int ydim1 = args[1].dat->size[1];

  if (xdim0 != xdim0_taylor_green_vortex_block0_7_kernel_h || ydim0 != ydim0_taylor_green_vortex_block0_7_kernel_h || xdim1 != xdim1_taylor_green_vortex_block0_7_kernel_h || ydim1 != ydim1_taylor_green_vortex_block0_7_kernel_h) {
    cudaMemcpyToSymbolAsync( xdim0_taylor_green_vortex_block0_7_kernel, &xdim0, sizeof(int),0,cudaMemcpyHostToDevice,stream );
    xdim0_taylor_green_vortex_block0_7_kernel_h = xdim0;
    cudaMemcpyToSymbolAsync( ydim0_taylor_green_vortex_block0_7_kernel, &ydim0, sizeof(int),0,cudaMemcpyHostToDevice,stream );
    ydim0_taylor_green_vortex_block0_7_kernel_h = ydim0;
    cudaMemcpyToSymbolAsync( xdim1_taylor_green_vortex_block0_7_kernel, &xdim1, sizeof(int),0,cudaMemcpyHostToDevice,stream );
    xdim1_taylor_green_vortex_block0_7_kernel_h = xdim1;
    cudaMemcpyToSymbolAsync( ydim1_taylor_green_vortex_block0_7_kernel, &ydim1, sizeof(int),0,cudaMemcpyHostToDevice,stream );
    ydim1_taylor_green_vortex_block0_7_kernel_h = ydim1;
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, z_size);
  dim3 tblock(OPS_block_size_x,OPS_block_size_y,1);




  char *p_a[2];
  int dat0 = args[0].dat->elem_size;
  int dat1 = args[1].dat->elem_size;

  //set up initial pointers
  int base0 = args[0].dat->base_offset;
  base0 += dat0 * (start[0] * args[0].stencil->stride[0]);
  base0 += dat0 *
    args[0].dat->size[0] *
    (start[1] * args[0].stencil->stride[1]);
  base0 += dat0 *
    args[0].dat->size[0] *
    args[0].dat->size[1] *
    (start[2] * args[0].stencil->stride[2]);
  p_a[0] = (char *)args[0].dat->data_d + base0;

  int base1 = args[1].dat->base_offset;
  base1 += dat1 * (start[0] * args[1].stencil->stride[0]);
  base1 += dat1 *
    args[1].dat->size[0] *
    (start[1] * args[1].stencil->stride[1]);
  base1 += dat1 *
    args[1].dat->size[0] *
    args[1].dat->size[1] *
    (start[2] * args[1].stencil->stride[2]);
  p_a[1] = (char *)args[1].dat->data_d + base1;


  ops_H_D_exchanges_device(args, 2);
  ops_halo_exchanges(args,2,range);

  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[15].mpi_time += t2-t1;
  }


  //call kernel wrapper function, passing in pointers to data
  ops_taylor_green_vortex_block0_7_kernel<<<grid, tblock, 0, stream >>> (  (double *)p_a[0], (double *)p_a[1],x_size, y_size, z_size);

  if (OPS_diags>1) {
    cutilSafeCall(cudaStreamSynchronize(stream));
    ops_timers_core(&c1,&t1);
    OPS_kernels[15].time += t1-t2;
  }

  ops_set_dirtybit_device(args, 2);
  ops_set_halo_dirtybit3(&args[1],range);

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    OPS_kernels[15].mpi_time += t2-t1;
    OPS_kernels[15].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[15].transfer += ops_compute_transfer(dim, start, end, &arg1);
  }
}

void ops_par_loop_taylor_green_vortex_block0_7_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->index = 15;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 15;
  for ( int i=0; i<6; i++ ){
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
  desc->function = ops_par_loop_taylor_green_vortex_block0_7_kernel_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(15,"taylor_green_vortex_block0_7_kernel");
  }
  ops_enqueue_kernel(desc);
}
