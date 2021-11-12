#include<stdio.h>
#include"buff.h"
#include"buff.c"

int main(){
    BUFF B;
    CreateEmptyBuff(&B);
    IsiBuff(&B,1,"Senter ajaib", "Terang sekali");
    PrintBuff(B, 1);
    return 0;
}