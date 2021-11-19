#include "listlinier.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int r1,r2,r3,x,posisi;
    r1 = random(1);
    List skill;
    CreateEmpty(&skill);
    printf("%d\n", r1);
    InsVLast(&skill, r1);
    r2 = random(3);
    printf("%d\n", r2);
    InsVLast(&skill, r2);
    r3 = random(2);
    printf("%d\n", r3);
    InsVLast(&skill, r3);
    PrintInfo(skill);
    printf("\n");
    PrintSkill(skill);
    printf("Masukkan indeks skill yang ingin dihapus: ");
    scanf("%d", &posisi);
    printf("Hapus Skill ke-%d\n", posisi);
    DelX(&skill, posisi);
    PrintInfo(skill);
    printf("\n");
    PrintSkill(skill);
}