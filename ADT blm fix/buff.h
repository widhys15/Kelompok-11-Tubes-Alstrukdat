#ifndef BUFF_H
#define BUFF_H

#include <stdio.h>

typedef struct buff
{
    int idbuff [10];
    char* nama;
    char* deskripsi;
} BUFF;

#define idbuff(B) (B).idbuff
#define nama(B) (B).nama
#define deskripsi(B) (B).deskripsi

void CreateEmptyBuff(BUFF *B);
/* Membuat buff kosong. */
/* I.S. B sembarang */
/* F.S. B menjadi buff kosong */

void IsiBuff(BUFF *B, int x, char* nama, char* desc);
/* Mengisi buff. */
/* I.S. B sudah terdefinisi */
/* F.S. B terisi oleh buff yang dimasukkan */

void PrintBuff(BUFF B, int x);
/* Menampilkan buff. */
/* I.S. B sudah terisi */
/* F.S. Menampilkan buff ke-x */

#endif
