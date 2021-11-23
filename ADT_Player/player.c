#include "player.h"
#include <stdio.h>
#include "../ADT_Mesinkata/mesin_kata.c"
#include "../ADT_Mesinkar/mesin_kar.c"
#include "../ADT_Skill/listlinier.c"

void CreateEmptyArrayPlayer(Players *p)
/* I.S. sembarang             */
/* F.S. Terbentuk array player kosong */
{
    JumlahPlayer(*p) = 0;
}

void AddPlayer(Players *p, int jumlahPlayer)
/* I.S. p terdefinisi */
/* F.S. Menambahkan player sejumlah input ke dalam array players */
{
    JumlahPlayer(*p) = jumlahPlayer;
    for (int i = 0; i < jumlahPlayer; i++)
    {
        CreatePlayer(&(ArrayPlayer(*p)[i]), i + 1);
    }
}

void CreatePlayer(Player *p, int playerKe)
/* I.S. p terdefinisi */
/* F.S. Mengisi data-data seperti nama, posisi, dan list skill ke dalam player */
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
/* I.S. p terdefinisi */
/* F.S. Menampilkan nama player */
{
    int length = NameLength(p);
    for (int i = 0; i < length; i++)
    {
        printf("%c", (Name(p))[i]);
    }
}