#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#define PORT 12357
int main(void){int s=socket(AF_INET,SOCK_DGRAM,0);struct sockaddr_in a={.sin_family=AF_INET,.sin_addr.s_addr=htonl(INADDR_ANY),.sin_port=htons(PORT)};if(s<0||bind(s,(struct sockaddr *)&a,sizeof(a))<0){perror("server setup");return EXIT_FAILURE;}printf("Concurrent UDP time server listening on %d...\n",PORT);for(;;){struct sockaddr_in c;socklen_t l=sizeof(c);char request[64];ssize_t n=recvfrom(s,request,sizeof(request),0,(struct sockaddr *)&c,&l);if(n<0)continue;pid_t pid=fork();if(pid==0){time_t now=time(NULL);char reply[128];snprintf(reply,sizeof(reply),"%s",ctime(&now));sendto(s,reply,strlen(reply),0,(struct sockaddr *)&c,l);_exit(0);}}}
