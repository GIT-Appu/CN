#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 12357
int main(void){int s=socket(AF_INET,SOCK_DGRAM,0);struct sockaddr_in a={.sin_family=AF_INET,.sin_port=htons(PORT)};char b[128];if(s<0||inet_pton(AF_INET,"127.0.0.1",&a.sin_addr)!=1){perror("setup");return EXIT_FAILURE;}sendto(s,"TIME",4,0,(struct sockaddr *)&a,sizeof(a));ssize_t n=recvfrom(s,b,sizeof(b)-1,0,NULL,NULL);if(n>0){b[n]='\0';printf("Server time: %s",b);}close(s);return 0;}
