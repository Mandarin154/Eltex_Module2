#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SYM 50  
#define MAX_PHONE_NUM 20  
#define MAX_EMAIL_LEN 50  
#define MAX_SOC 100 

struct Contact {
    char firstname[MAX_SYM];
    char lastname[MAX_SYM];
    char thirdname[MAX_SYM];
    char company[MAX_SYM];
    char post[MAX_SYM];
    char phone_numbers[MAX_PHONE_NUM][MAX_PHONE_NUM];
    char emails[MAX_EMAIL_LEN][MAX_EMAIL_LEN];
    char social_links[MAX_SOC][MAX_SOC];
    char messenger_links[MAX_SOC][MAX_SOC];
    int phone_count;
    int email_count;
    int social_count;
    int messenger_count;

    struct Contact *prev; // Указатель на предыдущий контакт
    struct Contact *next; // Указатель на следующий контакт
};

struct Contact *head = NULL;

void addContact() {
    struct Contact *new_person= (struct Contact *)malloc(sizeof(struct Contact));
    if (new_person == NULL) {
        printf("Ошибка выделения памяти!\n");
        return;
    }

    printf("Введите имя: ");
    scanf("%s", new_person->firstname);

    printf("Введите фамилию: ");
    scanf("%s", new_person->lastname);

    printf("Введите Отчество: ");
    scanf("%s", new_person->thirdname);

    printf("Введите место работы (необязательно): ");
    scanf("%s", new_person->company);

    printf("Введите должность (необязательно): ");
    scanf("%s", new_person->post);

    printf("Введите номера телефонов (разделяйте пробелами, введите 'end' для завершения): ");
    new_person->phone_count = 0;
    while (1) {
        char phone[MAX_PHONE_NUM];
        scanf("%s", phone);
        if (strcmp(phone, "end") == 0) {
            break;
        }
        strcpy(new_person->phone_numbers[new_person->phone_count++], phone);
    }

    printf("Введите адреса электронной почты (разделяйте пробелами, введите 'end' для завершения): ");
    new_person->email_count = 0;
    while (1) {
        char email[MAX_EMAIL_LEN];
        scanf("%s", email);
        if (strcmp(email, "end") == 0) {
            break;
        }
        strcpy(new_person->emails[new_person->email_count++], email);
    }

    printf("Введите ссылки на страницы в соцсетях (разделяйте пробелами, введите 'end' для завершения): ");
    new_person->social_count = 0;
    while (1) {
        char link[MAX_SOC];
        scanf("%s", link);
        if (strcmp(link, "end") == 0) {
            break;
        }
        strcpy(new_person->social_links[new_person->social_count++], link);
    }

    printf("Введите ссылки на профили в мессенджерах (разделяйте пробелами, введите 'end' для завершения): ");
    new_person->messenger_count = 0;
    while (1) {
        char link[MAX_SOC];
        scanf("%s", link);
        if (strcmp(link, "end") == 0) {
            break;
        }
        strcpy(new_person->messenger_links[new_person->messenger_count++], link);
    }

    // Вставка нового контакта в список
    new_person->prev = NULL;
    new_person->next = head;
    if (head != NULL) {
        head->prev = new_person;
    }
    head = new_person;

    printf("Контакт добавлен.\n");
}

void editContact() {
    if (head == NULL) {
        printf("Список контактов пуст.\n");
        return;
    }

    int index = 0;
    struct Contact *current = head;

    printf("Введите номер контакта для редактирования (от 0): ");
    scanf("%d", &index);

    while (current != NULL && index > 0) {
        current = current->next;
        index--;
    }

    if (current == NULL) {
        printf("Неверный номер контакта.\n");
        return;
    }

    printf("Текущие данные контакта:\n");
    printf("Имя: %s\n", current->firstname);
    printf("Фамилия: %s\n", current->lastname);
    printf("Отчество: %s\n", current->thirdname);
    printf("Место работы: %s\n", current->company);
    printf("Должность: %s\n", current->post);
    printf("Номера телефонов: ");
    for (int i = 0; i < current->phone_count; i++) {
        printf("%s ", current->phone_numbers[i]);
    }
    printf("\n");
    printf("Адреса электронной почты: ");
    for (int i = 0; i < current->email_count; i++) {
        printf("%s ", current->emails[i]);
    }
    printf("\n");
    printf("Ссылки на соцсети: ");
    for (int i = 0; i < current->social_count; i++) {
        printf("%s ", current->social_links[i]);
    }
    printf("\n");
    printf("Ссылки на мессенджеры: ");
    for (int i = 0; i < current->messenger_count; i++) {
        printf("%s ", current->messenger_links[i]);
    }
    printf("\n");

}

void printContacts() {
    if (head == NULL) {
        printf("Список контактов пуст.\n");
        return;
    }

    struct Contact *current = head;
    int i = 0;
    while (current != NULL) {
        printf("\nКонтакт %d:\n", i);
        printf("Имя: %s\n", current->firstname);
        printf("Фамилия: %s\n", current->lastname);
        printf("Отчество: %s\n", current->thirdname);
        printf("Место работы: %s\n", current->company);
        printf("Должность: %s\n", current->post);
        printf("Номера телефонов: ");
        for (int j = 0; j < current->phone_count; j++) {
            printf("%s ", current->phone_numbers[j]);
        }
        printf("\n");
        printf("Адреса электронной почты: ");
        for (int j = 0; j < current->email_count; j++) {
            printf("%s ", current->emails[j]);
        }
        printf("\n");
        printf("Ссылки на соцсети: ");
        for (int j = 0; j < current->social_count; j++) {
            printf("%s ", current->social_links[j]);
        }
        printf("\n");
        printf("Ссылки на мессенджеры: ");
        for (int j = 0; j < current->messenger_count; j++) {
            printf("%s ", current->messenger_links[j]);
        }
        printf("\n");

        current = current->next;
        i++;
    }
}

void deleteContact() {
    if (head == NULL) {
        printf("Список контактов пуст.\n");
        return;
    }

    int index = 0;
    struct Contact *current = head;

    printf("Введите номер контакта для удаления (от 0): ");
    scanf("%d", &index);

    while (current != NULL && index > 0) {
        current = current->next;
        index--;
    }

    if (current == NULL) {
        printf("Неверный номер контакта.\n");
        return;
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        head = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    free(current);

    printf("Контакт удален.\n");
}

int main() {
    int choice;

    while (1) {
        printf("\nМеню:\n");
        printf("1. Добавить контакт\n");
        printf("2. Редактировать контакт\n");
        printf("3. Вывести список контактов\n");
        printf("4. Удалить контакт\n");
        printf("5. Выход\n");
        printf("Введите ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                editContact();
                break;
            case 3:
                printContacts();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                printf("Выход...\n");
                return 0;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    }

    return 0;
}