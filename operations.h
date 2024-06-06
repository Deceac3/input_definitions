#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define MAX_PATH 260
#define DEEP_WAY 5

struct new_path
{
    char *path;
    size_t count;
};

char* line_input();
_Bool check(char*);
void path_wiev(char*);
_Bool processing(struct new_path*,char*);

_Bool check_c(int, char*);


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
                    break;
                }
            }
            else
            {
                printf("Error: Введённый вами символ недопустим в наборе путей: %ld[%c]",i,buf[i]);
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

_Bool processing(struct new_path* path,char* buf){
    for (size_t i = 0; i < MAX_PATH; i++)
    {
        if ((buf[i]=='c')&&(i<260-9))
        {
            /* находим первым символом c значит проверяем на cygdrive */
            if(check_c(i,buf)){
                i += 9;
                if (((buf[i]>='A')&&(buf[i]<='Z'))||((buf[i]>='a')&&(buf[i]<='z')))
                {
                    if (buf[i+1]=='\\')
                    {
                        path->path[path->count]=toupper(buf[i]);
                        path->count++;
                        path->path[path->count]='/';
                        path->count;    // На этом моменте мы имеем 1- наименование католога 2-всё остальное пути в катологе
                    }
                    else
                    {
                        return false;
                    }
                    
                }
                else
                {
                    printf("Error: ожидалось наименование каталога в %ld символе |%c|",i,buf[i]);
                    return false;
                }
            }
            else{
                return false;
            }
        }
        else if ((buf[i]>'0')&&(buf[i]<'9'))
        {
            /* адресация может начинаться с ip, если находим первым число, то проверяем на условия ip*/
            return true;
        }
        else if ((buf[i]==' ')||(buf[i]=='/'))
        {
            /* skip moment. такое может быть, что начало адреса записаное после нескольких пробеллов или после / */
        }
        else if(buf[i]=='\n'){
            return true;
        }
        else
        {
            printf("Error: путь записан неверно ...%c%c|%c|%c%c...\n",buf[i-2],buf[i-1],buf[i],buf[i+1],buf[i+2]);
            return false;
        }
    }
    return false;
}

_Bool check_c(int i,char* buf){
    char check[11] = "cygdrive\\";
    char *bufs=NULL;
    bufs = strstr(buf, check);
    if(bufs!=NULL){
        return true;
    }
    else
    {
        return false;
    }
    return true;
}
