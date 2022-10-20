#include <stdio.h>
#include <cstdio>
#include <iostream>

int  main(int argc, char *argv[]) {
    for(int i = 0 ; i < atoi(argv[1]); i++) {
        printf("%i) %s",i+1,argv[2]);
        printf("\n");
    }
    return 0;
}