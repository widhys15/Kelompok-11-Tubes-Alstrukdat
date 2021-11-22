#include <stdio.h>
#include <stdlib.h>
#include "array.h"

void CreateMap(Map *M, int PPetak, char importMap[100])
/* 
I.S. M Sembarang
I.F. Tebentuk Map dengan Neff sama dengan PPetak dan 
tiap tp bernilai -1
*/
{
    (*M).Neff = PPetak;
    for (int i = 0; i < PPetak; i++)
    {
        Petak((*M).map[i]) = importMap[i];
        Tp((*M).map[i]) = -1;
    }
}

void PrintMap(Map *M)
/*
I.S. M sebuah Map yang terdefinisi
I.F. Menampilkan Map yang terdefinisi
*/
{
    for (int i = 0; i < (*M).Neff; i++)
    {
        printf("%c", Petak((*M).map[i]));
    }
}
// void PrintLokasiPlayer(Map M, int lokasi)
// /*
// I.S. M sebuah Map yang terdefinisi
// I.F. Menampilkan Map yang terdefinisi
// */
// // KALO MAKE POINTER, YG ORIGINAL BAKAL BERUBAH
// {
//     Petak((M).map[lokasi - 1]) = '*';
//     for (int i = 0; i < (M).Neff; i++)
//     {
//         printf("%c", Petak((M).map[i]));
//     }
// }

void SetTeleport(Map *M, int In, int Out)
/*
I.S. M sebuah Map terdefinisi
I.F. Mengset lokasi In dan Out teleport pada petak
*/
{
    Tp((*M).map[In - 1]) = Out;
}