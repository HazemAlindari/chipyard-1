#include <stdio.h>

// Simulate MMIO device
long int write_address = 0;
long int read_address = 1000;

void write_device(int *address, int value) {
    *address = value;
}

int read_device(int *address) {
    return *address;
}

int main() {
    int value = 123;
    printf("Writing value %d to device...\n", value);
    write_device(&write_address, value);
    //read_address = &write_address;
    int read_value = read_device(read_address);
    printf("Read value from device: %d\n", read_value);

    return 0;
}