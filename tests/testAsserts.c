#include <stdio.h>
#include <assert.h>

int main() {
    unsigned int a = 60;    /* 60 = 0011 1100 */
    unsigned int b = 13;    /* 13 = 0000 1101 */
    int c = 0;

    c = a & b;       /* 12 = 0000 1100 */
    assert(c == 12);
    printf("AND operation passed\n");

    c = a | b;       /* 61 = 0011 1101 */
    assert(c == 61);
    printf("OR operation passed\n");

    c = a ^ b;       /* 49 = 0011 0001 */
    assert(c == 49);
    printf("XOR operation passed\n");

    c = ~a;          /*-61 = 1100 0011 */
    assert(c == -61);
    printf("NOT operation passed\n");

    c = a << 2;     /* 240 = 1111 0000 */
    assert(c == 240);
    printf("LEFT SHIFT operation passed\n");

    c = a >> 2;     /* 15 = 0000 1111 */
    assert(c == 15);
    printf("RIGHT SHIFT operation passed\n");

    printf("All operations passed\n");
    return 0;
}