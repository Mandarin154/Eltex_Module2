#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA_LENGTH 256

typedef struct ContactNode {
  char data[MAX_DATA_LENGTH];
  struct ContactNode *prev;
  struct ContactNode *next;
} ContactNode;

ContactNode *createContactNode(const char *data) {
  ContactNode *newContact = (ContactNode *)malloc(sizeof(ContactNode));
  if (newContact == NULL) {
    fprintf(stderr, "Ошибка выделения памяти\n");
    exit(1);
  }

  strcpy(newContact->data, data);
  newContact->prev = NULL;
  newContact->next = NULL;

  return newContact;
}

void insertContact(ContactNode **head, ContactNode *newContact) {
  if (*head == NULL) {
    *head = newContact;
    return;
  }

  ContactNode *current = *head;
  while (current->next != NULL && strcmp(current->next->data, newContact->data) < 0) {
    current = current->next;
  }

  newContact->next = current->next;
  if (current->next != NULL) {
    current->next->prev = newContact;
  }
  newContact->prev = current;
  current->next = newContact;
}

void printContactList(ContactNode *head) {
  if (head == NULL) {
    printf("Список контактов пуст.\n");
    return;
  }

  ContactNode *current = head;
  while (current != NULL) {
    printf("%s\n", current->data);
    current = current->next;
  }
}

void freeContactList(ContactNode *head) {
  ContactNode *current = head;
  while (current != NULL) {
    ContactNode *temp = current;
    current = current->next;
    free(temp);
  }
}

void editContact(ContactNode **head, const char *searchData, const char *newData) {
  ContactNode *current = *head;
  while (current != NULL) {
    if (strcmp(current->data, searchData) == 0) {
      strcpy(current->data, newData);
      printf("Контакт изменен.\n");
      return;
    }
    current = current->next;
  }
  printf("Контакт не найден.\n");
}

void deleteContact(ContactNode **head, const char *searchData) {
  ContactNode *current = *head;
  while (current != NULL) {
    if (strcmp(current->data, searchData) == 0) {
      if (current->prev != NULL) {
        current->prev->next = current->next;
      } else {
        *head = current->next;
      }

      if (current->next != NULL) {
        current->next->prev = current->prev;
      }

      free(current);
      printf("Контакт удален.\n");
      return;
    }
    current = current->next;
  }
  printf("Контакт не найден.\n");
}

int main() {
  ContactNode *head = NULL;

  while (1) {
    printf("Введите команду (add - добавить контакт, list - показать список, edit - редактировать контакт, delete - удалить контакт, exit - выход): ");
    char command[20];
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = 0; 

    if (strcmp(command, "add") == 0) {
      printf("Введите данные о контакте (имя, фамилия, отчество, компания, должность, телефон, email, соц сети, разделенные запятыми): ");
      char data[MAX_DATA_LENGTH];
      fgets(data, sizeof(data), stdin);
      data[strcspn(data, "\n")] = 0;

      ContactNode *newContact = createContactNode(data);
      insertContact(&head, newContact);
    } else if (strcmp(command, "list") == 0) {
      printContactList(head);
    } else if (strcmp(command, "edit") == 0) {
      printf("Введите данные контакта для редактирования: ");
      char searchData[MAX_DATA_LENGTH];
      fgets(searchData, sizeof(searchData), stdin);
      searchData[strcspn(searchData, "\n")] = 0; 
      printf("Введите новые данные контакта: ");
      char newData[MAX_DATA_LENGTH];
      fgets(newData, sizeof(newData), stdin);
      newData[strcspn(newData, "\n")] = 0; 
      editContact(&head, searchData, newData);
    } else if (strcmp(command, "delete") == 0) {
      printf("Введите данные контакта для удаления: ");
      char searchData[MAX_DATA_LENGTH];
      fgets(searchData, sizeof(searchData), stdin);
      searchData[strcspn(searchData, "\n")] = 0; 
      deleteContact(&head, searchData);
    } else if (strcmp(command, "exit") == 0) {
      break;
    } else {
      printf("Неизвестная команда.\n");
    }
  }

  freeContactList(head);
  return 0;
}