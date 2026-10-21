#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 12347
static int sock;
static void *reader(void *unused) { char b[1024]; (void)unused; ssize_t n; while ((n=recv(sock,b,sizeof(b)-1,0))>0) { b[n]='\0'; fputs(b,stdout); fflush(stdout); } return NULL; }
int main(void) { struct sockaddr_in s={.sin_family=AF_INET,.sin_port=htons(PORT)}; sock=socket(AF_INET,SOCK_STREAM,0); if(sock<0||inet_pton(AF_INET,"127.0.0.1",&s.sin_addr)!=1||connect(sock,(struct sockaddr *)&s,sizeof(s))<0){perror("connect");return EXIT_FAILURE;} pthread_t t;pthread_create(&t,NULL,reader,NULL); char b[1024]; printf("Connected. Type messages; Ctrl+D to exit.\n");while(fgets(b,sizeof(b),stdin))send(sock,b,strlen(b),0);shutdown(sock,SHUT_WR);pthread_join(t,NULL);close(sock);return 0; }
