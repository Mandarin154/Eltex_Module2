#include <stdio.h>
#include <stdlib.h>

typedef struct Command {
    char *name; 
    double (*func)(double[], int); 
} Command;


double sum(double args[], int num_args) {
    double result= 0;
    for (int i = 0; i < num_args; i++) {
        result+= args[i];
    }
    return result;
}

double minus(double args[], int num_args) {
    double result = args[0];
    for (int i = 1; i < num_args; i++) {
        result -= args[i];
    }
    return result;
}

double multiply(double args[], int num_args) {
    double result = 1;
    for (int i = 0; i < num_args; i++) {
        result*= args[i];
    }
    return result;
}

double divide(double args[], int num_args) {
    double result = args[0];
    for (int i = 1; i < num_args; i++) {
        if (args[i] == 0) {
            printf("Деление на ноль невозможно!\n");
            return 0;
        }
        result /= args[i];
    }
    return result;
}

void exit_program() {
    printf("Выход...\n");
    exit(0);
}

int main() {
    int num_args, choice, i;
    double args[100]; 

    Command commands[] = {
        {"Сложение", sum},
        {"Вычитание", minus},
        {"Умножение", multiply},
        {"Деление", divide},
        {"Выход", exit_program} 
    };

    int num_commands = sizeof(commands) / sizeof(Command);

    printf("Введите количество аргументов: ");
    scanf("%d", &num_args);

    printf("Введите эти аргументы:\n", num_args);
    for (i = 0; i < num_args; i++) {
        printf("Аргумент %d: ", i + 1);
        scanf("%lf", &args[i]);
    }

    while (1) {
        printf("\nВыберите операцию:\n");

        for (i = 0; i < num_commands; i++) {
            printf("%d. %s\n", i + 1, commands[i].name);
        }

        printf("\nВведите ваш выбор: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > num_commands) {
            printf("Ошибка выбора.\n");
            continue;
        }

        double result = commands[choice - 1].func(args, num_args);

        if (choice != num_commands) {
            printf("Результат: %.2lf\n", result);
        }
    }

    return 0;
}