/* File         : mesin_kata.c */
/* Deskripsi    : ADT Mesinkata */

#ifndef __MESINKATA_H__
#define __MESINKATA_H__

#include "../boolean.h"
#include "../ADT_Mesinkar/mesin_kar.h"

#define NMax 500
#define BLANK ' '
#define MARK '\n'

typedef struct
{
   char TabKata[NMax + 1]; /* container penyimpan kata, indeks yang dipakai [1..NMax] */
   int Length;
} Kata;

/* State Mesin Kata */
extern boolean EndKata;
extern Kata CKata;

void C_STARTKATA(char *c);
void C_ADVKATA();
void C_SalinKata();
void C_IgnoreBlank();
void IgnoreBlank();
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */

void SalinKata();
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

void STARTKATA();
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void ADVKATA();
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.
   Proses : Akuisisi kata menggunakan procedure SalinKata */
Kata AskCommand();
boolean STRCOMP(Kata k1, char k2[100]);
boolean IsNumber(Kata k);
int KataInt(Kata k);
void KataMap(Kata k, char importMap[100]);
void KataPlayer(Kata k, char namaPlayer[20]);
void printKata(Kata kata);
void KataChar(Kata k, char c[100]);
#endif