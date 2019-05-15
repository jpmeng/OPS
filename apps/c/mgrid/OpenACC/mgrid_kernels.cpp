//
// auto-generated by ops.py//

#include "./OpenACC/mgrid_common.h"

#include <openacc.h>

void ops_init_backend() {
  acc_set_device_num(ops_get_proc() % acc_get_num_devices(acc_device_nvidia),
                     acc_device_nvidia);
  ops_device_initialised_externally = 1;
}

void ops_decl_const_char(int dim, char const *type, int size, char *dat,
                         char const *name) {
  {
    printf("error: unknown const name\n");
    exit(1);
  }
}

// user kernel files
#include "mgrid_populate_kernel_1_openacc_kernel.cpp"
#include "mgrid_populate_kernel_3_openacc_kernel.cpp"
#include "mgrid_prolong_kernel_openacc_kernel.cpp"
#include "mgrid_restrict_kernel_openacc_kernel.cpp"
#include "prolong_check_openacc_kernel.cpp"
#include "restrict_check_openacc_kernel.cpp"
