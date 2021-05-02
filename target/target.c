#include <stdbool.h>
#include <stdio.h>

void foo() {
    printf("foo\n");
}

int main() {
    do {
        printf("loop\n");
        foo();
    } while (getchar() != 'q');
}
