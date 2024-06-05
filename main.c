#include "operations.h"

int main(){
    char *buf=NULL;
    buf=line_input();
    if(!check(buf)){
        return 0;
    };
    if(!processing(buf)){
        return 0;
    };
    path_wiev(buf);
    return 0;
}
