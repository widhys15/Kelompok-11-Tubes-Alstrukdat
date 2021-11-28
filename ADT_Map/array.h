/* File         : array.h */
/* Deskripsi    : ADT Map dari array */

#ifndef ARRAY_H
#define ARRAY_H
#include "../boolean.h"

#define MaxPetak 500

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
/* I.S. M Sembarang */
/* F.S. Tebentuk Map dengan Neff sama dengan PPetak dan tiap tp bernilai -1 */

void PrintMap(Map *M);
/* I.S. M sebuah Map yang terdefinisi */
/* F.S. Menampilkan Map yang terdefinisi */

void SetTeleport(Map *M, int In, int Out);
/* I.S. M sebuah Map terdefinisi */
/* F.S. Mengset lokasi In dan Out teleport pada petak */

#endif