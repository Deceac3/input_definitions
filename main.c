#include "operations.h"

int main(){
    char *buf=NULL;
    buf=line_input();
    check(buf);
    path_wiev(buf);
    return 0;
}
