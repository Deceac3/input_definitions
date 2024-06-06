#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define MAX_PATH 260
#define DEEP_WAY 5

char* line_input();
_Bool check(char*);
void path_wiev(char*);
char* processing(char*);

char* line_input(){
    char *giga;
    giga = (char*)malloc(MAX_PATH*sizeof(int));
    fgets(giga,MAX_PATH,stdin);
    return (giga);
}

_Bool check(char* inp){
    char *buf=NULL;
    buf = strtok(inp,"\0");
    if (buf!=NULL)
    {
        for (size_t i = 0; i <= MAX_PATH; i++){          //Проверяем на допустимые символы. Других не должно быть вообще.
            if (((buf[i]<'z')&&(buf[i]>'a'))||((buf[i]>'A')&&(buf[i]<'Z'))||((buf[i]>'0')&&(buf[i]<'9'))||(buf[i]=='.')||(buf[i]=='+')||(buf[i]=='\\')||(buf[i]=='/')||(buf[i]=='\n'))
            {
                if (buf[i]=='\n')
                {
                    printf("Проверка на символы закончена\n");
                    break;
                }
            }
            else
            {
                printf("Error: Введённый вами символ недопустим в наборе путей: %d[%c]", buf[i]);
                return false;
            }
        }
    }
    else
    {
        printf("Error: Введённый путь выходит за предел в 260 символов.\n");    // по стандарту Windows PATH < 260 иначе ошибка
        return false;
    }
    return true;
    //Так как остальные 2 проверки нашего пути напрямую связанны с процессом преобразования строки
    //мы засунем эти функции в сам процесс преобразования строки.
}

void path_wiev(char* buf){
    printf("new path: %s", buf);
}

char* processing(char* buf){
    char *new_way= NULL;
    _Bool first_p=true;
    new_way = (char*)malloc(MAX_PATH*sizeof(int));
    for (size_t i = 0; i < MAX_PATH; i++)
    {
        if (first_p)
        {
            printf("%c\n",buf[i]);
            if (buf[i]=='c')
            {
                /* находим первым символом c значит проверяем на cygdrive */
                char *test=NULL;
                test=strtok(strchr(buf, 'c'), 'cygdrive');
                test[10] = '\0';
                return test;
            }
            else if ((buf[i]>'0')&&(buf[i]<'9'))
            {
                /* адресация может начинаться с ip, если находим первым число, то проверяем на условия ip*/
                return buf;
            }
            else if ((buf[i]==' ')||(buf[i]=='/'))
            {
                /* skip moment. такое может быть, что начало адреса записаное после нескольких пробеллов или после / */
            }
            else
            {
                printf("Error: путь записан неверно ...%c%c|%c|%c%c...",buf[i-2],buf[i-1],buf[i],buf[i+1],buf[i+2]);
                return false;
            }
        }
    }
}
