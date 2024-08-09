#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

#define MAX_IP 255
#define SUBNET_BITS 32

int is_in_subnet(const char *ip_str, const char *gateway_str, const char *mask_str) {
    struct in_addr ip, gateway, mask;

    inet_pton(AF_INET, ip_str, &ip);
    inet_pton(AF_INET, gateway_str, &gateway);
    inet_pton(AF_INET, mask_str, &mask);

    return (ip.s_addr & mask.s_addr) == (gateway.s_addr & mask.s_addr);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Использование: %s <IP адрес шлюза> <маска подсети> <количество пакетов>\n", argv[0]);
        return 1;
    }

    const char *gateway = argv[1];
    const char *mask = argv[2];
    int num_packets = atoi(argv[3]);
    if (num_packets <= 0) {
        fprintf(stderr, "Количество пакетов должно быть положительным.\n");
        return 1;
    }

    srand(time(NULL));
    int in_subnet_count = 0;

    for (int i = 0; i < num_packets; i++) {
        struct in_addr ip_addr;
        ip_addr.s_addr = htonl((rand() % (MAX_IP + 1)) << 24 |
                              (rand() % (MAX_IP + 1)) << 16 |
                              (rand() % (MAX_IP + 1)) << 8 |
                              (rand() % (MAX_IP + 1)));

        char ip_str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &ip_addr, ip_str, sizeof(ip_str));

        if (is_in_subnet(ip_str, gateway, mask)) {
            in_subnet_count++;
            printf("Пакет %d: %s - внутри своей подсети\n", i + 1, ip_str);
        } else {
            printf("Пакет %d: %s - вне своей подсети\n", i + 1, ip_str);
        }
    }

    printf("\nСтатистика:\n");
    printf("Всего пакетов: %d\n", num_packets);
    printf("Пакетов в своей подсети: %d (%.2f%%)\n", in_subnet_count, (in_subnet_count * 100.0) / num_packets);
    printf("Пакетов вне своей подсети: %d (%.2f%%)\n", num_packets - in_subnet_count, 
           ((num_packets - in_subnet_count) * 100.0) / num_packets);

    return 0;
}