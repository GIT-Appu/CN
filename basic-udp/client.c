#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12345

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in server_addr;
    socklen_t len;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    char *msg = "Hello from UDP client";

    // Send message
    sendto(sockfd, msg, strlen(msg)+1, 0,
           (struct sockaddr *)&server_addr, sizeof(server_addr));

    len = sizeof(server_addr);

    // Receive response
    recvfrom(sockfd, buffer, sizeof(buffer), 0,
             (struct sockaddr *)&server_addr, &len);

    printf("Server: %s\n", buffer);

    close(sockfd);
    return 0;
}
