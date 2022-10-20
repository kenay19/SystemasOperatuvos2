#include <pthread.h>
#include <cstdio>
#include <iostream>

void* char_print (void*);

struct char_print_parms  {
    int count;
    char caracter;

};

void* char_print(void* parameters) {
    struct char_print_parms* p = (struct char_print_parms*) parameters;
    for(int i = 0  ; i < p->count;i++) {
        std::cout << p->caracter;

    }
    return NULL;
}

int main() {
    pthread_t thread1_id;
    pthread_t thread2_id;
    pthread_t thread3_id;

    struct char_print_parms thread1_args;
    struct char_print_parms thread2_args;
    struct char_print_parms thread3_args;
    thread1_args.caracter = 'x';
    thread1_args.count = '10000';
    pthread_create(&thread1_id,NULL,&char_print,&thread1_args);
    thread2_args.caracter = 'y';
    thread2_args.count = '10000';
    pthread_create(&thread2_id,NULL,&char_print,&thread2_args);
    thread3_args.caracter = 'z';
    thread3_args.count = '10000';
    pthread_create(&thread3_id,NULL,&char_print,&thread3_args);
    pthread_join(thread1_id,NULL);
    pthread_join(thread2_id,NULL);
    pthread_join(thread3_id,NULL);
    return 0;
    pthread_exit(NULL);
}