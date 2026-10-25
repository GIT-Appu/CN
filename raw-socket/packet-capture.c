#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#include <linux/if_packet.h>
#include <net/ethernet.h>

#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>

#define BUFFER_SIZE 65536

void print_mac(const unsigned char *mac)
{
    printf("%02X:%02X:%02X:%02X:%02X:%02X",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

int main(void)
{
    int sockfd;
    unsigned char *buffer;
    int data_size;
    struct sockaddr saddr;
    socklen_t saddr_len;

    buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        perror("malloc");
        return 1;
    }

    sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockfd < 0) {
        perror("socket");
        free(buffer);
        return 1;
    }

    printf("\n==============================================\n");
    printf("        RAW SOCKET PACKET CAPTURE\n");
    printf("==============================================\n");
    printf("Press Ctrl+C to stop...\n\n");

    while (1) {
        saddr_len = sizeof(saddr);
        data_size = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, &saddr, &saddr_len);

        if (data_size < 0) {
            perror("recvfrom");
            break;
        }

        if (data_size < (int)sizeof(struct ethhdr))
            continue;

        struct ethhdr *eth = (struct ethhdr *)buffer;

        printf("\n==============================================\n");
        printf("Packet Length : %d Bytes\n", data_size);
        printf("\nEthernet Header\n");
        printf("-----------------------------\n");

        printf("Destination MAC : ");
        print_mac(eth->h_dest);
        printf("\nSource MAC      : ");
        print_mac(eth->h_source);
        printf("\nProtocol        : 0x%04X\n", ntohs(eth->h_proto));

        if (ntohs(eth->h_proto) != ETH_P_IP)
            continue;

        if (data_size < (int)(sizeof(struct ethhdr) + sizeof(struct iphdr)))
            continue;

        struct iphdr *iph = (struct iphdr *)(buffer + sizeof(struct ethhdr));
        int ip_header_length = iph->ihl * 4;
        if (ip_header_length < (int)sizeof(struct iphdr) ||
            data_size < (int)sizeof(struct ethhdr) + ip_header_length)
            continue;

        struct sockaddr_in src;
        struct sockaddr_in dst;
        memset(&src, 0, sizeof(src));
        memset(&dst, 0, sizeof(dst));
        src.sin_addr.s_addr = iph->saddr;
        dst.sin_addr.s_addr = iph->daddr;

        printf("\nIP Header\n");
        printf("-----------------------------\n");
        printf("Source IP      : %s\n", inet_ntoa(src.sin_addr));
        printf("Destination IP : %s\n", inet_ntoa(dst.sin_addr));
        printf("TTL            : %d\n", iph->ttl);
        printf("Protocol       : %d\n", iph->protocol);

        unsigned char *transport = buffer + sizeof(struct ethhdr) + ip_header_length;
        int transport_length = data_size - sizeof(struct ethhdr) - ip_header_length;

        if (iph->protocol == IPPROTO_TCP &&
            transport_length >= (int)sizeof(struct tcphdr)) {
            struct tcphdr *tcp = (struct tcphdr *)transport;
            printf("\nTCP Header\n");
            printf("-----------------------------\n");
            printf("Source Port      : %u\n", ntohs(tcp->source));
            printf("Destination Port : %u\n", ntohs(tcp->dest));
        } else if (iph->protocol == IPPROTO_UDP &&
                   transport_length >= (int)sizeof(struct udphdr)) {
            struct udphdr *udp = (struct udphdr *)transport;
            printf("\nUDP Header\n");
            printf("-----------------------------\n");
            printf("Source Port      : %u\n", ntohs(udp->source));
            printf("Destination Port : %u\n", ntohs(udp->dest));
        } else if (iph->protocol == IPPROTO_ICMP &&
                   transport_length >= (int)sizeof(struct icmphdr)) {
            struct icmphdr *icmp = (struct icmphdr *)transport;
            printf("\nICMP Header\n");
            printf("-----------------------------\n");
            printf("Type : %d\n", icmp->type);
            printf("Code : %d\n", icmp->code);
        } else {
            printf("\nOther Protocol\n");
        }
    }

    close(sockfd);
    free(buffer);
    return 0;
}
