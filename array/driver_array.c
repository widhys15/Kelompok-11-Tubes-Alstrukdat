#include <stdio.h>
#include "array.h"
#include "array.c"

int main()
{
    //{'.','.','#','.','.'}
    char t[6] = {'.', '.', '#', '.', '.'};
    Map lvl1;
    CreateMap(&lvl1, 5, t);
    PrintMap(&lvl1);
    SetTeleport(&lvl1, 1, 3);
    int tmp = InfoTp(&lvl1, 1);
    printf("\n");
    printf("%d\n", tmp);
    return 0;
}