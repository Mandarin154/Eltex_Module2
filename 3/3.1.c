#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void convert_to_binary(const char *permissions, char *binary) {
    int i;
    binary[0] = '0'; 
    for (i = 0; i < 3; i++) {
        if (permissions[i * 3] == 'r') binary[1 + i * 3] = '1'; else binary[1 + i * 3] = '0';
        if (permissions[i * 3 + 1] == 'w') binary[2 + i * 3] = '1'; else binary[2 + i * 3] = '0';
        if (permissions[i * 3 + 2] == 'x') binary[3 + i * 3] = '1'; else binary[3 + i * 3] = '0';
    }
    binary[10] = '\0'; 
}

void display_file_permissions(const char *filename) {
    struct stat file_stat;
    
    if (stat(filename, &file_stat) == -1) {
        perror("Ошибка получения информации о файле");
        return;
    }
    
    char permissions[10];
    snprintf(permissions, sizeof(permissions), "%c%c%c%c%c%c%c%c%c",
              (file_stat.st_mode & S_IRUSR) ? 'r' : '-',
              (file_stat.st_mode & S_IWUSR) ? 'w' : '-',
              (file_stat.st_mode & S_IXUSR) ? 'x' : '-',
              (file_stat.st_mode & S_IRGRP) ? 'r' : '-',
              (file_stat.st_mode & S_IWGRP) ? 'w' : '-',
              (file_stat.st_mode & S_IXGRP) ? 'x' : '-',
              (file_stat.st_mode & S_IROTH) ? 'r' : '-',
              (file_stat.st_mode & S_IWOTH) ? 'w' : '-',
              (file_stat.st_mode & S_IXOTH) ? 'x' : '-'
    );

    char binary[11];
    convert_to_binary(permissions, binary);

    printf("Для файла '%s':\n", filename);
    printf("Буквенное представление прав доступа: %s\n", permissions);
    printf("Цифровое обозначение прав доступа: %o\n", file_stat.st_mode & (S_IRUSR | S_IWUSR | S_IXUSR |
                                                                       S_IRGRP | S_IWGRP | S_IXGRP |
                                                                       S_IROTH | S_IWOTH | S_IXOTH));
    printf("Битовое представление прав доступа: %s\n", binary);
}

void convert_from_numeric(int num, char *permissions) {
    permissions[0] = (num & 0400) ? 'r' : '-';
    permissions[1] = (num & 0200) ? 'w' : '-';
    permissions[2] = (num & 0100) ? 'x' : '-';
    permissions[3] = (num & 0040) ? 'r' : '-';
    permissions[4] = (num & 0020) ? 'w' : '-';
    permissions[5] = (num & 0010) ? 'x' : '-';
    permissions[6] = (num & 0004) ? 'r' : '-';
    permissions[7] = (num & 0002) ? 'w' : '-';
    permissions[8] = (num & 0001) ? 'x' : '-';
    permissions[9] = '\0'; 
}

void modify_permissions(char *permissions, const char *modification) {
    for (int i = 0; i < strlen(modification); i++) {
        switch (modification[i]) {
            case 'u':
                if (i + 1 < strlen(modification)) {
                    if (modification[i + 1] == '+') {
                        if (modification[i + 2] == 'r') permissions[0] = 'r';
                        else if (modification[i + 2] == 'w') permissions[1] = 'w';
                        else if (modification[i + 2] == 'x') permissions[2] = 'x';
                    } else if (modification[i + 1] == '-') {
                        if (modification[i + 2] == 'r') permissions[0] = '-';
                        else if (modification[i + 2] == 'w') permissions[1] = '-';
                        else if (modification[i + 2] == 'x') permissions[2] = '-';
                    }
                    i += 2; 
                }
                break;
            case 'g':
                if (i + 1 < strlen(modification)) {
                    if (modification[i + 1] == '+') {
                        if (modification[i + 2] == 'r') permissions[3] = 'r';
                        else if (modification[i + 2] == 'w') permissions[4] = 'w';
                        else if (modification[i + 2] == 'x') permissions[5] = 'x';
                    } else if (modification[i + 1] == '-') {
                        if (modification[i + 2] == 'r') permissions[3] = '-';
                        else if (modification[i + 2] == 'w') permissions[4] = '-';
                        else if (modification[i + 2] == 'x') permissions[5] = '-';
                    }
                    i += 2; 
                }
                break;
            case 'o':
                if (i + 1 < strlen(modification)) {
                    if (modification[i + 1] == '+') {
                        if (modification[i + 2] == 'r') permissions[6] = 'r';
                        else if (modification[i + 2] == 'w') permissions[7] = 'w';
                        else if (modification[i + 2] == 'x') permissions[8] = 'x';
                    } else if (modification[i + 1] == '-') {
                        if (modification[i + 2] == 'r') permissions[6] = '-';
                        else if (modification[i + 2] == 'w') permissions[7] = '-';
                        else if (modification[i + 2] == 'x') permissions[8] = '-';
                    }
                    i += 2; 
                }
                break;
            default:
                break;
        }
    }
}

int main() {
    while (1) {
        printf("\nМеню:\n");
        printf("1. Ввести права доступа в буквеном или цифром формате.\n");
        printf("2. Ввести имя файла.\n");
        printf("3. Изменить права доступа по команде (chmod).\n");
        printf("4. Выход.\n");
        printf("Выберите действие: ");

        int choice;
        scanf("%d", &choice);
        if (choice == 4) break;

        char permissions[10] = "---------"; // Начальные права доступа
        char modification[10] = "";
        char filename[100];
        int num_permissions = 0; 

        switch (choice) {
            case 1: {
                printf("Введите права доступа в буквеном формате (например, rwxrwxrwx): ");
                scanf("%s", permissions);
                char binary[11];
                convert_to_binary(permissions, binary);
                printf("Битовое представление прав доступа: %s\n", binary);
                break;
            }
            case 2: {
                printf("Введите имя файла: ");
                scanf("%s", filename);
                display_file_permissions(filename);
                break;
            }
            case 3: {
                printf("Введите права доступа в буквеном формате (например, rwxrwxrwx) или в цифром формате (например, 755): ");
                scanf("%s", permissions);
                
                if (strlen(permissions) == 3 && isdigit(permissions[0])) { 
                    num_permissions = atoi(permissions);
                    convert_from_numeric(num_permissions, permissions);
                }
                
                printf("Введите модификацию прав доступа (например, u+x, g-w, o=r): ");
                scanf("%s", modification);
                modify_permissions(permissions, modification);

                char binary[11];
                convert_to_binary(permissions, binary);

                printf("После модификации:\n");
                printf("Буквенное представление прав доступа: %s\n", permissions);
                printf("Битовое представление прав доступа: %s\n", binary);
                printf("Цифровое обозначение прав доступа: %o\n", num_permissions);
                break;
            }
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    }

    return 0;
}