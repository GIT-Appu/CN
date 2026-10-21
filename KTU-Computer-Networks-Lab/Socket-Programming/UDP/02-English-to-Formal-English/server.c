#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 12356
static const char *formalize(const char *s) { if(!strcasecmp(s,"hi")||!strcasecmp(s,"hello"))return "Good day."; if(!strcasecmp(s,"thanks")||!strcasecmp(s,"thank you"))return "Thank you."; if(!strcasecmp(s,"bye"))return "Goodbye."; if(!strcasecmp(s,"can you help me?"))return "Could you please assist me?"; return "I am unable to translate that expression."; }
int main(void){int sock=socket(AF_INET,SOCK_DGRAM,0);struct sockaddr_in a={.sin_family=AF_INET,.sin_addr.s_addr=htonl(INADDR_ANY),.sin_port=htons(PORT)},c;socklen_t l=sizeof(c);char b[1024];if(sock<0||bind(sock,(struct sockaddr *)&a,sizeof(a))<0){perror("server setup");return EXIT_FAILURE;}printf("Translator server listening on %d...\n",PORT);for(;;){ssize_t n=recvfrom(sock,b,sizeof(b)-1,0,(struct sockaddr *)&c,&l);if(n<0)continue;b[n]='\0';b[strcspn(b,"\r\n")]='\0';const char *r=formalize(b);sendto(sock,r,strlen(r),0,(struct sockaddr *)&c,l);}}
