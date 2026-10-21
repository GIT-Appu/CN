#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 12346
#define MAX_N 20
static int send_all(int fd, const void *data, size_t length) { const char *p=data; size_t d=0; while(d<length){ssize_t n=send(fd,p+d,length-d,0);if(n<=0)return -1;d+=(size_t)n;}return 0; }
static int receive_all(int fd, void *data, size_t length) { char *p=data; size_t d=0; while(d<length){ssize_t n=recv(fd,p+d,length-d,0);if(n<=0)return -1;d+=(size_t)n;}return 0; }
int main(void) {
    int n, sock = socket(AF_INET, SOCK_STREAM, 0); struct sockaddr_in server = { .sin_family=AF_INET, .sin_port=htons(PORT) };
    if (sock < 0 || inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) != 1 || connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) { perror("connect"); return EXIT_FAILURE; }
    printf("Order of square matrix (1-%d): ", MAX_N); if (scanf("%d", &n) != 1 || n < 1 || n > MAX_N) return EXIT_FAILURE;
    int net_n=htonl(n); send_all(sock,&net_n,sizeof(net_n));
    printf("Enter %d elements:\n",n*n); for(int i=0;i<n*n;i++){int v;if(scanf("%d",&v)!=1)return EXIT_FAILURE;v=htonl(v);if(send_all(sock,&v,sizeof(v)))return EXIT_FAILURE;}
    int r[3]; if(receive_all(sock,r,sizeof(r))) return EXIT_FAILURE;
    printf("Positive: %d\nNegative: %d\nZero: %d\n",ntohl(r[0]),ntohl(r[1]),ntohl(r[2])); close(sock); return 0;
}
