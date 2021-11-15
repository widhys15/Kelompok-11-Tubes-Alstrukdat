#include "listlinier.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void skill(List L, int inputs);
void skill(List L, int inputs)
{
    PrintMenuSkill(L);
    printf("\nMasukkan skill: ");
    scanf("%d", &inputs);
    if (inputs > 0)
    {
        printf("\nPlayer memakai skill ");
        PrintSkillKe(L, inputs);
        printf("\n");
        DelX(&L, inputs);
    }
    else if (inputs < 0)
    {
        inputs = inputs * (-1);
        printf("\nPlayer membuang skill ");
        PrintSkillKe(L, inputs);
        printf("\n");
        DelX(&L, inputs);
    }
    else
    {
        printf("\nPlayer keluar dari menu Skill\n");
        // Masuk main menu command
    }
}

int main()
{
    int compare,inputs;
    List skill;
    CreateEmpty(&skill);
    char inp[20];
    char str[20] = "SKILL";
    int r1 = random(1);
    int r2 = random(3);
    int r3 = random(2);
    InsVLast(&skill, r1);
    InsVLast(&skill, r2);
    InsVLast(&skill, r3);
    int r4 = random(12);
    printf("Masukkan command: ");
    scanf("%s", &inp);
    compare = strcmp(str,inp);
    PrintMenuSkill(skill);
    printf("\nMasukkan skill: ");
    scanf("%d", &inputs);
    if (inputs > 0)
    {
        printf("\nPlayer memakai skill ");
        PrintSkillKe(skill, inputs);
        printf("\n");
        DelX(&skill, inputs);
    }
    else if (inputs < 0)
    {
        inputs = inputs * (-1);
        printf("\nPlayer membuang skill ");
        PrintSkillKe(skill, inputs);
        printf("\n");
        DelX(&skill, inputs);
    }
    else
    {
        printf("\nPlayer keluar dari menu Skill\n");
        // Masuk main menu command
    }
    PrintSkill(skill);
    
    /*int r1,r2,r3,r4,x,posisi,compare;
    char inp[20];
    char str[20] = "SKILL";
    r1 = random(1);
    r2 = random(3);
    r3 = random(2);
    List skill;
    CreateEmpty(&skill);
    printf("Masukkan command: ");
    scanf("%s", &inp);
    compare = strcmp(str,inp);
    if (compare == 0)
    {
        InsVLast(&skill, r1);
        InsVLast(&skill, r2);
        InsVLast(&skill, r3);
    }
    PrintSkill(skill);
    printf("\nTekan 0 untuk keluar. Masukkan bilangan negatif untuk membuang skill.\n");
    printf("Masukkan skill: ");
    scanf("%d", &posisi);
    printf("\n");
    if (posisi > 0)
    {
        printf("player memakai skill %d\n", posisi);
        DelX(&skill, posisi);
    }
    else if (posisi == 0)
    {
        printf("Keluar\n");
    }
    else
    {
        posisi = posisi * (-1);
        printf("player membuang skill %d\n", posisi);
        DelX(&skill, posisi);
    }
    PrintSkill(skill);
    r4 = random(6);
    printf("\nMasukkan command: ");
    scanf("%s", &inp);
    compare = strcmp(str,inp);
    if (compare == 0)
    {
        InsVLast(&skill, r4);
        InsVLast(&skill, r1);
        InsVLast(&skill, r2);
        InsVLast(&skill, r3);
        InsVLast(&skill, r1);
        InsVLast(&skill, r2);
        InsVLast(&skill, r3);
    }
    PrintSkill(skill);
    printf("\nTekan 0 untuk keluar. Masukkan bilangan negatif untuk membuang skill.\n");
    printf("Masukkan skill: ");
    scanf("%d", &posisi);
    if (posisi > 0)
    {
        printf("player memakai skill %d\n", posisi);
        DelX(&skill, posisi);
    }
    else if (posisi == 0)
    {
        printf("Keluar\n");
    }
    else
    {
        posisi = posisi * (-1);
        printf("player membuang skill %d\n", posisi);
        DelX(&skill, posisi);
    }
    printf("\n");
    PrintSkill(skill);
    printf("\n");
    if (NbElmt(skill) != 10)
    {
        InsVLast(&skill, r1);
    }
    else
    {
        printf("Skill penuh\n");
    }
    printf("\n");
    PrintSkill(skill);
    //printf("Hapus Skill ke-%d\n", posisi);
    //DelX(&skill, posisi);
    //PrintInfo(skill);
    //printf("\n");*/
    
}