#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CONTACTS 100 
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
  char messenger_links[MAX_SOC ][MAX_SOC ];
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

  printf("Введите Отчество: ");
  scanf("%s", new_person.thirdname);

  printf("Введите место работы (необязательно): ");
  scanf("%s", new_person.company);

  printf("Введите должность (необязательно): ");
  scanf("%s", new_person.post);

  printf("Введите номера телефонов (разделяйте пробелами, введите 'end' для завершения): ");
  new_person.phone_count = 0;
  while (1) {
    char phone[MAX_PHONE_NUM];
    scanf("%s", phone);
    if (strcmp(phone, "end") == 0) {
      break;
    }
    strcpy(new_person.phone_numbers[new_person.phone_count++], phone);
  }

  printf("Введите адреса электронной почты (разделяйте пробелами, введите 'end' для завершения): ");
  new_person.email_count = 0;
  while (1) {
    char email[MAX_EMAIL_LEN];
    scanf("%s", email);
    if (strcmp(email, "end") == 0) {
      break;
    }
    strcpy(new_person.emails[new_person.email_count++], email);
  }

  printf("Введите ссылки на страницы в соцсетях (разделяйте пробелами, введите 'end' для завершения): ");
  new_person.social_count = 0;
  while (1) {
    char link[MAX_SOC];
    scanf("%s", link);
    if (strcmp(link, "end") == 0) {
      break;
    }
    strcpy(new_person.social_links[new_person.social_count++], link);
  }

  printf("Введите ссылки на профили в мессенджерах (разделяйте пробелами, введите 'end' для завершения): ");
  new_person.messenger_count = 0;
  while (1) {
    char link[MAX_SOC];
    scanf("%s", link);
    if (strcmp(link, "end") == 0) {
      break;
    }
    strcpy(new_person.messenger_links[new_person.messenger_count++], link);
  }

  contacts[contact_count++] = new_person;
  printf("Контакт добавлен.\n");
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
  printf("\n");
  printf("Адреса электронной почты: ");
  for (int i = 0; i < contact->email_count; i++) {
    printf("%s ", contact->emails[i]);
  }
  printf("\n");
  printf("Ссылки на соцсети: ");
  for (int i = 0; i < contact->social_count; i++) {
    printf("%s ", contact->social_links[i]);
  }
  printf("\n");
  printf("Ссылки на мессенджеры: ");
  for (int i = 0; i < contact->messenger_count; i++) {
    printf("%s ", contact->messenger_links[i]);
  }
  printf("\n");

  printf("Что вы хотите отредактировать?\n");
  printf("1. Имя\n");
  printf("2. Фамилию\n");
  printf("3. Отчествоn");
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
      printf("Введите новые номера телефонов (разделяйте пробелами, введите 'end' для завершения): ");
      contact->phone_count = 0;
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
      printf("Введите новые адреса электронной почты (разделяйте пробелами, введите 'end' для завершения): ");
      contact->email_count = 0;
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
      printf("Введите новые ссылки на соцсети (разделяйте пробелами, введите 'end' для завершения): ");
      contact->social_count = 0;
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
      printf("Введите новые ссылки на мессенджеры (разделяйте пробелами, введите 'end' для завершения): ");
      contact->messenger_count = 0;
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
      printf("Неверный выбор.\n");
  }

  printf("Контакт обновлен.\n");
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

  // Перенос номеров телефонов из удаляемого контакта
  for (int i = 0; i < contacts[index].phone_count; i++) {
    // Проверка, есть ли свободное место в массиве phone_numbers последнего контакта
    if (contacts[contact_count - 1].phone_count < MAX_PHONE_NUM) {
      strcpy(contacts[contact_count - 1].phone_numbers[contacts[contact_count - 1].phone_count++], 
             contacts[index].phone_numbers[i]);
    } else {
      // Если свободного места нет, выводим сообщение об ошибке
      printf("Невозможно добавить все номера телефонов в последний контакт.\n");
      break; 
    }
  }

  for (int i = index; i < contact_count - 1; i++) {
    contacts[i] = contacts[i + 1];
  }
  contact_count--;
  printf("Контакт удален.\n");
}


void printContacts() {
  if (contact_count == 0) {
    printf("Список контактов пуст.\n");
    return;
  }

  for (int i = 0; i < contact_count; i++) {
    printf("----------------------------------------\n");
    printf("Контакт %d:\n", i);
    printf("Имя: %s\n", contacts[i].firstname);
    printf("Фамилия: %s\n", contacts[i].lastname);
    printf("Отчество: %s\n", contacts[i].thirdname);
    printf("Место работы: %s\n", contacts[i].company);
    printf("Должность: %s\n", contacts[i].post);
    printf("Номера телефонов: ");
    for (int j = 0; j < contacts[i].phone_count; j++) {
      printf("%s ", contacts[i].phone_numbers[j]);
    }
    printf("\n");
    printf("Адреса электронной почты: ");
    for (int j = 0; j < contacts[i].email_count; j++) {
      printf("%s ", contacts[i].emails[j]);
    }
    printf("\n");
    printf("Ссылки на соцсети: ");
    for (int j = 0; j < contacts[i].social_count; j++) {
      printf("%s ", contacts[i].social_links[j]);
    }
    printf("\n");
    printf("Ссылки на мессенджеры: ");
    for (int j = 0; j < contacts[i].messenger_count; j++) {
      printf("%s ", contacts[i].messenger_links[j]);
    }
    printf("\n");
  }
}

int main() {
  int choice;

  while (1) {
    printf("\nТелефонная книга\n");
    printf("1. Добавить контакт\n");
    printf("2. Редактировать контакт\n");
    printf("3. Удалить контакт\n");
    printf("4. Вывести список контактов\n");
    printf("0. Выход\n");
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
        deleteContact();
        break;
      case 4:
        printContacts();
        break;
      case 0:
        printf("Выход.\n");
        return 0;
      default:
        printf("Неверный выбор.\n");
    }
  }

  return 0;
}