#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100
#define MAX_SYM 100
#define MAX_PHONE_NUM 15
#define MAX_EMAIL_LEN 50
#define MAX_SOC 50

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
};

struct Contact contacts[MAX_CONTACTS];
int contact_count = 0;

void addContact() {
    struct Contact new_person;

    printf("Введите имя: ");
    scanf("%s", new_person.firstname);

    printf("Введите фамилию: ");
    scanf("%s", new_person.lastname);

    printf("Введите отчество: ");
    scanf("%s", new_person.thirdname);

    printf("Введите место работы (необязательно): ");
    scanf("%s", new_person.company);

    printf("Введите должность (необязательно): ");
    scanf("%s", new_person.post);

    new_person.phone_count = 0;
    printf("Введите номера телефонов (разделяйте пробелами, введите 'end' для завершения): ");
    while (1) {
        char phone[MAX_PHONE_NUM];
        scanf("%s", phone);
        if (strcmp(phone, "end") == 0) {
            break;
        }
        strcpy(new_person.phone_numbers[new_person.phone_count++], phone);
    }

    new_person.email_count = 0;
    printf("Введите адреса электронной почты (разделяйте пробелами, введите 'end' для завершения): ");
    while (1) {
        char email[MAX_EMAIL_LEN];
        scanf("%s", email);
        if (strcmp(email, "end") == 0) {
            break;
        }
        strcpy(new_person.emails[new_person.email_count++], email);
    }

    new_person.social_count = 0;
    printf("Введите ссылки на соцсети (разделяйте пробелами, введите 'end' для завершения): ");
    while (1) {
        char link[MAX_SOC];
        scanf("%s", link);
        if (strcmp(link, "end") == 0) {
            break;
        }
        strcpy(new_person.social_links[new_person.social_count++], link);
    }

    new_person.messenger_count = 0;
    printf("Введите ссылки на мессенджеры (разделяйте пробелами, введите 'end' для завершения): ");
    while (1) {
        char link[MAX_SOC];
        scanf("%s", link);
        if (strcmp(link, "end") == 0) {
            break;
        }
        strcpy(new_person.messenger_links[new_person.messenger_count++], link);
    }

    contacts[contact_count++] = new_person;
    printf("Контакт добавлен. Номер: %d\n", contact_count - 1);
}

void editContact() {
    if (contact_count == 0) {
        printf("Список контактов пуст.\n");
        return;
    }

    int index;
    printf("Введите номер контакта для редактирования (от 0 до %d): ", contact_count - 1);
    scanf("%d", &index);

    if (index < 0 || index >= contact_count) {
        printf("Неверный номер контакта.\n");
        return;
    }

    struct Contact *contact = &contacts[index];

    printf("Текущие данные контакта:\n");
    printf("Имя: %s\n", contact->firstname);
    printf("Фамилия: %s\n", contact->lastname);
    printf("Отчество: %s\n", contact->thirdname);
    printf("Место работы: %s\n", contact->company);
    printf("Должность: %s\n", contact->post);
    printf("Номера телефонов: ");
    for (int i = 0; i < contact->phone_count; i++) {
        printf("%s ", contact->phone_numbers[i]);
    }
    printf("\nАдреса электронной почты: ");
    for (int i = 0; i < contact->email_count; i++) {
        printf("%s ", contact->emails[i]);
    }
    printf("\nСсылки на соцсети: ");
    for (int i = 0; i < contact->social_count; i++) {
        printf("%s ", contact->social_links[i]);
    }
    printf("\nСсылки на мессенджеры: ");
    for (int i = 0; i < contact->messenger_count; i++) {
        printf("%s ", contact->messenger_links[i]);
    }
    printf("\n");

    printf("Что вы хотите отредактировать?\n");
    printf("1. Имя\n");
    printf("2. Фамилию\n");
    printf("3. Отчество\n");
    printf("4. Место работы\n");
    printf("5. Должность\n");
    printf("6. Номера телефонов\n");
    printf("7. Адреса электронной почты\n");
    printf("8. Ссылки на соцсети\n");
    printf("9. Ссылки на мессенджеры\n");
    printf("0. Вернуться в главное меню\n");

    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Введите новое имя: ");
            scanf("%s", contact->firstname);
            break;
        case 2:
            printf("Введите новую фамилию: ");
            scanf("%s", contact->lastname);
            break;
        case 3:
            printf("Введите новое отчество: ");
            scanf("%s", contact->thirdname);
            break;
        case 4:
            printf("Введите новое место работы: ");
            scanf("%s", contact->company);
            break;
        case 5:
            printf("Введите новую должность: ");
            scanf("%s", contact->post);
            break;
        case 6:
            contact->phone_count = 0;
            printf("Введите номера телефонов (разделяйте пробелами, введите 'end' для завершения): ");
            while (1) {
                char phone[MAX_PHONE_NUM];
                scanf("%s", phone);
                if (strcmp(phone, "end") == 0) {
                    break;
                }
                strcpy(contact->phone_numbers[contact->phone_count++], phone);
            }
            break;
        case 7:
            contact->email_count = 0;
            printf("Введите адреса электронной почты (разделяйте пробелами, введите 'end' для завершения): ");
            while (1) {
                char email[MAX_EMAIL_LEN];
                scanf("%s", email);
                if (strcmp(email, "end") == 0) {
                    break;
                }
                strcpy(contact->emails[contact->email_count++], email);
            }
            break;
        case 8:
            contact->social_count = 0;
            printf("Введите ссылки на соцсети (разделяйте пробелами, введите 'end' для завершения): ");
            while (1) {
                char link[MAX_SOC];
                scanf("%s", link);
                if (strcmp(link, "end") == 0) {
                    break;
                }
                strcpy(contact->social_links[contact->social_count++], link);
            }
            break;
        case 9:
            contact->messenger_count = 0;
            printf("Введите ссылки на мессенджеры (разделяйте пробелами, введите 'end' для завершения): ");
            while (1) {
                char link[MAX_SOC];
                scanf("%s", link);
                if (strcmp(link, "end") == 0) {
                    break;
                }
                strcpy(contact->messenger_links[contact->messenger_count++], link);
            }
            break;
        case 0: 
            return;
        default:
            printf("Неверный выбор\n");
    }
}

void deleteContact() {
    if (contact_count == 0) {
        printf("Список контактов пуст.\n");
        return;
    }

    int index;
    printf("Введите номер контакта для удаления (от 0 до %d): ", contact_count - 1);
    scanf("%d", &index);

    if (index < 0 || index >= contact_count) {
        printf("Неверный номер контакта.\n");
        return;
    }

    // Сдвигаем все контакты после удаляемого на одно место влево
    for (int i = index; i < contact_count - 1; i++) {
        contacts[i] = contacts[i + 1];
    }
    contact_count--;
    printf("Контакт удален.\n");
}

void displayContacts() {
    if (contact_count == 0) {
        printf("Список контактов пуст.\n");
        return;
    }

    printf("Список контактов:\n");
    for (int i = 0; i < contact_count; i++) {
        printf("Контакт %d:\n", i);
        printf("Имя: %s\n", contacts[i].firstname);
        printf("Фамилия: %s\n", contacts[i].lastname);
        printf("Отчество: %s\n", contacts[i].thirdname);
        printf("Место работы: %s\n", contacts[i].company);
        printf("Должность: %s\n", contacts[i].post);
        printf("Телефоны: ");
        for (int j = 0; j < contacts[i].phone_count; j++) {
            printf("%s ", contacts[i].phone_numbers[j]);
        }
        printf("\nEmail: ");
        for (int j = 0; j < contacts[i].email_count; j++) {
            printf("%s ", contacts[i].emails[j]);
        }
        printf("\nСоцсети: ");
        for (int j = 0; j < contacts[i].social_count; j++) {
            printf("%s ", contacts[i].social_links[j]);
        }
        printf("\nМессенджеры: ");
        for (int j = 0; j < contacts[i].messenger_count; j++) {
            printf("%s ", contacts[i].messenger_links[j]);
        }
        printf("\n\n");
    }
}

void menu() {
    printf("\n--- Меню ---\n");
    printf("1. Добавить контакт\n");
    printf("2. Редактировать контакт\n");
    printf("3. Удалить контакт\n");
    printf("4. Показать все контакты\n");
    printf("5. Выйти\n");
    printf("Выберите команду: ");
}

int main() {
    while (1) {
        menu();
        int choice;
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                editContact();
                break;
            case 3:
                deleteContact();
                break;
            case 4:
                displayContacts();
                break;
            case 5:
                printf("Выход из программы.\n");
                return 0;
            default:
                printf("Неверный ввод. Пожалуйста, попробуйте снова.\n");
        }
    }

    return 0;
}
