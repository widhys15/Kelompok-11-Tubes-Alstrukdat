#include "player.h"
#include <stdio.h>
#include "../mesinkata/mesin_kata.c"
#include "../mesinkar/mesin_kar.c"
#include "../skill/listlinier.c"
void CreateEmptyArrayPlayer(Players *p)
{
    JumlahPlayer(*p) = 0;
}
void AddPlayer(Players *p, int jumlahPlayer)
{
    JumlahPlayer(*p) = jumlahPlayer;
    for (int i = 0; i < jumlahPlayer; i++)
    {
        CreatePlayer(&(ArrayPlayer(*p)[i]), i + 1);
    }
}
void CreatePlayer(Player *p, int playerKe)
{
    printf("Nama Player %d: ", playerKe);
    STARTKATA();
    NameLength(*p) = CKata.Length;
    KataPlayer(CKata, Name(*p));
    Posisi(*p) = 1;
    First((PlayerSkills(*p))) = Nil;
    //BUFF
    ImmuneTP(*p) = false;
    BuffPembesar(*p) = false;
    BuffPengecil(*p) = false;
    Cermin(*p) = false;
    // ImmuneTP(*p) = true;
    // BuffPembesar(*p) = true;
    // BuffPengecil(*p) = true;
    // Cermin(*p) = true;
}
void PrintNamePlayer(Player p)
{
    int length = NameLength(p);
    for (int i = 0; i < length; i++)
    {
        printf("%c", (Name(p))[i]);
    }
}