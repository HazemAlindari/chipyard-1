//All rights reserved by Hazem Al Indari
#include "mmio_FPGA.h"
#include <stdio.h>

unsigned int fpga_ref(unsigned int x, unsigned int y) {
  while (y != 0) {
    if (x > y)
      x = x - y;
    else
      y = y - x;
  }
  return x;
}

//FPGA test
int main(void)
{
  uint64_t z, ref, x = 20, y = 15;
  uint64_t input0[] = {x};
  uint64_t input1[] = {y};
  reset_FPGA();

  // wait for peripheral to be ready
  wait_for_inputs_receive_ready_FPGA();

  //writing inputs to buffer
  write_input0_FPGA(input0, 1);
  write_input1_FPGA(input1, 1);

  // wait for peripheral to complete
  wait_for_output_ready_FPGA();
  
  z = read_output0_FPGA();
  ref = fpga_ref(x, y);

  if (z != ref) {
    printf("Hardware result %ld does not match reference value %ld\n", z, ref);
    return 1;
  }
  printf("Hardware result %ld is correct for FPGA\n", z);
  return 0;
}
