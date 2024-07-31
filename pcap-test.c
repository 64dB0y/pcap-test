#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define ETHER_ADDR_LEN 6
#define FDDI_ADDR_LEN 6
#define LIBNET_ORG_CODE_SIZE 3
#define TOKEN_RING_ADDR_LEN 6
typedef uint32_t n_time;

#include "libnet-headers.h"

void usage() {
    printf("syntax: pcap-test <interface>\n");
    printf("sample: pcap-test wlan0\n");
}

void print_mac(const uint8_t* mac) {
    printf("%02x:%02x:%02x:%02x:%02x:%02x",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void print_ip(uint32_t ip) {
    struct in_addr addr;
    addr.s_addr = ip;
    printf("%s", inet_ntoa(addr));
}

void print_tcp_info(const u_char* packet, uint32_t length) {
    struct libnet_ethernet_hdr* eth = (struct libnet_ethernet_hdr*)packet;
    struct libnet_ipv4_hdr* iphdr = (struct libnet_ipv4_hdr*)(packet + sizeof(struct libnet_ethernet_hdr));
    uint8_t ip_header_length = iphdr->ip_hl * 4;
    struct libnet_tcp_hdr* tcphdr = (struct libnet_tcp_hdr*)(packet + sizeof(struct libnet_ethernet_hdr) + ip_header_length);

    printf("src mac: ");
    print_mac(eth->ether_shost);
    printf(" -> dst mac: ");
    print_mac(eth->ether_dhost);
    printf("\nsrc ip: ");
    print_ip(iphdr->ip_src.s_addr);
    printf(" -> dst ip: ");
    print_ip(iphdr->ip_dst.s_addr);
    printf("\nsrc port: %d -> dst port: %d\n", ntohs(tcphdr->th_sport), ntohs(tcphdr->th_dport));

    const u_char* payload = (u_char*)(tcphdr + 1);
    int data_len = length - (payload - packet);
    printf("Data: ");
    for (int i = 0; i < data_len && i < 20; i++) {
        printf("%02x ", payload[i]);
    }
    printf("\n\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        usage();
        return -1;
    }

    char* dev = argv[1];
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* pcap = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (!pcap) {
        fprintf(stderr, "pcap_open_live(%s) error: %s\n", dev, errbuf);
        return -1;
    }

    while (1) {
        struct pcap_pkthdr* header;
        const u_char* packet;
        int res = pcap_next_ex(pcap, &header, &packet);
        if (res == 0) continue;
        if (res < 0) {
            fprintf(stderr, "pcap_next_ex error: %s\n", pcap_geterr(pcap));
            break;
        }

        struct libnet_ipv4_hdr* iphdr = (struct libnet_ipv4_hdr*)(packet + sizeof(struct libnet_ethernet_hdr));
        if (iphdr->ip_p == IPPROTO_TCP) {
            printf("%u bytes captured\n", header->caplen);
            print_tcp_info(packet, header->caplen);
        }
    }

    pcap_close(pcap);
    return 0;
}
