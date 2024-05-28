#include <stdio.h>
#include <stdlib.h>


long factorial(int n) {
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

int main() {
    int number = rand() % 20;
    printf("The positive integer is: %d\n", number);
    printf("Factorial of %d = %ld\n", number, factorial(number));
    return 0;
}