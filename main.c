#include "operations.h"

int main(){
    struct new_path path;
    char *buf=NULL;
    buf=line_input();
    char *new_way= NULL;
    new_way = (char*)malloc(MAX_PATH*sizeof(int));
    path.path = new_way;
    path.count = 0;
    if(!check(buf)){
        return 0;
    };
    if(processing(&path,buf)){
        return 0;
    };
    path_wiev(path.path);
    return 0;
}
