#include "player.h"
#include "player.c"
#include "../ADT_Mesinkata/mesin_kata.h"
#include <stdio.h>

int main()
{
    // Define players
    Players ArrayPlayer;
    CreateEmptyArrayPlayer(&ArrayPlayer);
    printf("Berapa player: ");
    STARTKATA();
    int jumlahplayer = KataInt(CKata);
    // Menambahkan player
    AddPlayer(&ArrayPlayer, jumlahplayer);
    // Menampilkan salah satu nama orang di array player
    printf("Print nama player ke-: ");
    STARTKATA();
    int playerke = KataInt(CKata);
    PrintNamePlayer(ArrayPlayer(ArrayPlayer)[playerke-1]);
}