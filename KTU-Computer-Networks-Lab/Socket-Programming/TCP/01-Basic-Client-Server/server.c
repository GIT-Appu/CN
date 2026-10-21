#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 12345

int main(void) {
    int server_fd, client_fd, opt = 1;
    struct sockaddr_in address = {0};
    socklen_t address_len = sizeof(address);
    char buffer[1024] = {0};
    const char *reply = "Hello from server";

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) { perror("socket"); return EXIT_FAILURE; }
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0 ||
        listen(server_fd, 3) < 0) { perror("bind/listen"); close(server_fd); return EXIT_FAILURE; }

    printf("Server is listening on port %d...\n", PORT);
    client_fd = accept(server_fd, (struct sockaddr *)&address, &address_len);
    if (client_fd < 0) { perror("accept"); close(server_fd); return EXIT_FAILURE; }
    ssize_t received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (received > 0) {
        buffer[received] = '\0';
        printf("Client: %s\n", buffer);
        send(client_fd, reply, strlen(reply), 0);
        printf("Message sent to client\n");
    }
    close(client_fd); close(server_fd);
    return 0;
}
