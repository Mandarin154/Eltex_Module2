#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct Node {
    struct Contact contact;
    struct Node *left;
    struct Node *right;
} Node;

// Глобальная переменная для корня дерева
Node *root = NULL;

// Прототипы функций
Node* createNode(struct Contact contact);
Node* insert(Node* node, struct Contact contact);
void inOrder(Node* node, int* count);
void editContactData(struct Contact *contact);
void editContact(Node *node, int index, int *count);
Node* deleteNode(Node* root, int index, int *count);
void menu();

Node* createNode(struct Contact contact) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->contact = contact;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* node, struct Contact contact) {
    if (node == NULL) {
        return createNode(contact);
    }
    if (strcmp(contact.lastname, node->contact.lastname) < 0) {
        node->left = insert(node->left, contact);
    } else {
        node->right = insert(node->right, contact);
    }
    return node;
}

void inOrder(Node* node, int* count) {
    if (node != NULL) {
        inOrder(node->left, count);
        printf("Контакт %d:\n", *count);  
        printf("Имя: %s\n", node->contact.firstname);
        printf("Фамилия: %s\n", node->contact.lastname);
        printf("Отчество: %s\n", node->contact.thirdname);
        printf("Компания: %s\n", node->contact.company);
        printf("Должность: %s\n", node->contact.post);
        printf("Телефоны: ");
        for (int j = 0; j < node->contact.phone_count; j++) {
            printf("%s ", node->contact.phone_numbers[j]);
        }
        printf("\nEmail: ");
        for (int j = 0; j < node->contact.email_count; j++) {
            printf("%s ", node->contact.emails[j]);
        }
        printf("\nСоцсети: ");
        for (int j = 0; j < node->contact.social_count; j++) {
            printf("%s ", node->contact.social_links[j]);
        }
        printf("\nМессенджеры: ");
        for (int j = 0; j < node->contact.messenger_count; j++) {
            printf("%s ", node->contact.messenger_links[j]);
        }
        printf("\n\n");

        (*count)++;
        inOrder(node->right, count);
    }
}

void editContactData(struct Contact *contact) {
    printf("Имя: %s\n", contact->firstname);
    printf("Фамилия: %s\n", contact->lastname);
    printf("Отчество: %s\n", contact->thirdname);
    printf("Компания: %s\n", contact->company);
    printf("Должность: %s\n", contact->post);
    printf("Телефоны: ");
    for (int j = 0; j < contact->phone_count; j++) {
        printf("%s ", contact->phone_numbers[j]);
    }
    printf("\nEmail: ");
    for (int j = 0; j < contact->email_count; j++) {
        printf("%s ", contact->emails[j]);
    }
    printf("\nСоцсети: ");
    for (int j = 0; j < contact->social_count; j++) {
        printf("%s ", contact->social_links[j]);
    }
    printf("\nМессенджеры: ");
    for (int j = 0; j < contact->messenger_count; j++) {
        printf("%s ", contact->messenger_links[j]);
    }
    printf("\n");
    
    // Выбор поля для редактирования
    printf("Что вы хотите отредактировать?\n");
    printf("1. Имя\n");
    printf("2. Фамилию\n");
    printf("3. Отчество\n");
    printf("4. Компанию\n");
    printf("5. Должность\n");
    printf("6. Номера телефонов\n");
    printf("7. Адреса электронной почты\n");
    printf("8. Ссылки на соцсети\n");
    printf("9. Ссылки на мессенджеры\n");
    printf("0. Вернуться в главное меню\n");

    int choice;
    scanf("%d", &choice);

    // Обновление данных контакта в зависимости от выбора
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
            printf("Введите новую компанию: ");
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

void editContact(Node *node, int index, int *count) {
    if (node != NULL) {
        editContact(node->left, index, count);
        if (*count == index) {  
            printf("Редактирование контакта:\n");
            editContactData(&node->contact);
        }
        (*count)++;
        editContact(node->right, index, count);
    }
}

Node* deleteNode(Node* root, int index, int *count) {
    if (root == NULL) return root;

    // Сначала обходим левое поддерево
    root->left = deleteNode(root->left, index, count);
    
    if (*count == index) {
        // Удаление узла
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }

        // Узел с двумя поддеревьями: получить прямого преемника
        Node *temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }

        // Заменить корень на прямого преемника
        root->contact = temp->contact;
        root->right = deleteNode(root->right, *count + 1, count); 
    }
    
    (*count)++;
    return root; 
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
            case 1: {
                struct Contact new_person;
                printf("Введите имя: ");
                scanf("%s", new_person.firstname);
                printf("Введите фамилию: ");
                scanf("%s", new_person.lastname);
                printf("Введите отчество: ");
                scanf("%s", new_person.thirdname);
                printf("Введите компанию (необязательно): ");
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

                root = insert(root, new_person);
                printf("Контакт добавлен.\n");
                break;
            }
            case 2: {
                int count = 0;
                printf("Введите номер контакта для редактирования:\n");
                inOrder(root, &count); 
                printf("Номер контакта: ");
                int index;
                scanf("%d", &index);
                count = 0; 
                editContact(root, index, &count); 
                break;
            }
            case 3: {
                int count = 0;
                printf("Введите номер контакта для удаления:\n");
                inOrder(root, &count); 
                printf("Номер контакта: ");
                int index;
                scanf("%d", &index);
                count = 0; 
                root = deleteNode(root, index, &count); 
                printf("Контакт удален.\n");
                break;
            }
            case 4: {
                int count = 0;
                inOrder(root, &count);
                break;
            }
            case 5:
                printf("Выход из программы.\n");
                return 0;
            default:
                printf("Неверный ввод. Пожалуйста, попробуйте снова.\n");
        }
    }

    return 0;
}
