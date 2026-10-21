#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#define PORT 12358
#define BLOCK 1024
int main(void){char name[256],out[300],b[BLOCK];int s=socket(AF_INET,SOCK_DGRAM,0);struct sockaddr_in a={.sin_family=AF_INET,.sin_port=htons(PORT)};if(s<0||inet_pton(AF_INET,"127.0.0.1",&a.sin_addr)!=1){perror("setup");return EXIT_FAILURE;}printf("File name: ");if(!fgets(name,sizeof(name),stdin))return EXIT_FAILURE;name[strcspn(name,"\r\n")]='\0';snprintf(out,sizeof(out),"received_%s",strrchr(name,'/')?strrchr(name,'/')+1:name);sendto(s,name,strlen(name),0,(struct sockaddr *)&a,sizeof(a));struct timeval tv={5,0};setsockopt(s,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));FILE *f=fopen(out,"wb");if(!f){perror("fopen");return EXIT_FAILURE;}for(;;){ssize_t n=recvfrom(s,b,sizeof(b),0,NULL,NULL);if(n<0){perror("receive");fclose(f);return EXIT_FAILURE;}if(n==7&&!memcmp(b,"__EOF__",7))break;if(n>=7&&!memcmp(b,"ERROR:",6)){printf("%.*s\n",(int)n,b);fclose(f);return EXIT_FAILURE;}fwrite(b,1,(size_t)n,f);}fclose(f);printf("Saved as %s\n",out);close(s);return 0;}
