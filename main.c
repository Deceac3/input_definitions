#include "operations.h"

int main(){
    struct new_path path;
    char *buf=NULL;
    buf=line_input();
    char *new_way= NULL;
    new_way = (char*)malloc(MAX_PATH*sizeof(int));
    path.path = new_way;
    path.count = 0;
    if(check(buf)){
    }
    else{
        return 0;
        printf("Error: Ошибка в формате записи пути используются неккоректные символы\n");
    }
    if(processing(&path,buf)){
    }
    else{
        return 0;
        printf("Error: Ошибка в пути, он неккоректно заисан\n");
    }
    path_wiev(path.path);
    return 0;
}
