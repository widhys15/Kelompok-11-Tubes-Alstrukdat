#include "listlinier.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void skill(List L);
void skill(List L)
{
    int inputs;
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