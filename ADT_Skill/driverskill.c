#include <stdio.h>
#include <stdlib.h>
#include "listlinier.h"

int main()
{
    List l;
    CreateEmpty(&l);
    // Coba masukin skill
    RandomSkill(&l, 30);
    RandomSkill(&l, 50);
    RandomSkill(&l, 80);
    // Nunjukkin menu
    PrintMenuSkill(l);
    // Delete Skill kedua
    DeleteSkill(&l,2);
    PrintMenuSkill(l);
}