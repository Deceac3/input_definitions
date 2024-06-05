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
        for (size_t i = 0; i <= sizeof(buf); i++){          //Проверяем на допустимые символы. Других не должно быть вообще.
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
                printf("Введённый вами символ недопустим в наборе путей: %d[%c]",buf[i]);
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
