#include "mesin_kata.h"
#include <stdio.h>
#include "mesin_kata.c"
#include "../mesinkar/mesin_kar.h"
#include "../mesinkar/mesin_kar.c"
// #include "geserkata.c"
void copyKata(Kata k1, Kata *k2)
{
    (*k2) = k1;
}
void printKata(Kata kata);
int main()
{
    Kata tmp;
    STARTKATA();
    while (!EndKata)
    {
        puts("--------------");
        printKata(CKata);
        puts("");
        puts("--------------");
        int t = KataInt(CKata);
        printf("%d", t);
        ADVKATA();
    }
}
void printKata(Kata kata)
{
    for (int i = 1; i <= kata.Length; i++)
    {
        printf("%c", kata.TabKata[i]);
    }
}