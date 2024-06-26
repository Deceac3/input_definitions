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
_Bool path_control(struct new_path*,size_t*,char*);

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
            if (((buf[i]<='z')&&(buf[i]>='a'))||((buf[i]>='A')&&(buf[i]<='Z'))||((buf[i]>='0')&&(buf[i]<='9'))||(buf[i]=='.')||(buf[i]=='+')||(buf[i]=='\\')||(buf[i]=='/')||(buf[i]=='\n')||(buf[i]==':'))
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
    printf("new path: %s\n", buf);
}

_Bool processing(struct new_path* path,char* buf){
    _Bool path_poz= true;
    for (size_t i = 0; i < MAX_PATH; i++)
    {
        if (path_poz)
        {
            if ((buf[i]=='c')&&(i<260))
            {
                /* находим первым символом c значит проверяем на cygdrive/ */
                if(check_c(i,buf)){
                    i += 9;
                    if (((buf[i]>='A')&&(buf[i]<='Z'))||((buf[i]>='a')&&(buf[i]<='z')))
                    {
                        if (buf[i+1]=='/')
                        {
                            path->path[path->count]=toupper(buf[i]);
                            path->count++;
                            path->path[path->count]=':';
                            path->count++;
                            path->path[path->count]='\\';
                            path->count++;    // На этом моменте мы имеем 1- наименование католога 2-всё остальное пути в катологе
                            i+=2;
                            _Bool ccheck = true;
                            int count = 0;
                            while (ccheck)
                            {
                                if (count <=4){
                                    if(path_control(path,&i,buf)){
                                        if (buf[i]=='+')
                                        {
                                            path_poz = false;
                                            ccheck = false;
                                        }
                                        else if (buf[i]=='\n')
                                        {
                                            return true;
                                        }
                                        else{
                                            count++;
                                            i++;
                                        }
                                    }
                                    else
                                    {
                                        return false;
                                    }
                                }
                                else
                                {
                                    printf("Error: длинна одного стандартного пути не может превышать 5 эллементов\n");
                                    return false;
                                }
                            }
                        }
                        else
                        {
                            printf("Error: ожидалось '/' на символе %ld |%c|\n", i+1,buf[i+1]);
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
                    printf("Error: неверно записан путь\n");
                    return false;
                }
            }
            else if ((buf[i]>='0')&&(buf[i]<='9'))
            {
                /* 
                адресация может начинаться с ip, если находим первым число, то проверяем на условия ip
                Так как мы подключаемся к удалённому серверу по индксу, нам не нужно узнавать его наименование корня дерева
                */
                _Bool ip_check=true;
                size_t numbs=0;
                int count=0;
                char ip[4];
                ip[0]=' ';
                ip[1]=' ';
                ip[2]=' ';
                ip[3]=' ';
                while (ip_check)
                {
                    if ((count<4))
                    {
                        if (((buf[i+1]=='.')||((numbs==3)&&(buf[i+1]==':')))&&(buf[i]>='0')&&(buf[i]<='9'))
                        {
                            ip[count] = buf[i]; 
                            if (strtol(ip, NULL,10)<=255)
                            {
                                path->path[path->count]=buf[i];
                                path->count++;
                                if (numbs<3)
                                {
                                    path->path[path->count]='.';
                                    path->count++;
                                }
                                count=0;
                                i+=2;
                                numbs++;
                                ip[0]=' ';
                                ip[1]=' ';
                                ip[2]=' ';
                                ip[3]=' ';
                            }
                            else
                            {
                                printf("Error: введённый ip адрес не соответствует стандарту и он не должен быть больше 255 %s - %ld|%ld\n",ip,strtol(ip, NULL,10),numbs);
                                return false;
                            }
                        }
                        else if ((buf[i]>='0')&&(buf[i]<='9'))
                        {
                            path->path[path->count]=buf[i];
                            path->count++;
                            ip[count] = buf[i];
                            count++;
                            i++;
                        }
                        else
                        {
                            printf("Error: ip-адрес не может содержать никаких других символов, кроме 0-9\n");
                            return false;
                        }
                        
                    }
                    else
                    {
                        printf("Error: значение ip записано неверно\n");
                        return false;
                    }
                    if (numbs==4)
                    {
                        path->path[path->count]=':';
                        path->count++;
                        path->path[path->count]='\\';
                        path->count++;
                        i ++;
                        _Bool ccheck = true;
                        int count = 0;
                        while (ccheck)
                        {
                            if (count <=4){
                                if(path_control(path,&i,buf)){
                                    if (buf[i]=='+')
                                    {
                                        path_poz = false;
                                        ccheck = false;
                                    }
                                    else if (buf[i]=='\n')
                                    {
                                        return true;
                                    }
                                    else{
                                        count++;
                                        i++;
                                    }
                                }
                                else
                                {
                                    return false;
                                }
                            }
                            else
                            {
                                printf("Error: длинна одного стандартного пути не может превышать 5 эллементов\n");
                                return false;
                            }
                        }
                    }
                    
                }
                return true;
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
    }
    printf("Error; invalid\n");
    return false;
}

_Bool check_c(int i,char* buf){
    char check[11] = "cygdrive/";
    char *bufs=NULL;
    bufs = strstr(buf, check);
    if(bufs!=NULL){
        return true;
    }
    else
    {
        return false;
    }
}

_Bool path_control(struct new_path *path, size_t* i, char *buf){
    size_t dot_count = 0;
    while (true)
    {
        if (((buf[*i]>='A')&&(buf[*i]<='Z'))||((buf[*i]>='a')&&(buf[*i]<='z'))||((buf[*i]>='0')&&buf[*i]<='9'))
        {
            path->path[path->count]=buf[*i];
            path->count++;
            *i=*i+1;
        }
        else if (buf[*i]=='.')
        {
            if (dot_count<1)
            {
                path->path[path->count]=buf[*i];
                path->count++;
                dot_count++;
                *i=*i+1;
            }
            else
            {
                printf("Error: в записи путя не может быть более 1 точки\n");
                return false;
            }
        }
        else if (buf[*i]=='/')
        {
            path->path[path->count]='\\';
            path->count++;
            return true;
        }
        else if (buf[*i]=='+')
        {
            path->path[path->count]=buf[*i];
            path->count++;
            return true;
        }
        else if (buf[*i]=='\n')
        {
            return true;
        }
    }
}
