#include "buff.h"
#include <stdio.h>

void CreateEmptyBuff(BUFF *B)
/* Membuat buff kosong. */
/* I.S. B sembarang */
/* F.S. B menjadi buff kosong */
{
    idbuff(*B)[0] = 0;
    nama(*B) = "tes";
    deskripsi(*B) = "tes";
}

void IsiBuff(BUFF *B, int x, char* nama, char* desc)
/* Mengisi buff. */
/* I.S. B sudah terdefinisi */
/* F.S. B terisi oleh buff yang dimasukkan */
{
    idbuff(*B)[x] = x;
    nama(*B) = nama;
    deskripsi(*B)= desc;
}

void PrintBuff(BUFF B, int x)
/* Menampilkan buff. */
/* I.S. B sudah terisi */
/* F.S. Menampilkan buff ke-x */
{
    printf("Nomor Buff : %d\n", idbuff(B));
    printf("Nama : %c\n", nama(B));
    printf("Deskripsi : %c\n", deskripsi(B)); 
}