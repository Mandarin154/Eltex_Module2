#include <stdio.h>
#include <stdlib.h>

double sum(double args[], int num_args) {
    double sum = 0;
    for (int i = 0; i < num_args; i++) {
        sum += args[i];
    }
    return sum;
}

double minus(double args[], int num_args) {
    double result = args[0];
    for (int i = 1; i < num_args; i++) {
        result -= args[i];
    }
    return result;
}

double multiply(double args[], int num_args) {
    double product = 1;
    for (int i = 0; i < num_args; i++) {
        product *= args[i];
    }
    return product;
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

int main() {
    int num_args, choice, i;
    double args[100]; 

    printf("Введите количество аргументов: ");
    scanf("%d", &num_args);

    printf("Введите %d аргументов:\n", num_args);
    for (i = 0; i < num_args; i++) {
        printf("Аргумент %d: ", i + 1);
        scanf("%lf", &args[i]);
    }

    while (1) {
        printf("\nВыберите операцию:\n");
        printf("1. Сложение\n");
        printf("2. Вычитание\n");
        printf("3. Умножение\n");
        printf("4. Деление\n");
        printf("5. Выход\n");
        printf("Введите ваш выбор: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nРезультат Суммы: %.2lf\n", sum(args, num_args));
                break;
            case 2:
                printf("\nРезультат вычитания: %.2lf\n", minus(args, num_args));
                break;
            case 3:
                printf("\nРезультат произведения: %.2lf\n", multiply(args, num_args));
                break;
            case 4:
                printf("\nРезультат деления: %.2lf\n", divide(args, num_args));
                break;
            case 5:
                printf("\nВыход.\n");
                exit(0);
            default:
                printf("\nНеверный выбор!\n");
        }
    }

    return 0;
}