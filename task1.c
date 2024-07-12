#include <stdio.h>
#include <string.h>
#define Max_Sym 10
#define Max_Soc 5

typedef struct social
{
    char *workmail[Max_Soc];
    char *email[Max_Soc];
    char *social[Max_Soc];
};


typedef struct person
{

    char *firstname;
    char *surname;
    char *thirdname;
    char *workplace;
    char *post;
};

int addperson(){
    char *firstname;
    char *surname;
    char *thirdname;
    char *workplace;
    char *post;
    printf("Ввод данных контакта:");
    printf("Введите имя:");
    scanf("%s", firstname);
    printf("Введите Фамилию:");
    scanf("%s", surname);
    printf("Введите Отчество:");
    scanf("%s", thirdname);
    printf("Введите место работы:");
    scanf("%s", workplace);
    printf("Введите Должность:");
    scanf("%s", post);

};

void main(){
int k;
while(1){
    printf("Введите цифру для выбора:");
    printf("1)Ввести контакт");
    printf("2)Удалить контакт");
    printf("3)Редактировать контакт");
    printf("4)Вывести информацию из книги");
    scanf("%d", k);
    switch (k)
    {
    case (1):
    addperson();
        break;
    
    case (2):
    remperson();
        break;
    
    case (3):
    redperson();
        break;
    
    case (4):
    info();
        break;
    
    default:
    printf("Ошибка ввода");
        break;
    }}
    printf('\n');
return;
};
