// test.c
#include <stdio.h>
#include "mymath.h"// 自定义头文件
int main(){
    int a = 2;
    int b = 3;
    int sum = add(a, b); 
    printf("a=%d, b=%d, a+b=%d\n", a, b, sum);
}
// [preprocessing]
// gcc -E -I ./inc test.c -o test.i

// [compilation]
// gcc -S -I ./inc test.c -o test.s

// [assemble]
// gcc -c test.s -o test.o

// [linking] 
// ld -o test.out test.o inc/mymath.o ... libraries ...
