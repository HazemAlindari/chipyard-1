#include <stdio.h>

int main() {

    int intType;
    long longType;
    unsigned int unsignedIntType;
    long long longLongType;
    double doubleType;
    float floatType;
    char charType;

    printf("Size of int: %lu bytes\n", sizeof(intType));
    printf("Size of long: %lu bytes\n", sizeof(longType));
    printf("Size of unsigned int: %lu bytes\n", sizeof(unsignedIntType));
    printf("Size of long long: %lu bytes\n", sizeof(longLongType));
    printf("Size of double: %lu bytes\n", sizeof(doubleType));
    printf("Size of float: %lu bytes\n", sizeof(floatType));
    printf("Size of char: %lu bytes\n", sizeof(charType));

    return 0;
}