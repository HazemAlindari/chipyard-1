//All rights reserved by Hazem Al Indari
//FIXME: change the test to sha3
#include "mmio_FPGA.h"
#include "mmio.h"
#include <stdio.h>

#define REF0 0xb42137958fda58b4
#define REF1 0xbfcb5ae5a6ae59f3
#define REF2 0xf8e187be068126e3
#define REF3 0x32f385815f2715f5
#define REF4 0x800c9539448931be
#define REF5 0x3f94169dc2763760
#define REF6 0xea429581c987efe4
#define REF7 0x28c2b500d9fde90e

//FPGA test
int main(void)
{
    //uint64_t z, ref, x = 20, y = 15;
    //uint64_t input0[] = {x,0};
    //uint64_t input1[] = {y,0,0};
    //int input0Size = sizeof(input0) / sizeof(input0[0]);
    //int input1Size = sizeof(input1) / sizeof(input1[0]);
    uint64_t output[8], ref[8];
    reset_FPGA();

    uint8_t input[] = {0b01010100 ,0b01101000 ,0b01100101 ,0b00100000 ,0b01110001 ,0b01110101 ,0b01101001 ,0b01100011, 0b01101011, 0b00101110};
    int input0Size = sizeof(input) / sizeof(input[0]);

    reset_FPGA();
    
    // wait for peripheral to be ready
    wait_for_inputs_receive_ready_FPGA();

    //riting inputs to buffer
    if ((write_input0_FPGA(input, input0Size))) {
        printf("Error writing input0\n");
        return 1;
    }
    
    // wait for peripheral to complete
    wait_for_output_ready_FPGA();

    read_outputs_FPGA(output);
    ref[0] = REF0;
    ref[1] = REF1;
    ref[2] = REF2;
    ref[3] = REF3;
    ref[4] = REF4;
    ref[5] = REF5;
    ref[6] = REF6;
    ref[7] = REF7;

    int noMatch = 0;
    for (int i = 0; i < input0Size; i++) {
        if (output[i] != ref[i]) {
            noMatch = 1;
            break;
        }
    }
    if (noMatch) {
        printf("Hardware result is incorrect for sha3\n");
        printf("Expected: %#lx %#lx %#lx %#lx %#lx %lx %lx %lx\n", ref[0], ref[1], ref[2], ref[3], ref[4], ref[5], ref[6], ref[7]);
        printf("Got     : %#lx %#lx %#lx %#lx %#lx %lx %lx %lx\n", output[0], output[1], output[2], output[3], output[4], output[5], output[6], output[7]);
    } else {
        printf("Hardware result is correct for sha3\n");
        printf("Got back: %#lx, %#lx, %#lx, %#lx, %#lx, %lx, %lx, %lx\n", output[0], output[1], output[2], output[3], output[4], output[5], output[6], output[7]);
    }

    return 0;
}
