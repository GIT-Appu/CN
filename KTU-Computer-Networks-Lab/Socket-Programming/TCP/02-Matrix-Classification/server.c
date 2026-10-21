#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 12346
#define MAX_N 20

static int receive_all(int fd, void *data, size_t length) {
    char *p = data; size_t done = 0;
    while (done < length) { ssize_t n = recv(fd, p + done, length - done, 0); if (n <= 0) return -1; done += (size_t)n; }
    return 0;
}
static int send_all(int fd, const void *data, size_t length) {
    const char *p = data; size_t done = 0;
    while (done < length) { ssize_t n = send(fd, p + done, length - done, 0); if (n <= 0) return -1; done += (size_t)n; }
    return 0;
}
int main(void) {
    int s = socket(AF_INET, SOCK_STREAM, 0), c, opt = 1, net_n;
    struct sockaddr_in a = { .sin_family = AF_INET, .sin_addr.s_addr = htonl(INADDR_ANY), .sin_port = htons(PORT) };
    socklen_t len = sizeof(a);
    if (s < 0 || setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0 || bind(s, (struct sockaddr *)&a, sizeof(a)) < 0 || listen(s, 3) < 0) { perror("server setup"); return EXIT_FAILURE; }
    printf("Matrix server listening on %d...\n", PORT);
    c = accept(s, (struct sockaddr *)&a, &len);
    if (c < 0 || receive_all(c, &net_n, sizeof(net_n)) < 0) { perror("receive"); return EXIT_FAILURE; }
    int n = ntohl(net_n), positive = 0, negative = 0, zero = 0;
    if (n < 1 || n > MAX_N) { fprintf(stderr, "Invalid matrix size\n"); return EXIT_FAILURE; }
    for (int i = 0; i < n * n; i++) { int value; if (receive_all(c, &value, sizeof(value))) return EXIT_FAILURE; value = ntohl(value); if (value > 0) positive++; else if (value < 0) negative++; else zero++; }
    int result[3] = { htonl(positive), htonl(negative), htonl(zero) };
    send_all(c, result, sizeof(result));
    printf("Classified %d x %d matrix: +%d, -%d, 0=%d\n", n, n, positive, negative, zero);
    close(c); close(s); return 0;
}
