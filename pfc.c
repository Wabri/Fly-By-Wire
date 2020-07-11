
/*
 *
 * Hello world!
 *
 */

#include <stdio.h>


int main( void ) {
    printf("char %d\n", (int)sizeof(char));
    printf("short %d\n", (int)sizeof(short));
    printf("int %d\n", (int)sizeof(int));
    printf("long %d\n", (int)sizeof(long));
    printf("float %d\n", (int)sizeof(float));
    printf("double %d\n", (int)sizeof(double));
    printf("long double %d\n", (int)sizeof(long double));

    printf("unsigned char %d\n", (int)sizeof(unsigned char));
    printf("unsigned short %d\n", (int)sizeof(unsigned short));
    printf("unsigned int %d\n", (int)sizeof(unsigned int));
    printf("unsigned long %d\n", (int)sizeof(unsigned long));
    return 0;
}

