#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define PORT 12358
#define BLOCK 1024
int main(void){int s=socket(AF_INET,SOCK_DGRAM,0);struct sockaddr_in a={.sin_family=AF_INET,.sin_addr.s_addr=htonl(INADDR_ANY),.sin_port=htons(PORT)};if(s<0||bind(s,(struct sockaddr *)&a,sizeof(a))<0){perror("server setup");return EXIT_FAILURE;}printf("UDP file server listening on %d...\n",PORT);for(;;){struct sockaddr_in c;socklen_t l=sizeof(c);char name[256];ssize_t n=recvfrom(s,name,sizeof(name)-1,0,(struct sockaddr *)&c,&l);if(n<0)continue;name[n]='\0';pid_t p=fork();if(p==0){FILE *f=fopen(name,"rb");char block[BLOCK];if(!f){sendto(s,"ERROR: file not found",21,0,(struct sockaddr *)&c,l);_exit(0);}size_t got;while((got=fread(block,1,sizeof(block),f))>0)sendto(s,block,got,0,(struct sockaddr *)&c,l);fclose(f);sendto(s,"__EOF__",7,0,(struct sockaddr *)&c,l);_exit(0);}}}
