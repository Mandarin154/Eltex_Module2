#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PACKETS 1000


void get_ip (int ip, char *ip_str){
    sprintf(ip_str, "%u.%u.%u.%u",
            (ip >>24) & 0xFF,
            (ip >>16) & 0xFF,
            (ip >>8) & 0xFF,
            (ip >>0) & 0xFF);

}


int in_subnet(int ip, int address, int netmask){
    return(ip & netmask) == address;
}


int main(int argc, char *argv[]){
    if (argc != 4){
        printf("Невереное кол-во аргументов.\n");
    return 0;
    }

char *ip = argv[1];
char *netmask_str = argv[2];
int num_packets = atoi(argv[3]);

int netmask;


}

