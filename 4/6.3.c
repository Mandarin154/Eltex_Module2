#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <dirent.h>

typedef struct Command {
    char *name; 
    double (*func)(double[], int); 
} Command;

#define MAX_LIB_PATH 1024
#define MAX_COMMANDS 100

int load_commands(const char *directory, Command *commands, int *num_commands) {
    DIR *dir = opendir(directory);
    if (dir == NULL) {
        perror("Не удалось открыть директорию");
        return -1;
    }

    struct dirent *entry;
    *num_commands = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;

        char lib_path[MAX_LIB_PATH];
        snprintf(lib_path, sizeof(lib_path), "%s/%s", directory, entry->d_name);

        void *handle = dlopen(lib_path, RTLD_LAZY);
        if (!handle) {
            fprintf(stderr, "Не удалось загрузить библиотеку: %s\n", dlerror());
            continue;
        }

        double (*func)(double[], int) = dlsym(handle, "execute");
        if (!func) {
            fprintf(stderr, "Не удалось найти функцию 'execute' в библиотеке %s: %s\n", entry->d_name, dlerror());
            dlclose(handle);
            continue;
        }

        commands[*num_commands].name = entry->d_name; 
        commands[*num_commands].func = func;
        (*num_commands)++;
    }

    closedir(dir);
    return 0;
}

int main() {
    int num_args, choice, i;
    double args[100]; 

    Command commands[MAX_COMMANDS];
    int num_commands;

    if (load_commands("./libs", commands, &num_commands) != 0) {
        return 1; 
    }

    printf("Введите количество аргументов: ");
    scanf("%d", &num_args);

    printf("Введите эти аргументы:\n");
    for (i = 0; i < num_args; i++) {
        printf("Аргумент %d: ", i + 1);
        scanf("%lf", &args[i]);
    }

    while (1) {
        printf("\nВыберите операцию:\n0. Выход\n");

        for (i = 0; i < num_commands; i++) {
            printf("%d. %s\n", i + 1, commands[i].name);
        }

        printf("\nВведите ваш выбор: ");
        scanf("%d", &choice);

        if (choice == 0) {
            printf("Выход.\n");
            break;
        }
        if (choice < 1 || choice > num_commands) {
            printf("Ошибка выбора.\n");
            continue;
        }

        double result = commands[choice - 1].func(args, num_args);
        printf("Результат: %.2lf\n", result);
    }

    return 0;
}