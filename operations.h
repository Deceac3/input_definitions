#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_PATH 260
#define DEEP_WAY 5

char* line_input();

char* line_input(){
    char *giga;
    giga = (char*)malloc(MAX_PATH*sizeof(int));
    fgets(giga,MAX_PATH,stdin);
    return (giga);
}
