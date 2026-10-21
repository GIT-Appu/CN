#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 12345

int main(void) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server = {0};
    char buffer[1024] = {0};
    const char *message = "Hello from client";
    if (sock < 0) { perror("socket"); return EXIT_FAILURE; }
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) != 1 ||
        connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) { perror("connect"); close(sock); return EXIT_FAILURE; }
    send(sock, message, strlen(message), 0);
    printf("Message sent to server\n");
    ssize_t received = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (received > 0) { buffer[received] = '\0'; printf("Server: %s\n", buffer); }
    close(sock);
    return 0;
}
