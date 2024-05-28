//All rights reserved by Hazem Al Indari
#ifndef __FPGA_MMIO_H__
#define __FPGA_MMIO_H__
#include "mmio.h"
#include <stdio.h>

#define FPGA_STATUS 0x5000
#define FPGA_RST 0x5002
#define FPGA_INPUT0ATTR_IN 0x5004
#define FPGA_INPUT1ATTR_IN 0x5006
#define FPGA_INPUT0ATTR_OUT 0x5008
#define FPGA_INPUT1ATTR_OUT 0x500A
#define FPGA_INPUT0 0x5010
#define FPGA_INPUT1 0x5018
#define FPGA_OUTPUT0 0x5020
#define FPGA_OUTPUT1 0x5028
#define bitsToBePrintedAtLeastConstant 16
#define FPGA_BUFFER_SIZE 256
#define DEBUG 0

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
void _buffer_write_FPGA(unsigned long inputAddress, unsigned long attrInAddress, unsigned long attrOutAddress, uint64_t* data, int size) {
  if (size > FPGA_BUFFER_SIZE) {
    printf("Size is too large for buffer\n");
    return;
  }
  uint16_t attrIn = 0b0000000011111111;
  for (int i = 0; i < size; i++) {
    if (DEBUG) printf("i = %d\n", i);
    if (i >= size - 1) { //if last data, set last bit of attrIn to 0
      attrIn = attrIn + 1; //increment attrIn
      attrIn = attrIn - 0b0000000100000000; //set last bit of attrIn to 0 //fix me later (make or operation instead of subtraction)
      if (DEBUG) printf("next attrIn = 0b");
      if (DEBUG) print_binary(attrIn,bitsToBePrintedAtLeastConstant);
    } else {
      attrIn = attrIn + 1; //increment attrIn
      if (DEBUG) printf("next attrIn = attrIn + 1 = 0b");
      if (DEBUG) print_binary(attrIn,bitsToBePrintedAtLeastConstant);
    }
    if (size == 1) { //if only one data, set last bit of attrIn to 0
    if (DEBUG) printf("size = 1\n");
      attrIn = 0b0000000000000000;
    }
    reg_write16(attrInAddress, attrIn); //write attrIn to input attribute
    if (DEBUG) printf("attrIn written successfully\n");
    if (DEBUG) printf("attrIn = 0b");
    if (DEBUG) print_binary(attrIn,bitsToBePrintedAtLeastConstant);
    if (DEBUG) printf("attrOut = 0b");
    if (DEBUG) print_binary(reg_read16(attrOutAddress),bitsToBePrintedAtLeastConstant);

    while (reg_read16(attrOutAddress) - 1 != attrIn) //check if input buffer is ready
     {
      printf("Waiting for input buffer to be ready\n");
      if (DEBUG) printf("attrIn = 0b");
      if (DEBUG) print_binary(attrIn,bitsToBePrintedAtLeastConstant);
      if (DEBUG) printf("attrOut = 0b");
      if (DEBUG) print_binary(reg_read16(attrOutAddress),bitsToBePrintedAtLeastConstant);
      //attrOut = reg_read16(attrOutAddress);
    }; 
    if(DEBUG) printf("input buffer is ready\n");
    reg_write64(inputAddress,data[i]); //write data to input buffer
    printf("Writing %ld to buffer[%d]\n", data[i], i);


  if (DEBUG) printf("\n\n\n");

  };
  if (DEBUG) printf("\n\n");
}
void wait_for_output_ready_FPGA() {
  //if output0,1 are ready => fpga completed calculations and loop exits
  while ((reg_read16(FPGA_STATUS) & 0b1100000000000000)  == 0) {
    printf("waiting for peripheral to complete\n");
    if (DEBUG) printf("FPGA_STATUS = 0b");
    if (DEBUG) print_binary(reg_read16(FPGA_STATUS),bitsToBePrintedAtLeastConstant);
  };
  printf("peripheral completed\n");
}
void write_input0_FPGA(uint64_t* data, int size) {
  _buffer_write_FPGA(FPGA_INPUT0, FPGA_INPUT0ATTR_IN, FPGA_INPUT0ATTR_OUT, data, size);
}
void write_input1_FPGA(uint64_t* data, int size) {
  _buffer_write_FPGA(FPGA_INPUT1, FPGA_INPUT1ATTR_IN, FPGA_INPUT1ATTR_OUT, data, size);
}
void print_output0_FPGA(uint64_t* data, int size) {
  for (int i = 0; i < size; i++) {
    data[i] = reg_read64(FPGA_OUTPUT0);
    printf("Reading %ld from buffer[%d]\n", data[i], i);
  }
}
uint64_t read_output0_FPGA() {
  return reg_read64(FPGA_OUTPUT0);
}
uint64_t read_output1_FPGA() {
  return reg_read64(FPGA_OUTPUT1);
}
void wait_for_inputs_receive_ready_FPGA() {
  //if input0,1 and idle state => fpga is ready and loop exits
  while ((reg_read16(FPGA_STATUS) & 0b0010000000000011) == 0) {
    printf("waiting for peripheral to be ready\n");
    if (DEBUG) printf("FPGA_STATUS = 0b");
    if (DEBUG) print_binary(reg_read16(FPGA_STATUS),bitsToBePrintedAtLeastConstant);
  };
  printf("peripheral is ready\n");
}

#endif
