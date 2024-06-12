//All rights reserved by Hazem Al Indari
#ifndef __FPGA_MMIO_H__
#define __FPGA_MMIO_H__
#include "mmio.h"
#include <stdio.h>

#define FPGA_STATUS 0x5000
#define FPGA_RST 0x5002
#define FPGA_INPUT0ATTR_IN 0x5004
#define FPGA_INPUT0ATTR_OUT 0x5006
#define FPGA_INPUT0 0x5010
#define FPGA_OUTPUT0 0x5018
#define FPGA_OUTPUT1 0x5020
#define FPGA_OUTPUT2 0x5028
#define FPGA_OUTPUT3 0x5030
#define FPGA_OUTPUT4 0x5038
#define FPGA_OUTPUT5 0x5040
#define FPGA_OUTPUT6 0x5048
#define FPGA_OUTPUT7 0x5050
#define bitsToBePrintedAtLeastConstant 16
#define FPGA_BUFFER_SIZE 256
#define DEBUG 1

//helper functions
void print_binary(int num, int bitsToBePrintedAtLeast) {
    int bitsToBePrinted = bitsToBePrintedAtLeast;
    int binary[bitsToBePrinted];

    for (int j = bitsToBePrinted - 1; j >= 0; j--) {
        binary[j] = num % 2;
        num = num / 2;
    }

    for (int j = 0; j < bitsToBePrinted; j++) {
        printf("%d", binary[j]);
    }
    printf("\n");
}
void reset_FPGA() {
    uint8_t rst = 0b11111111;
    reg_write16(FPGA_RST,rst);
    reg_write16(FPGA_RST,0);
    printf("FPGA reset\n");
}

//input functions
void wait_for_inputs_receive_ready_FPGA() {
    //if input0,1 and idle state => fpga is ready and loop exits
    while ((reg_read16(FPGA_STATUS) & 0b0010000000000001) == 0) {
        printf("waiting for peripheral to be ready\n");
        if (DEBUG) printf("FPGA_STATUS = 0b");
        if (DEBUG) print_binary(reg_read16(FPGA_STATUS),bitsToBePrintedAtLeastConstant);
    };
    printf("peripheral is ready\n");
}
int write_input0_FPGA(uint64_t* data, int size) {
    wait_for_inputs_receive_ready_FPGA();
    return _buffer_write_FPGA(FPGA_INPUT0, FPGA_INPUT0ATTR_IN, FPGA_INPUT0ATTR_OUT, data, size);
}
int _buffer_write_FPGA(unsigned long inputAddress, unsigned long attrInAddress, unsigned long attrOutAddress, uint8_t* data, int size) {

    int byte_num = ((size % 8) * (2 ^ 13)); //byte number to be embedded in the last 3 bits of the last attrIn
    
    //add an empty element to the buffer if size is a multiple of 8
    int emptyElement = 0; //set to true if size is a multiple of 8
    if (size % 8 == 0) {
        if (DEBUG) printf("Size is a multiple of 8\n");
        emptyElement = 1; //set to true if size is a multiple of 8
        size = size + 1; //add one to size to write the last data
    }

    //fill data with 0s until it's a multiple of 8
    while (size % 8 != 0) {
        data[size] = 0;
        size = size + 1;
    }

    size = size / 8; //convert size to number of 64-bit data
    //check if size is too large for buffer
    if (size > FPGA_BUFFER_SIZE) {
        printf("Size is too large for buffer\n");
        return 1;
    }

    //convert data to 64-bit
    uint64_t data64[size];
    for (int i = 0; i < size; i++) {
        data64[i] = 0;
        for (int j = 0; j < 8; j++) {
            data64[i] = data64[i] + (data[i * 8 + j] * (2 ^ (8 * (7 - j))));
        }
    }

    //write data to buffer
    uint16_t attrIn = 0b0000000011111111;
    for (int i = 0; i < size; i++) {
        if (DEBUG) printf("i = %d\n", i);

        //if last data, set last bit of attrIn to 0
        if (i >= size - 1) { 
            attrIn = attrIn + 1; //increment attrIn
            attrIn = attrIn - 0b0000000100000000; //set last bit of attrIn to 0 //fix me later (make or operation instead of subtraction)
            attrIn = attrIn + byte_num; //add byte number to the last 3 bits of attrIn
            if (DEBUG) printf("next attrIn = 0b");
            if (DEBUG) print_binary(attrIn,bitsToBePrintedAtLeastConstant);
        } else {
            attrIn = attrIn + 1; //increment attrIn
            if (DEBUG) printf("next attrIn = attrIn + 1 = 0b");
            if (DEBUG) print_binary(attrIn,bitsToBePrintedAtLeastConstant);
        }

        //if only one data, set last bit of attrIn to 0
        if (size == 1) { 
        if (DEBUG) printf("size = 1\n");
            attrIn = 0b0000000000000000;
        }
        
        //write attrIn to input attribute
        reg_write16(attrInAddress, attrIn); 
        if (DEBUG) printf("attrIn written successfully\n");
        if (DEBUG) printf("attrIn = 0b");
        if (DEBUG) print_binary(attrIn,bitsToBePrintedAtLeastConstant);
        if (DEBUG) printf("attrOut = 0b");
        if (DEBUG) print_binary(reg_read16(attrOutAddress),bitsToBePrintedAtLeastConstant);

        //check if input buffer is ready
        while (reg_read16(attrOutAddress) - 1 != attrIn) 
         {
            printf("Waiting for input buffer to be ready\n");
            if (DEBUG) printf("attrIn = 0b");
            if (DEBUG) print_binary(attrIn,bitsToBePrintedAtLeastConstant);
            if (DEBUG) printf("attrOut = 0b");
            if (DEBUG) print_binary(reg_read16(attrOutAddress),bitsToBePrintedAtLeastConstant);
        }; 
        if(DEBUG) printf("input buffer is ready\n");

        //if last data and size is a multiple of 8, write 0 to the buffer
        if (i == size && emptyElement == 1) { 
            if (DEBUG) printf("Writing 0 to buffer[%d]\n", i);
            reg_write64(inputAddress,0); //write 0 to input buffer
            if (DEBUG) printf("\n\n\n");
            //continue;
        } else {
            if (DEBUG) printf("Writing %ld to buffer[%d]\n", data64[i], i);
            reg_write64(inputAddress,data64[i]); //write data to input buffer
            if (DEBUG) printf("\n\n\n");
        }
    };
    if (DEBUG) printf("\n\n");
    return 0;
}

//output functions
void wait_for_output_ready_FPGA() {
    //if output0 is ready => fpga completed calculations and loop exits
    while ((reg_read16(FPGA_STATUS) & 0b0100000000000000)    == 0) {
        printf("waiting for peripheral to complete\n");
        if (DEBUG) printf("FPGA_STATUS = 0b");
        if (DEBUG) print_binary(reg_read16(FPGA_STATUS),bitsToBePrintedAtLeastConstant);
    };
    printf("peripheral completed\n");
}
uint64_t read_output0_FPGA() {
    return reg_read64(FPGA_OUTPUT0);
}
uint64_t read_output1_FPGA() {
    return reg_read64(FPGA_OUTPUT1);
}
uint64_t read_output2_FPGA() {
    return reg_read64(FPGA_OUTPUT2);
}
uint64_t read_output3_FPGA() {
    return reg_read64(FPGA_OUTPUT3);
}
uint64_t read_output4_FPGA() {
    return reg_read64(FPGA_OUTPUT4);
}
uint64_t read_output5_FPGA() {
    return reg_read64(FPGA_OUTPUT5);
}
uint64_t read_output6_FPGA() {
    return reg_read64(FPGA_OUTPUT6);
}
uint64_t read_output7_FPGA() {
    return reg_read64(FPGA_OUTPUT7);
}
uint512_t read_outputs_FPGA() {
        uint512_t outputs;
        memset (&outputs, 0, sizeof(outputs));
        outputs.val0 = read_output0_FPGA();
        outputs.val1 = read_output1_FPGA();
        outputs.val2 = read_output2_FPGA();
        outputs.val3 = read_output3_FPGA();
        outputs.val4 = read_output4_FPGA();
        outputs.val5 = read_output5_FPGA();
        outputs.val6 = read_output6_FPGA();
        outputs.val7 = read_output7_FPGA();
        return outputs;
}
void print_output0_FPGA() {
    printf("Output0 = %ld\n", read_output0_FPGA());
}
void print_output1_FPGA() {
    printf("Output1 = %ld\n", read_output1_FPGA());
}
void print_output2_FPGA() {
    printf("Output2 = %ld\n", read_output2_FPGA());
}
void print_output3_FPGA() {
    printf("Output3 = %ld\n", read_output3_FPGA());
}
void print_output4_FPGA() {
    printf("Output4 = %ld\n", read_output4_FPGA());
}
void print_output5_FPGA() {
    printf("Output5 = %ld\n", read_output5_FPGA());
}
void print_output6_FPGA() {
    printf("Output6 = %ld\n", read_output6_FPGA());
}
void print_output7_FPGA() {
    printf("Output7 = %ld\n", read_output7_FPGA());
}
void print_outputs_FPGA() {
        printf("Output = ");
        printf("%ld ", read_output0_FPGA());
        printf("%ld ", read_output1_FPGA());
        printf("%ld ", read_output2_FPGA());
        printf("%ld ", read_output3_FPGA());
        printf("%ld ", read_output4_FPGA());
        printf("%ld ", read_output5_FPGA());
        printf("%ld ", read_output6_FPGA());
        printf("%ld\n", read_output7_FPGA());
}


#endif
