#include <stdio.h>
#include "array.h"
#include "array.c"

int main()
{
    // ### Cek Fungsi CreateMap ###
    puts("### Cek Fungsi CreateMap ###");
    char t[6] = {'.', '.', '#', '.', '.'};
    Map lvl1;
    CreateMap(&lvl1, 5, t);

    // ### Cek Fungsi Print Map ###
    puts("\n### Cek Fungsi Print Map ###");
    PrintMap(&lvl1);

    // ### Cek Fungsi SetTeleport ###
    puts("\n### Cek Fungsi SetTeleport ###");
    puts("Sebelum diset: ");
    printf("Teleport out pada petak pertama adalah petak %d\n", Tp(lvl1.map[0]));
    SetTeleport(&lvl1, 1, 3);
    puts("Sesudah diset: ");
    printf("Teleport out pada petak pertama adalah petak %d\n", Tp(lvl1.map[0]));
}