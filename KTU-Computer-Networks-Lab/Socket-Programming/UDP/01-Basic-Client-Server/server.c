#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 12355
int main(void) { int s=socket(AF_INET,SOCK_DGRAM,0); struct sockaddr_in a={.sin_family=AF_INET,.sin_addr.s_addr=htonl(INADDR_ANY),.sin_port=htons(PORT)}, client; socklen_t len=sizeof(client); char b[1024]; if(s<0||bind(s,(struct sockaddr *)&a,sizeof(a))<0){perror("server setup");return EXIT_FAILURE;} printf("UDP server listening on %d...\n",PORT); ssize_t n=recvfrom(s,b,sizeof(b)-1,0,(struct sockaddr *)&client,&len);if(n>0){b[n]='\0';printf("Client: %s\n",b);const char *r="Hello from UDP server";sendto(s,r,strlen(r),0,(struct sockaddr *)&client,len);}close(s);return 0; }
