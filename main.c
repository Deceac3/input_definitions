#include "operations.h"

int main(){
    char *buf=NULL;
    buf=line_input();
    if(!check(buf)){
        return 0;
    };
    if(buf=processing(buf)==NULL){
        return 0;
    };
    path_wiev(buf);
    return 0;
}
