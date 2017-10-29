//
// auto-generated by ops.py
//
__constant__ int xdim0_taylor_green_vortex_block0_20_kernel;
int xdim0_taylor_green_vortex_block0_20_kernel_h = -1;
__constant__ int ydim0_taylor_green_vortex_block0_20_kernel;
int ydim0_taylor_green_vortex_block0_20_kernel_h = -1;
__constant__ int xdim1_taylor_green_vortex_block0_20_kernel;
int xdim1_taylor_green_vortex_block0_20_kernel_h = -1;
__constant__ int ydim1_taylor_green_vortex_block0_20_kernel;
int ydim1_taylor_green_vortex_block0_20_kernel_h = -1;
__constant__ int xdim2_taylor_green_vortex_block0_20_kernel;
int xdim2_taylor_green_vortex_block0_20_kernel_h = -1;
__constant__ int ydim2_taylor_green_vortex_block0_20_kernel;
int ydim2_taylor_green_vortex_block0_20_kernel_h = -1;
__constant__ int xdim3_taylor_green_vortex_block0_20_kernel;
int xdim3_taylor_green_vortex_block0_20_kernel_h = -1;
__constant__ int ydim3_taylor_green_vortex_block0_20_kernel;
int ydim3_taylor_green_vortex_block0_20_kernel_h = -1;
__constant__ int xdim4_taylor_green_vortex_block0_20_kernel;
int xdim4_taylor_green_vortex_block0_20_kernel_h = -1;
__constant__ int ydim4_taylor_green_vortex_block0_20_kernel;
int ydim4_taylor_green_vortex_block0_20_kernel_h = -1;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4


#define OPS_ACC0(x,y,z) (x+xdim0_taylor_green_vortex_block0_20_kernel*(y)+xdim0_taylor_green_vortex_block0_20_kernel*ydim0_taylor_green_vortex_block0_20_kernel*(z))
#define OPS_ACC1(x,y,z) (x+xdim1_taylor_green_vortex_block0_20_kernel*(y)+xdim1_taylor_green_vortex_block0_20_kernel*ydim1_taylor_green_vortex_block0_20_kernel*(z))
#define OPS_ACC2(x,y,z) (x+xdim2_taylor_green_vortex_block0_20_kernel*(y)+xdim2_taylor_green_vortex_block0_20_kernel*ydim2_taylor_green_vortex_block0_20_kernel*(z))
#define OPS_ACC3(x,y,z) (x+xdim3_taylor_green_vortex_block0_20_kernel*(y)+xdim3_taylor_green_vortex_block0_20_kernel*ydim3_taylor_green_vortex_block0_20_kernel*(z))
#define OPS_ACC4(x,y,z) (x+xdim4_taylor_green_vortex_block0_20_kernel*(y)+xdim4_taylor_green_vortex_block0_20_kernel*ydim4_taylor_green_vortex_block0_20_kernel*(z))

//user function
__device__

void taylor_green_vortex_block0_20_kernel_gpu(double *rhou1 , double *rhoE , double *rho , double *rhou2 , double *rhou0)
{
   rho[OPS_ACC2(0,0,1)] = rho[OPS_ACC2(0,0,-1)];
   rho[OPS_ACC2(0,0,2)] = rho[OPS_ACC2(0,0,-2)];
   rhou0[OPS_ACC4(0,0,1)] = rhou0[OPS_ACC4(0,0,-1)];
   rhou0[OPS_ACC4(0,0,2)] = rhou0[OPS_ACC4(0,0,-2)];
   rhou1[OPS_ACC0(0,0,1)] = rhou1[OPS_ACC0(0,0,-1)];
   rhou1[OPS_ACC0(0,0,2)] = rhou1[OPS_ACC0(0,0,-2)];
   rhou2[OPS_ACC3(0,0,1)] = rhou2[OPS_ACC3(0,0,-1)];
   rhou2[OPS_ACC3(0,0,2)] = rhou2[OPS_ACC3(0,0,-2)];
   rhoE[OPS_ACC1(0,0,1)] = rhoE[OPS_ACC1(0,0,-1)];
   rhoE[OPS_ACC1(0,0,2)] = rhoE[OPS_ACC1(0,0,-2)];
}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4


__global__ void ops_taylor_green_vortex_block0_20_kernel(
double* __restrict arg0,
double* __restrict arg1,
double* __restrict arg2,
double* __restrict arg3,
double* __restrict arg4,
int size0,
int size1,
int size2 ){


  int idx_z = blockDim.z * blockIdx.z + threadIdx.z;
  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1*1 + idx_y * 1*1 * xdim0_taylor_green_vortex_block0_20_kernel + idx_z * 1*1 * xdim0_taylor_green_vortex_block0_20_kernel * ydim0_taylor_green_vortex_block0_20_kernel;
  arg1 += idx_x * 1*1 + idx_y * 1*1 * xdim1_taylor_green_vortex_block0_20_kernel + idx_z * 1*1 * xdim1_taylor_green_vortex_block0_20_kernel * ydim1_taylor_green_vortex_block0_20_kernel;
  arg2 += idx_x * 1*1 + idx_y * 1*1 * xdim2_taylor_green_vortex_block0_20_kernel + idx_z * 1*1 * xdim2_taylor_green_vortex_block0_20_kernel * ydim2_taylor_green_vortex_block0_20_kernel;
  arg3 += idx_x * 1*1 + idx_y * 1*1 * xdim3_taylor_green_vortex_block0_20_kernel + idx_z * 1*1 * xdim3_taylor_green_vortex_block0_20_kernel * ydim3_taylor_green_vortex_block0_20_kernel;
  arg4 += idx_x * 1*1 + idx_y * 1*1 * xdim4_taylor_green_vortex_block0_20_kernel + idx_z * 1*1 * xdim4_taylor_green_vortex_block0_20_kernel * ydim4_taylor_green_vortex_block0_20_kernel;

  if (idx_x < size0 && idx_y < size1 && idx_z < size2) {
    taylor_green_vortex_block0_20_kernel_gpu(arg0, arg1, arg2, arg3,
                   arg4);
  }

}

// host stub function
// host stub function
void ops_par_loop_taylor_green_vortex_block0_20_kernel_execute(ops_kernel_descriptor *desc) {
  #ifdef OPS_MPI
  ops_block block = desc->block;
  #endif
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];
  ops_arg arg3 = desc->args[3];
  ops_arg arg4 = desc->args[4];

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[5] = { arg0, arg1, arg2, arg3, arg4};


  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,5,range,6)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(6,"taylor_green_vortex_block0_20_kernel");
    OPS_kernels[6].count++;
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
  int xdim2 = args[2].dat->size[0];
  int ydim2 = args[2].dat->size[1];
  int xdim3 = args[3].dat->size[0];
  int ydim3 = args[3].dat->size[1];
  int xdim4 = args[4].dat->size[0];
  int ydim4 = args[4].dat->size[1];

  if (xdim0 != xdim0_taylor_green_vortex_block0_20_kernel_h || ydim0 != ydim0_taylor_green_vortex_block0_20_kernel_h || xdim1 != xdim1_taylor_green_vortex_block0_20_kernel_h || ydim1 != ydim1_taylor_green_vortex_block0_20_kernel_h || xdim2 != xdim2_taylor_green_vortex_block0_20_kernel_h || ydim2 != ydim2_taylor_green_vortex_block0_20_kernel_h || xdim3 != xdim3_taylor_green_vortex_block0_20_kernel_h || ydim3 != ydim3_taylor_green_vortex_block0_20_kernel_h || xdim4 != xdim4_taylor_green_vortex_block0_20_kernel_h || ydim4 != ydim4_taylor_green_vortex_block0_20_kernel_h) {
    cudaMemcpyToSymbolAsync( xdim0_taylor_green_vortex_block0_20_kernel, &xdim0, sizeof(int),0,cudaMemcpyHostToDevice,stream );
    xdim0_taylor_green_vortex_block0_20_kernel_h = xdim0;
    cudaMemcpyToSymbolAsync( ydim0_taylor_green_vortex_block0_20_kernel, &ydim0, sizeof(int),0,cudaMemcpyHostToDevice,stream );
    ydim0_taylor_green_vortex_block0_20_kernel_h = ydim0;
    cudaMemcpyToSymbolAsync( xdim1_taylor_green_vortex_block0_20_kernel, &xdim1, sizeof(int),0,cudaMemcpyHostToDevice,stream );
    xdim1_taylor_green_vortex_block0_20_kernel_h = xdim1;
    cudaMemcpyToSymbolAsync( ydim1_taylor_green_vortex_block0_20_kernel, &ydim1, sizeof(int),0,cudaMemcpyHostToDevice,stream );
    ydim1_taylor_green_vortex_block0_20_kernel_h = ydim1;
    cudaMemcpyToSymbolAsync( xdim2_taylor_green_vortex_block0_20_kernel, &xdim2, sizeof(int),0,cudaMemcpyHostToDevice,stream );
    xdim2_taylor_green_vortex_block0_20_kernel_h = xdim2;
    cudaMemcpyToSymbolAsync( ydim2_taylor_green_vortex_block0_20_kernel, &ydim2, sizeof(int),0,cudaMemcpyHostToDevice,stream );
    ydim2_taylor_green_vortex_block0_20_kernel_h = ydim2;
    cudaMemcpyToSymbolAsync( xdim3_taylor_green_vortex_block0_20_kernel, &xdim3, sizeof(int),0,cudaMemcpyHostToDevice,stream );
    xdim3_taylor_green_vortex_block0_20_kernel_h = xdim3;
    cudaMemcpyToSymbolAsync( ydim3_taylor_green_vortex_block0_20_kernel, &ydim3, sizeof(int),0,cudaMemcpyHostToDevice,stream );
    ydim3_taylor_green_vortex_block0_20_kernel_h = ydim3;
    cudaMemcpyToSymbolAsync( xdim4_taylor_green_vortex_block0_20_kernel, &xdim4, sizeof(int),0,cudaMemcpyHostToDevice,stream );
    xdim4_taylor_green_vortex_block0_20_kernel_h = xdim4;
    cudaMemcpyToSymbolAsync( ydim4_taylor_green_vortex_block0_20_kernel, &ydim4, sizeof(int),0,cudaMemcpyHostToDevice,stream );
    ydim4_taylor_green_vortex_block0_20_kernel_h = ydim4;
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, z_size);
  dim3 tblock(OPS_block_size_x,OPS_block_size_y,1);




  char *p_a[5];
  int dat0 = args[0].dat->elem_size;
  int dat1 = args[1].dat->elem_size;
  int dat2 = args[2].dat->elem_size;
  int dat3 = args[3].dat->elem_size;
  int dat4 = args[4].dat->elem_size;

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

  int base2 = args[2].dat->base_offset;
  base2 += dat2 * (start[0] * args[2].stencil->stride[0]);
  base2 += dat2 *
    args[2].dat->size[0] *
    (start[1] * args[2].stencil->stride[1]);
  base2 += dat2 *
    args[2].dat->size[0] *
    args[2].dat->size[1] *
    (start[2] * args[2].stencil->stride[2]);
  p_a[2] = (char *)args[2].dat->data_d + base2;

  int base3 = args[3].dat->base_offset;
  base3 += dat3 * (start[0] * args[3].stencil->stride[0]);
  base3 += dat3 *
    args[3].dat->size[0] *
    (start[1] * args[3].stencil->stride[1]);
  base3 += dat3 *
    args[3].dat->size[0] *
    args[3].dat->size[1] *
    (start[2] * args[3].stencil->stride[2]);
  p_a[3] = (char *)args[3].dat->data_d + base3;

  int base4 = args[4].dat->base_offset;
  base4 += dat4 * (start[0] * args[4].stencil->stride[0]);
  base4 += dat4 *
    args[4].dat->size[0] *
    (start[1] * args[4].stencil->stride[1]);
  base4 += dat4 *
    args[4].dat->size[0] *
    args[4].dat->size[1] *
    (start[2] * args[4].stencil->stride[2]);
  p_a[4] = (char *)args[4].dat->data_d + base4;


  ops_H_D_exchanges_device(args, 5);
  ops_halo_exchanges(args,5,range);

  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[6].mpi_time += t2-t1;
  }


  //call kernel wrapper function, passing in pointers to data
  ops_taylor_green_vortex_block0_20_kernel<<<grid, tblock, 0, stream >>> (  (double *)p_a[0], (double *)p_a[1],
           (double *)p_a[2], (double *)p_a[3],
           (double *)p_a[4],x_size, y_size, z_size);

  if (OPS_diags>1) {
    cutilSafeCall(cudaStreamSynchronize(stream));
    ops_timers_core(&c1,&t1);
    OPS_kernels[6].time += t1-t2;
  }

  ops_set_dirtybit_device(args, 5);
  ops_set_halo_dirtybit3(&args[0],range);
  ops_set_halo_dirtybit3(&args[1],range);
  ops_set_halo_dirtybit3(&args[2],range);
  ops_set_halo_dirtybit3(&args[3],range);
  ops_set_halo_dirtybit3(&args[4],range);

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    OPS_kernels[6].mpi_time += t2-t1;
    OPS_kernels[6].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[6].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[6].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[6].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_kernels[6].transfer += ops_compute_transfer(dim, start, end, &arg4);
  }
}

void ops_par_loop_taylor_green_vortex_block0_20_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3, ops_arg arg4) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->index = 6;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 6;
  for ( int i=0; i<6; i++ ){
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 5;
  desc->args = (ops_arg*)malloc(5*sizeof(ops_arg));
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
  desc->function = ops_par_loop_taylor_green_vortex_block0_20_kernel_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(6,"taylor_green_vortex_block0_20_kernel");
  }
  ops_enqueue_kernel(desc);
}
