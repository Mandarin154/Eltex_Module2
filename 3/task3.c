#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define MAX_PACKETS 1000 

void int_to_ip(unsigned int ip, char *ip_str) {
  sprintf(ip_str, "%u.%u.%u.%u",
          (ip >> 24) & 0xFF,
          (ip >> 16) & 0xFF,
          (ip >> 8) & 0xFF,
          (ip >> 0) & 0xFF);
}

// Функция для проверки принадлежности IP-адреса к подсети
int is_in_subnet(unsigned int ip, unsigned int network_address, unsigned int netmask) {
  return (ip & netmask) == network_address;
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    fprintf(stderr, "Неверное количество аргументов.\n");
    fprintf(stderr, "Использование: %s <шлюз> <маска> <количество_пакетов>\n", argv[0]);
    return 1;
  }

  // Получение аргументов командной строки
  char *gateway_ip = argv[1];
  char *netmask_str = argv[2];
  int num_packets = atoi(argv[3]);

  // Преобразование маски подсети из строки в целое число
  unsigned int netmask;
  inet_pton(AF_INET, netmask_str, &netmask);

  // Вычисление сетевого адреса
  unsigned int gateway_ip_int;
  inet_pton(AF_INET, gateway_ip, &gateway_ip_int);
  unsigned int network_address = gateway_ip_int & netmask;

  int own_subnet_packets = 0;
  int other_networks_packets = 0;

  printf("Обработка %d пакетов:\n", num_packets);

  for (int i = 0; i < num_packets; i++) {
    // Генерация случайного IP-адреса назначения
    unsigned int destination_ip = rand();

    // Преобразование IP-адреса в строку
    char destination_ip_str[INET_ADDRSTRLEN];
    int_to_ip(destination_ip, destination_ip_str);

    // Проверка принадлежности IP-адреса к подсети
    if (is_in_subnet(destination_ip, network_address, netmask)) {
      own_subnet_packets++;
      printf("Пакет %d: %s -> Своя подсеть\n", i + 1, destination_ip_str);
    } else {
      other_networks_packets++;
      printf("Пакет %d: %s -> Другая сеть\n", i + 1, destination_ip_str);
    }
  }

  printf("\nСтатистика:\n");
  printf("Пакетов в своей подсети: %d (%d%%)\n", own_subnet_packets, 
         (own_subnet_packets * 100) / num_packets);
  printf("Пакетов в других сетях: %d (%d%%)\n", other_networks_packets, 
         (other_networks_packets * 100) / num_packets);

  return 0;
}