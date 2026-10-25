#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12345

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in server_addr, client_addr;
    socklen_t len;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind
    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("UDP Server is running...\n");

    len = sizeof(client_addr);

    // Receive message
    recvfrom(sockfd, buffer, sizeof(buffer), 0,
             (struct sockaddr *)&client_addr, &len);

    printf("Client: %s\n", buffer);

    // Send response
    char *msg = "Hello from UDP server";
    sendto(sockfd, msg, strlen(msg)+1, 0,
           (struct sockaddr *)&client_addr, len);

    close(sockfd);
    return 0;
}
