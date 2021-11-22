#include "player.h"
#include "player.c"
#include <stdio.h>

int main()
{
    Player Player1;
    CreatePlayer(&Player1, 1);
    PrintName(Player1);
}