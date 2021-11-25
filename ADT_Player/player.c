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

void PrintRanking(Players ps)
/* I.S. ps terdefinisi */
/* F.S. Menampilkan Ranking pemain yang menang */
{
    int totalplayers = JumlahPlayer(ps);
    int position[totalplayers];
    int p[totalplayers];
    int temp1, temp2;
    int i,j;
    // Deklarasi posisi pemain ke dalam array
    for (i = 0; i < totalplayers; i++)
    {
        position[i] = Posisi(ArrayPlayer(ps)[i]);
        p[i] = i;
    }
    // Sorting posisi player dari terbesar ke terkecil
    for (i = 0; i < totalplayers; i++)
    {
        for (j = 0; j < totalplayers-1; j++)
        {
            if (position[j] <= position[j+1])
            {
                temp1 = position[j];
                temp2 = p[j];
                position[j] = position[j+1];
                p[j] = p[j+1];
                position[j+1] = temp1;
                p[j+1] = temp2;
            }
            
        }
            
    }
    for (i = 0; i < totalplayers; i++)
    {
        printf("%d. ", i+1);
        PrintNamePlayer(ArrayPlayer(ps)[p[i]]);
        puts("");
    }
    
    
    
}