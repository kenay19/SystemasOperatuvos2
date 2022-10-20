#include <pthread.h>
#include <cstdio>
#include <iostream>

using namespace std;
void * print_xs(void*);
void* print_xs(void* unused) {
    while(1) {
       cout << "x" ;
       return NULL;
    }
}

int main() {
    pthread_t th1;
    pthread_create(&th1, NULL, &print_xs, NULL);
    while(1) {
        cout <<"0";
    }
    return 0;
    pthread_exit(NULL);
}