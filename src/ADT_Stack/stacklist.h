/* File         : stacklist.h */
/* Deskripsi    : ADT Stack dari definisi stacklist */

#ifndef _STACKLIST_H
#define _STACKLIST_H

#include "../boolean.h"
#include <stdlib.h>
#include "../ADT_Player/player.h"

/* Konstanta */

/* Deklarasi infotype */
typedef int infotype;

/* Stack dengan representasi berkait dengan pointer */
typedef struct tElmtStack *addressStack;
typedef struct tElmtStack
{
    Players ArrP;
    addressStack NextStack;
} ElmtStack;

/* Type stack dengan ciri TOP : */
typedef struct
{
    addressStack TOP;   /* alamat TOP: elemen puncak */
    infotype infoRonde; // Buat Info Ronde
} Stack;

/* Selektor */
#define Top(S) (S).TOP
#define InfoRonde(S) (S).infoRonde
#define ArrayPlayerStack(S) (S).TOP->ArrP
#define NextStack(P) (P)->NextStack
#define ArrayPlayerElmtStack(P) (P)->ArrP

/* Prototype manajemen memori */

void CopyArrayPlayer(Players copy, Players *paste);
/* I.S. players terdefinisi */
/* F.S. Data players terdefinisi ke dalam list baru */

void CopyPasteListSkill(List copy, List *paste);
/* I.S. list skill terdefinisi */
/* F.S. list skill terdefinisi ke dalam list baru */

void DealokasiSkillPlayer(Players *ps);
/* I.S. players terdefinisi */
/* F.S. Skill dari players terdealokasi */

void AlokasiStack(addressStack *P, Players ps);
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */

void DealokasiStack(addressStack P);
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */

/* ********* PROTOTYPE REPRESENTASI LOJIK STACK ***************/
boolean IsEmptyStack(Stack S);
/* Mengirim true jika Stack kosong: TOP(S) = Nil */

void CreateEmptyStack(Stack *S);
/* I.S. sembarang */
/* F.S. Membuat sebuah stack S yang kosong */

void Push(Stack *S, Players ps);
/* Menambahkan X sebagai elemen Stack S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TOP yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */

void Pop(Stack *S, Players *ps);
/* Menghapus X dari Stack S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, */
/*      elemen TOP yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */

#endif