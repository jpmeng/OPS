//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_viscosity_kernel;
int ydim0_viscosity_kernel;
int xdim1_viscosity_kernel;
int ydim1_viscosity_kernel;
int xdim2_viscosity_kernel;
int ydim2_viscosity_kernel;
int xdim3_viscosity_kernel;
int ydim3_viscosity_kernel;
int xdim4_viscosity_kernel;
int ydim4_viscosity_kernel;
int xdim5_viscosity_kernel;
int ydim5_viscosity_kernel;
int xdim6_viscosity_kernel;
int ydim6_viscosity_kernel;
int xdim7_viscosity_kernel;
int ydim7_viscosity_kernel;
int xdim8_viscosity_kernel;
int ydim8_viscosity_kernel;
int xdim9_viscosity_kernel;
int ydim9_viscosity_kernel;
int xdim10_viscosity_kernel;
int ydim10_viscosity_kernel;
int xdim11_viscosity_kernel;
int ydim11_viscosity_kernel;

//user function
#pragma acc routine
inline 
void viscosity_kernel(const ptr_double xvel0,
  const ptr_double yvel0,
  const ptr_double celldx,
  const ptr_double celldy,
  const ptr_double pressure,
  const ptr_double density0,
  ptr_double viscosity,
  const ptr_double zvel0,
  const ptr_double celldz,
  const ptr_double xarea,
  const ptr_double yarea,
  const ptr_double zarea) {

  double grad2,
         pgradx,pgrady,pgradz,
         pgradx2,pgrady2,pgradz2,
         grad,
         ygrad, xgrad, zgrad,
         div,
         limiter,
         pgrad;

  double ugradx1=OPS_ACC(xvel0, 0,0,0)+OPS_ACC(xvel0, 0,1,0)+OPS_ACC(xvel0, 0,0,1)+OPS_ACC(xvel0, 0,1,1);
  double ugradx2=OPS_ACC(xvel0, 1,0,0)+OPS_ACC(xvel0, 1,1,0)+OPS_ACC(xvel0, 1,0,1)+OPS_ACC(xvel0, 1,1,1);
  double ugrady1=OPS_ACC(xvel0, 0,0,0)+OPS_ACC(xvel0, 1,0,0)+OPS_ACC(xvel0, 0,0,1)+OPS_ACC(xvel0, 1,0,1);
  double ugrady2=OPS_ACC(xvel0, 0,1,0)+OPS_ACC(xvel0, 1,1,0)+OPS_ACC(xvel0, 0,1,1)+OPS_ACC(xvel0, 1,1,1);
  double ugradz1=OPS_ACC(xvel0, 0,0,0)+OPS_ACC(xvel0, 1,0,0)+OPS_ACC(xvel0, 0,1,0)+OPS_ACC(xvel0, 1,1,0);
  double ugradz2=OPS_ACC(xvel0, 0,0,1)+OPS_ACC(xvel0, 1,0,1)+OPS_ACC(xvel0, 0,1,1)+OPS_ACC(xvel0, 1,1,1);

  double vgradx1=OPS_ACC(yvel0, 0,0,0)+OPS_ACC(yvel0, 0,1,0)+OPS_ACC(yvel0, 0,0,1)+OPS_ACC(yvel0, 0,1,1);
  double vgradx2=OPS_ACC(yvel0, 1,0,0)+OPS_ACC(yvel0, 1,1,0)+OPS_ACC(yvel0, 1,0,1)+OPS_ACC(yvel0, 1,1,1);
  double vgrady1=OPS_ACC(yvel0, 0,0,0)+OPS_ACC(yvel0, 1,0,0)+OPS_ACC(yvel0, 0,0,1)+OPS_ACC(yvel0, 1,0,1);
  double vgrady2=OPS_ACC(yvel0, 0,1,0)+OPS_ACC(yvel0, 1,1,0)+OPS_ACC(yvel0, 0,1,1)+OPS_ACC(yvel0, 1,1,1);
  double vgradz1=OPS_ACC(yvel0, 0,0,0)+OPS_ACC(yvel0, 1,0,0)+OPS_ACC(yvel0, 0,1,0)+OPS_ACC(yvel0, 1,1,0);
  double vgradz2=OPS_ACC(yvel0, 0,0,1)+OPS_ACC(yvel0, 1,0,1)+OPS_ACC(yvel0, 0,1,1)+OPS_ACC(yvel0, 1,1,1);

  double wgradx1=OPS_ACC(zvel0, 0,0,0)+OPS_ACC(zvel0, 0,1,0)+OPS_ACC(zvel0, 0,0,1)+OPS_ACC(zvel0, 0,1,1);
  double wgradx2=OPS_ACC(zvel0, 1,0,0)+OPS_ACC(zvel0, 1,1,0)+OPS_ACC(zvel0, 1,0,1)+OPS_ACC(zvel0, 1,1,1);
  double wgrady1=OPS_ACC(zvel0, 0,0,0)+OPS_ACC(zvel0, 1,0,0)+OPS_ACC(zvel0, 0,0,1)+OPS_ACC(zvel0, 1,0,1);
  double wgrady2=OPS_ACC(zvel0, 0,1,0)+OPS_ACC(zvel0, 1,1,0)+OPS_ACC(zvel0, 0,1,1)+OPS_ACC(zvel0, 1,1,1);
  double wgradz1=OPS_ACC(zvel0, 0,0,0)+OPS_ACC(zvel0, 1,0,0)+OPS_ACC(zvel0, 0,1,0)+OPS_ACC(zvel0, 1,1,0);
  double wgradz2=OPS_ACC(zvel0, 0,0,1)+OPS_ACC(zvel0, 1,0,1)+OPS_ACC(zvel0, 0,1,1)+OPS_ACC(zvel0, 1,1,1);

  div = OPS_ACC(xarea, 0,0,0)*(ugradx2-ugradx1) + OPS_ACC(yarea, 0,0,0)*(vgrady2-vgrady1) + OPS_ACC(zarea, 0,0,0)*(wgradz2-wgradz1);

  double xx = 0.25*(ugradx2-ugradx1)/(OPS_ACC(celldx, 0,0,0));
  double yy = 0.25*(vgrady2-vgrady1)/(OPS_ACC(celldy, 0,0,0));
  double zz = 0.25*(wgradz2-wgradz1)/(OPS_ACC(celldz, 0,0,0));
  double xy = 0.25*(ugrady2-ugrady1)/(OPS_ACC(celldy, 0,0,0))+0.25*(vgradx2-vgradx1)/(OPS_ACC(celldx, 0,0,0));
  double xz = 0.25*(ugradz2-ugradz1)/(OPS_ACC(celldz, 0,0,0))+0.25*(wgradx2-wgradx1)/(OPS_ACC(celldx, 0,0,0));
  double yz = 0.25*(vgradz2-vgradz1)/(OPS_ACC(celldz, 0,0,0))+0.25*(wgrady2-wgrady1)/(OPS_ACC(celldy, 0,0,0));


  pgradx = (OPS_ACC(pressure, 1,0,0) - OPS_ACC(pressure, -1,0,0))/(OPS_ACC(celldx, 0,0,0)+ OPS_ACC(celldx, 1,0,0));
  pgrady = (OPS_ACC(pressure, 0,1,0) - OPS_ACC(pressure, 0,-1,0))/(OPS_ACC(celldy, 0,0,0)+ OPS_ACC(celldy, 0,1,0));
  pgradz = (OPS_ACC(pressure, 0,0,1) - OPS_ACC(pressure, 0,0,-1))/(OPS_ACC(celldz, 0,0,0)+ OPS_ACC(celldz, 0,0,1));

  pgradx2 = pgradx * pgradx;
  pgrady2 = pgrady * pgrady;
  pgradz2 = pgradz * pgradz;
  limiter = (xx*pgradx2+yy*pgrady2+zz*pgradz2
          +  xy*pgradx*pgrady+xz*pgradx*pgradz+yz*pgrady*pgradz)
                / MAX(pgradx2+pgrady2+pgradz2,1.0e-16);

  if( (limiter > 0.0) || (div >= 0.0)) {
        OPS_ACC(viscosity, 0,0,0) = 0.0;
  }
  else {
    pgradx = SIGN( MAX(1.0e-16, fabs(pgradx)), pgradx);
    pgrady = SIGN( MAX(1.0e-16, fabs(pgrady)), pgrady);
    pgradz = SIGN( MAX(1.0e-16, fabs(pgradz)), pgradz);
    pgrad = sqrt(pgradx*pgradx + pgrady*pgrady + pgradz*pgradz);
    xgrad = fabs(OPS_ACC(celldx, 0,0,0) * pgrad/pgradx);
    ygrad = fabs(OPS_ACC(celldy, 0,0,0) * pgrad/pgrady);
    zgrad = fabs(OPS_ACC(celldz, 0,0,0) * pgrad/pgradz);
    grad  = MIN(xgrad,MIN(ygrad,zgrad));
    grad2 = grad*grad;

    OPS_ACC(viscosity, 0,0,0) = 2.0 * (OPS_ACC(density0, 0,0,0)) * grad2 * limiter * limiter;
  }
}


void viscosity_kernel_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  double *p_a4,
  double *p_a5,
  double *p_a6,
  double *p_a7,
  double *p_a8,
  double *p_a9,
  double *p_a10,
  double *p_a11,
  int x_size, int y_size, int z_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2,p_a3,p_a4,p_a5,p_a6,p_a7,p_a8,p_a9,p_a10,p_a11)
  #pragma acc loop
  #endif
  for ( int n_z=0; n_z<z_size; n_z++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_y=0; n_y<y_size; n_y++ ){
      #ifdef OPS_GPU
      #pragma acc loop
      #endif
      for ( int n_x=0; n_x<x_size; n_x++ ){
        const ptr_double ptr0 = {  p_a0 + n_x*1*1 + n_y*xdim0_viscosity_kernel*1*1 + n_z*xdim0_viscosity_kernel*ydim0_viscosity_kernel*1*1, xdim0_viscosity_kernel, ydim0_viscosity_kernel};
        const ptr_double ptr1 = {  p_a1 + n_x*1*1 + n_y*xdim1_viscosity_kernel*1*1 + n_z*xdim1_viscosity_kernel*ydim1_viscosity_kernel*1*1, xdim1_viscosity_kernel, ydim1_viscosity_kernel};
        const ptr_double ptr2 = {  p_a2 + n_x*1*1 + n_y*xdim2_viscosity_kernel*0*1 + n_z*xdim2_viscosity_kernel*ydim2_viscosity_kernel*0*1, xdim2_viscosity_kernel, ydim2_viscosity_kernel};
        const ptr_double ptr3 = {  p_a3 + n_x*0*1 + n_y*xdim3_viscosity_kernel*1*1 + n_z*xdim3_viscosity_kernel*ydim3_viscosity_kernel*0*1, xdim3_viscosity_kernel, ydim3_viscosity_kernel};
        const ptr_double ptr4 = {  p_a4 + n_x*1*1 + n_y*xdim4_viscosity_kernel*1*1 + n_z*xdim4_viscosity_kernel*ydim4_viscosity_kernel*1*1, xdim4_viscosity_kernel, ydim4_viscosity_kernel};
        const ptr_double ptr5 = {  p_a5 + n_x*1*1 + n_y*xdim5_viscosity_kernel*1*1 + n_z*xdim5_viscosity_kernel*ydim5_viscosity_kernel*1*1, xdim5_viscosity_kernel, ydim5_viscosity_kernel};
        ptr_double ptr6 = {  p_a6 + n_x*1*1 + n_y*xdim6_viscosity_kernel*1*1 + n_z*xdim6_viscosity_kernel*ydim6_viscosity_kernel*1*1, xdim6_viscosity_kernel, ydim6_viscosity_kernel};
        const ptr_double ptr7 = {  p_a7 + n_x*1*1 + n_y*xdim7_viscosity_kernel*1*1 + n_z*xdim7_viscosity_kernel*ydim7_viscosity_kernel*1*1, xdim7_viscosity_kernel, ydim7_viscosity_kernel};
        const ptr_double ptr8 = {  p_a8 + n_x*0*1 + n_y*xdim8_viscosity_kernel*0*1 + n_z*xdim8_viscosity_kernel*ydim8_viscosity_kernel*1*1, xdim8_viscosity_kernel, ydim8_viscosity_kernel};
        const ptr_double ptr9 = {  p_a9 + n_x*1*1 + n_y*xdim9_viscosity_kernel*1*1 + n_z*xdim9_viscosity_kernel*ydim9_viscosity_kernel*1*1, xdim9_viscosity_kernel, ydim9_viscosity_kernel};
        const ptr_double ptr10 = {  p_a10 + n_x*1*1 + n_y*xdim10_viscosity_kernel*1*1 + n_z*xdim10_viscosity_kernel*ydim10_viscosity_kernel*1*1, xdim10_viscosity_kernel, ydim10_viscosity_kernel};
        const ptr_double ptr11 = {  p_a11 + n_x*1*1 + n_y*xdim11_viscosity_kernel*1*1 + n_z*xdim11_viscosity_kernel*ydim11_viscosity_kernel*1*1, xdim11_viscosity_kernel, ydim11_viscosity_kernel};
        viscosity_kernel( ptr0,
          ptr1,
          ptr2,
          ptr3,
          ptr4,
          ptr5,
          ptr6,
          ptr7,
          ptr8,
          ptr9,
          ptr10,
          ptr11 );

      }
    }
  }
}
