#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 12347
#define MAX_CLIENTS 20
#define BUFFER_SIZE 1024
static int clients[MAX_CLIENTS];
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static void broadcast(const char *message, int sender) {
    pthread_mutex_lock(&lock);
    for (int i = 0; i < MAX_CLIENTS; i++) if (clients[i] > 0 && clients[i] != sender) send(clients[i], message, strlen(message), 0);
    pthread_mutex_unlock(&lock);
}
static void *serve_client(void *arg) {
    int fd = *(int *)arg; free(arg); char buffer[BUFFER_SIZE];
    broadcast("[A user joined the chat]\n", fd);
    for (;;) { ssize_t n = recv(fd, buffer, sizeof(buffer) - 1, 0); if (n <= 0) break; buffer[n] = '\0'; broadcast(buffer, fd); }
    pthread_mutex_lock(&lock); for (int i = 0; i < MAX_CLIENTS; i++) if (clients[i] == fd) clients[i] = 0; pthread_mutex_unlock(&lock);
    close(fd); broadcast("[A user left the chat]\n", -1); return NULL;
}
int main(void) {
    int server = socket(AF_INET, SOCK_STREAM, 0), opt = 1; struct sockaddr_in a = { .sin_family=AF_INET, .sin_addr.s_addr=htonl(INADDR_ANY), .sin_port=htons(PORT) };
    if (server < 0 || setsockopt(server,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt)) < 0 || bind(server,(struct sockaddr *)&a,sizeof(a)) < 0 || listen(server,MAX_CLIENTS) < 0) { perror("server setup"); return EXIT_FAILURE; }
    printf("Chat server listening on %d...\n", PORT);
    for (;;) { int fd=accept(server,NULL,NULL), placed=0; if(fd<0) continue; pthread_mutex_lock(&lock); for(int i=0;i<MAX_CLIENTS;i++) if(!clients[i]) {clients[i]=fd;placed=1;break;} pthread_mutex_unlock(&lock); if(!placed){send(fd,"Server full\n",12,0);close(fd);continue;} int *p=malloc(sizeof(*p));*p=fd;pthread_t thread;pthread_create(&thread,NULL,serve_client,p);pthread_detach(thread); }
}
