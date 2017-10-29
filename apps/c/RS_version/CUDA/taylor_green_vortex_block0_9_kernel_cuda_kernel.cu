//
// auto-generated by ops.py
//
__constant__ int xdim0_taylor_green_vortex_block0_9_kernel;
int xdim0_taylor_green_vortex_block0_9_kernel_h = -1;
__constant__ int ydim0_taylor_green_vortex_block0_9_kernel;
int ydim0_taylor_green_vortex_block0_9_kernel_h = -1;
__constant__ int xdim1_taylor_green_vortex_block0_9_kernel;
int xdim1_taylor_green_vortex_block0_9_kernel_h = -1;
__constant__ int ydim1_taylor_green_vortex_block0_9_kernel;
int ydim1_taylor_green_vortex_block0_9_kernel_h = -1;

#undef OPS_ACC0
#undef OPS_ACC1


#define OPS_ACC0(x,y,z) (x+xdim0_taylor_green_vortex_block0_9_kernel*(y)+xdim0_taylor_green_vortex_block0_9_kernel*ydim0_taylor_green_vortex_block0_9_kernel*(z))
#define OPS_ACC1(x,y,z) (x+xdim1_taylor_green_vortex_block0_9_kernel*(y)+xdim1_taylor_green_vortex_block0_9_kernel*ydim1_taylor_green_vortex_block0_9_kernel*(z))

//user function
__device__

void taylor_green_vortex_block0_9_kernel_gpu(const double *u1 , double *wk8)
{
    wk8[OPS_ACC1(0,0,0)] = rinv1*((rc2)*u1[OPS_ACC0(0,0,-2)] - rc3*u1[OPS_ACC0(0,0,-1)] + (rc3)*u1[OPS_ACC0(0,0,1)] -
      rc2*u1[OPS_ACC0(0,0,2)]);
}



#undef OPS_ACC0
#undef OPS_ACC1


__global__ void ops_taylor_green_vortex_block0_9_kernel(
const double* __restrict arg0,
double* __restrict arg1,
int size0,
int size1,
int size2 ){


  int idx_z = blockDim.z * blockIdx.z + threadIdx.z;
  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1*1 + idx_y * 1*1 * xdim0_taylor_green_vortex_block0_9_kernel + idx_z * 1*1 * xdim0_taylor_green_vortex_block0_9_kernel * ydim0_taylor_green_vortex_block0_9_kernel;
  arg1 += idx_x * 1*1 + idx_y * 1*1 * xdim1_taylor_green_vortex_block0_9_kernel + idx_z * 1*1 * xdim1_taylor_green_vortex_block0_9_kernel * ydim1_taylor_green_vortex_block0_9_kernel;

  if (idx_x < size0 && idx_y < size1 && idx_z < size2) {
    taylor_green_vortex_block0_9_kernel_gpu(arg0, arg1);
  }

}

// host stub function
void ops_par_loop_taylor_green_vortex_block0_9_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[2] = { arg0, arg1};


  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,2,range,17)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(17,"taylor_green_vortex_block0_9_kernel");
    OPS_kernels[17].count++;
    ops_timers_core(&c1,&t1);
  }

  //compute locally allocated range for the sub-block
  int start[3];
  int end[3];
  #ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned) return;
  for ( int n=0; n<3; n++ ){
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
  for ( int n=0; n<3; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif

  int x_size = MAX(0,end[0]-start[0]);
  int y_size = MAX(0,end[1]-start[1]);
  int z_size = MAX(0,end[2]-start[2]);

  int xdim0 = args[0].dat->size[0];
  int ydim0 = args[0].dat->size[1];
  int xdim1 = args[1].dat->size[0];
  int ydim1 = args[1].dat->size[1];

  if (xdim0 != xdim0_taylor_green_vortex_block0_9_kernel_h || ydim0 != ydim0_taylor_green_vortex_block0_9_kernel_h || xdim1 != xdim1_taylor_green_vortex_block0_9_kernel_h || ydim1 != ydim1_taylor_green_vortex_block0_9_kernel_h) {
    cudaMemcpyToSymbol( xdim0_taylor_green_vortex_block0_9_kernel, &xdim0, sizeof(int) );
    xdim0_taylor_green_vortex_block0_9_kernel_h = xdim0;
    cudaMemcpyToSymbol( ydim0_taylor_green_vortex_block0_9_kernel, &ydim0, sizeof(int) );
    ydim0_taylor_green_vortex_block0_9_kernel_h = ydim0;
    cudaMemcpyToSymbol( xdim1_taylor_green_vortex_block0_9_kernel, &xdim1, sizeof(int) );
    xdim1_taylor_green_vortex_block0_9_kernel_h = xdim1;
    cudaMemcpyToSymbol( ydim1_taylor_green_vortex_block0_9_kernel, &ydim1, sizeof(int) );
    ydim1_taylor_green_vortex_block0_9_kernel_h = ydim1;
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, z_size);
  dim3 tblock(OPS_block_size_x,OPS_block_size_y,1);



  int dat0 = args[0].dat->elem_size;
  int dat1 = args[1].dat->elem_size;

  char *p_a[2];

  //set up initial pointers
  int d_m[OPS_MAX_DIM];
  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d] + OPS_sub_dat_list[args[0].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d];
  #endif
  int base0 = dat0 * 1 *
  (start[0] * args[0].stencil->stride[0] - args[0].dat->base[0] - d_m[0]);
  base0 = base0+ dat0 *
    args[0].dat->size[0] *
    (start[1] * args[0].stencil->stride[1] - args[0].dat->base[1] - d_m[1]);
  base0 = base0+ dat0 *
    args[0].dat->size[0] *
    args[0].dat->size[1] *
    (start[2] * args[0].stencil->stride[2] - args[0].dat->base[2] - d_m[2]);
  p_a[0] = (char *)args[0].data_d + base0;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[1].dat->d_m[d] + OPS_sub_dat_list[args[1].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[1].dat->d_m[d];
  #endif
  int base1 = dat1 * 1 *
  (start[0] * args[1].stencil->stride[0] - args[1].dat->base[0] - d_m[0]);
  base1 = base1+ dat1 *
    args[1].dat->size[0] *
    (start[1] * args[1].stencil->stride[1] - args[1].dat->base[1] - d_m[1]);
  base1 = base1+ dat1 *
    args[1].dat->size[0] *
    args[1].dat->size[1] *
    (start[2] * args[1].stencil->stride[2] - args[1].dat->base[2] - d_m[2]);
  p_a[1] = (char *)args[1].data_d + base1;


  ops_H_D_exchanges_device(args, 2);
  ops_halo_exchanges(args,2,range);

  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[17].mpi_time += t2-t1;
  }


  //call kernel wrapper function, passing in pointers to data
  ops_taylor_green_vortex_block0_9_kernel<<<grid, tblock >>> (  (double *)p_a[0], (double *)p_a[1],x_size, y_size, z_size);

  if (OPS_diags>1) {
    cutilSafeCall(cudaDeviceSynchronize());
    ops_timers_core(&c1,&t1);
    OPS_kernels[17].time += t1-t2;
  }

  ops_set_dirtybit_device(args, 2);
  ops_set_halo_dirtybit3(&args[1],range);

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    OPS_kernels[17].mpi_time += t2-t1;
    OPS_kernels[17].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[17].transfer += ops_compute_transfer(dim, start, end, &arg1);
  }
}
