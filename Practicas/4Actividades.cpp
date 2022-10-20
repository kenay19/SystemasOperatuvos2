#include <pthread.h>
#include <cstdio>
#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;
struct char_print_parms  {
    int count;
    char caracter;
    int a;
    int b;
    char* sentencia;
};

void* char_print (void*);
void* suma(void*);
void* listar(void*);
void* impresion(void*);

int main(int argc, char *argv[]) {
    pthread_t thread_id[3];
    struct char_print_parms thread_args[3];
    for(int i = 0 ; i < 4 ; i++) {
        if(i == 0){
            thread_args[i].caracter='a';
            thread_args[i].count = 20;
            pthread_create(&thread_id[i],NULL,&char_print,&thread_args[i]);
        }
        if(i == 1) {
            thread_args[i].a=1;
            thread_args[i].b = 100;
            pthread_create(&thread_id[i],NULL,&suma,&thread_args[i]);
        }
        if(i==2) {
            thread_args[i].sentencia = argv[1];
            pthread_create(&thread_id[i],NULL,&listar,&thread_args[i]);
        }if(i == 3) {
            thread_args[i].sentencia = argv[2];
            thread_args[i].count = 10;
            pthread_create(&thread_id[i],NULL,&impresion,&thread_args[i]);
        }
        
        
        
    }
    pthread_join(thread_id[0],NULL);
    pthread_join(thread_id[1],NULL);
    pthread_join(thread_id[2],NULL);
    pthread_join(thread_id[3],NULL);
    return 0;
    pthread_exit(NULL);
}

void* suma(void* parameters) {
    int suma = 0 ;
    struct char_print_parms* p = (struct char_print_parms*) parameters;
    for(int i = p->a; i <= p->b ; i++) {
        suma = suma + i;
    }
    printf("El resultado: %i",suma);
    return NULL;
}
void* char_print(void* parameters) {
    struct char_print_parms* p = (struct char_print_parms*) parameters;
    for(int i = 0  ; i < p->count;i++) {
        std::cout << p->caracter;
    }
    return NULL;
}
void* listar(void* parameters) {
    struct char_print_parms* p = (struct char_print_parms*) parameters;
    int result = system(p-> sentencia);;
    return NULL;
}

void* impresion(void* parameters) {
    struct char_print_parms* p = (struct char_print_parms*) parameters;
    for(int i = 0 ; i < p->count;i++) {
        cout << i <<") " << p->sentencia<<endl;
    }
    return NULL;
}


