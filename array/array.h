#ifndef ARRAY_H
#define ARRAY_H
#include "../boolean.h"

#define MaxPetak 100

typedef struct
{
    char petak; // Jenis petak, apakah kosong atau dilarang
    int tp;     /* Arah teleport kemana, kalo gk ada isinya -1 */
} info_petak;
typedef struct
{
    info_petak map[MaxPetak];
    int Neff; // Panjang Petak
} Map;

/* Selector */
#define Petak(P) (P).petak
#define Tp(P) (P).tp

void CreateMap(Map *M, int PPetak, char *importMap);
/* 
I.S. M Sembarang
I.F. Tebentuk Map dengan Neff sama dengan PPetak dan 
tiap tp bernilai -1
*/
void PrintMap(Map *M);
/*
I.S. M sebuah Map yang terdefinisi
I.F. Menampilkan Map yang terdefinisi
*/
// void PrintLokasiPlayer(Map M, int lokasi);

void SetTeleport(Map *M, int In, int Out);
/*
I.S. M sebuah Map terdefinisi
I.F. Mengset lokasi In dan Out teleport pada petak
*/
#endif