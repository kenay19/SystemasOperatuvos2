#include <pthread.h>
#include <cstdio>
#include <iostream>

using namespace std;
struct char_print_parms  {
    int count;
    char caracter;

};

void* char_print (void*);

int main(int argc, char *argv[]) {
    pthread_t thread_id[4];
    struct char_print_parms thread_args[4];
    for(int i = 0 ; i < 4 ; i++) {
        if(i == 0){thread_args[i].caracter='a';}
        if(i == 1){thread_args[i].caracter='b';}
        if(i == 2){thread_args[i].caracter='c';}
        if(i == 3){thread_args[i].caracter='d';}
        thread_args[i].count = '10000';
        pthread_create(&thread_id[i],NULL,&char_print,&thread_args[i]);
        
    }
    pthread_join(thread_id[0],NULL);
    pthread_join(thread_id[1],NULL);
    pthread_join(thread_id[2],NULL);
    pthread_join(thread_id[3],NULL);
    return 0;
    pthread_exit(NULL);
}

void* char_print(void* parameters) {
    struct char_print_parms* p = (struct char_print_parms*) parameters;
    for(int i = 0  ; i < p->count;i++) {
        std::cout << p->caracter;

    }
    return NULL;
}

void copiar() {
    
}