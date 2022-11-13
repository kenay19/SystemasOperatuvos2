#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include "sock.h"

int leng(const char * []);
const char *books[] = {
"1) War and Peace\n", 
"2)Pride and Prejudice\n",
"3) The Sound and the Fury\n ",
"4) Vaquero viejo\n",
"5) the pepe\n",
"\0"};

void report(const char *msg, int terminate){
  perror(msg);
  if (terminate)
    exit(-1); /* failure */
}

int main(){
  
  int fd = socket(AF_INET,     /* network versus AF_LOCAL */
                  SOCK_STREAM, /* reliable, bidirectional: TCP */
                  0);          /* system picks underlying protocol */
  if (fd < 0)
    report("socket", 1); /* terminate */

  /* bind the server's local address in memory */
  struct sockaddr_in saddr;
  memset(&saddr, 0, sizeof(saddr));          /* clear the bytes */
  saddr.sin_family = AF_INET;                /* versus AF_LOCAL */
  saddr.sin_addr.s_addr = htonl(INADDR_ANY); /* host-to-network endian */
  saddr.sin_port = htons(PortNumber);        /* for listening */

  if (bind(fd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    report("bind", 1); /* terminate */

  /* listen to the socket */
  if (listen(fd, MaxConnects) < 0) /* listen for clients, up to MaxConnects */
    report("listen", 1);           /* terminate */

  fprintf(stderr, "Listening on port %i for clients...\n", PortNumber);
  /* a server traditionally listens indefinitely */

  
  while (1){
    struct sockaddr_in caddr; /* client address */
    int len = sizeof(caddr);  /* address length could change */

    int client_fd = accept(fd, (struct sockaddr *)&caddr, &len); /* accept blocks */
    if (client_fd < 0){
      report("accept", 0); /* don't terminated, though there's a problem */
      continue;
    }
    for(int i = 0 ; i < leng(books); i++) {
      write(client_fd,books[i],strlen(books[i]));
    }
    while(1){
      char buffer[BuffSize +1];
    memset(buffer,'\0',sizeof(buffer));
    if(read(client_fd, buffer, sizeof(buffer))>0){
      for(int i = 0; i < strlen(buffer);i++) {
        write(client_fd,books[(buffer[i] - '0')-1],strlen(books[(buffer[i] - '0')-1]));
      }
    }
    }
    
    

    close(client_fd); /* break connection */
  }                   /* while(1) */
  return 0;
}

int leng(const char* msg[]) {
  int i = 0;
  int j = 0 ;
  while(msg[i][j] != '\0') {
    if(msg[i][j] == '\n'){
      i = i+1;
      j = 0;
    }
    j++;
  }
  return i;
}