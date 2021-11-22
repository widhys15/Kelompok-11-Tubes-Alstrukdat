#include "listlinier.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

address AdrMax(List L)
{
    address p = First(L);
    address max = First(L);
    while (p != Nil)
    {
        if (Info(p) > Info(max))
        {
            max = p;
        }
        p = Next(p);
    }
    return max;
}

infotype Min(List L)
{
    address p = First(L);
    address min = First(L);
    while (p != Nil)
    {
        if (Info(p) < Info(min))
        {
            min = p;
        }
        p = Next(p);
    }
    return Info(min);
}

address AdrMin(List L)
{
    address p = First(L);
    address min = First(L);
    while (p != Nil)
    {
        if (Info(p) < Info(min))
        {
            min = p;
        }
        p = Next(p);
    }
    return min;
}

float Average(List L)
{
    address p = First(L);
    int count = 0;
    float total, avg = 0;
    while (p != Nil)
    {
        total = total + Info(p);
        count = count + 1;
        p = Next(p);
    }
    avg = total / count;
    return (avg);
}

void InversList(List *L)
{
    address p, last, temp;
    p = First(*L);
    temp = Nil;
    while (p != Nil)
    {
        last = p;
        p = Next(p);
        Next(last) = temp;
        temp = last;
    }
    First(*L) = last;
};

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmpty(List L)
/* Mengirim true jika list kosong */
{
    return (First(L) == Nil);
};

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty(List *L)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
    First(*L) = Nil;
};

/****************** Manajemen Memori ******************/
address Alokasi(infotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
    ElmtList *E = (ElmtList *)malloc(sizeof(ElmtList));

    if (E != Nil)
    {
        Info(E) = X;
        Next(E) = Nil;
        return E;
    }
    else
    {
        return Nil;
    }
}
void Dealokasi(address *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
    free(*P);
};

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search(List L, infotype X)
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
    boolean cek = false;
    address P = First(L);

    if (!IsEmpty(L))
    {
        while (P != Nil && !cek)
        {
            if (Info(P) == X)
            {
                cek = true;
            }
            else
            {
                P = Next(P);
            }
        }
    }
    return P;
};

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst(List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
    address P = Alokasi(X);
    if (P != Nil)
    {
        InsertFirst(L, P);
    }
};
void InsVLast(List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    address P = Alokasi(X);
    if (P != Nil)
    {
        InsertLast(L, P);
    }
};

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst(List *L, infotype *X)
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
    address P;
    DelFirst(L, &P);
    *X = Info(P);
    Dealokasi(&P);
};
void DelVLast(List *L, infotype *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
    address P;
    DelLast(L, &P);
    *X = Info(P);
    Dealokasi(&P);
};

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst(List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
    if (P != Nil)
    {
        Next(P) = First(*L);
        First(*L) = P;
    }
}
void InsertAfter(List *L, address P, address Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
    if (P != Nil)
    {
        Next(P) = Next(Prec);
        Next(Prec) = P;
    }
}
void InsertLast(List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
    if (IsEmpty(*L))
    {
        InsertFirst(L, P);
    }
    else
    {
        address prevp = First(*L);
        while (Next(prevp) != Nil)
        {
            prevp = Next(prevp);
        }
        InsertAfter(L, P, prevp);
    }
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst(List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
    address p = First(*L);
    if (Next(p) == Nil)
    {
        CreateEmpty(L);
    }
    else
    {
        First(*L) = Next(p);
    }
    *P = p;
};

void DeleteSkill(List *L, infotype X)
/* I.S. Sembarang */
/* F.S. Elemen ke-X dari list dihapus dan didealokasi */
/* Jika tidak ada elemen list dengan list ke-X maka list tetap dan memberikan peringatan */
/* List mungkin menjadi kosong karena penghapusan */
{
    address P = First(*L);
    address Prev = Nil;
    if (X == 1)
    {
        DelFirst(L, &P);
    }
    else
    {
        for (int i = 1; i < X; i++)
        {
            Prev = P;
            P = Next(P);
        }
        Next(Prev) = Next(P);
        Dealokasi(&P);
    }
};

void DelP(List *L, infotype X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
    address P = Search(*L, X);
    if (P != Nil)
    {
        address prevp = First(*L);
        if (prevp == P)
        {
            DelFirst(L, &P);
        }
        else
        {
            while (Next(prevp) != P)
            {
                prevp = Next(prevp);
            }
            DelAfter(L, &P, prevp);
        }
    }
    Dealokasi(&P);
};
void DelLast(List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
{
    *P = First(*L);
    if (Next(*P) == Nil)
    {
        CreateEmpty(L);
    }
    else
    {
        address prevp = *P;
        while (Next(Next(prevp)) != Nil)
        {
            prevp = Next(prevp);
        }
        DelAfter(L, P, prevp);
    }
};
void DelAfter(List *L, address *Pdel, address Prec)
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
    *Pdel = Next(Prec);
    if (*Pdel != Nil)
    {
        Next(Prec) = Next(Next(Prec));
    }
};

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo(List L)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
    printf("[");
    if (!IsEmpty(L))
    {
        address P = First(L);
        while (P != Nil)
        {
            printf("%d", Info(P));
            P = Next(P);
            if (P != Nil)
            {
                printf(",");
            }
        }
    }
    printf("]");
};

void PrintSkill(List L)
{
    if (!IsEmpty(L))
    {
        int i = 1;
        printf("\nKamu memiliki skill: \n");
        address P = First(L);
        while (P != Nil)
        {
            printf("%d. ", i);
            if (Info(P) == 1)
            {
                printf("Pintu Ga Ke Mana Mana\n");
            }
            else if (Info(P) == 2)
            {
                printf("Cermin Pengganda\n");
            }
            else if (Info(P) == 3 || Info(P) == 4)
            {
                printf("Senter Pembesar Hoki\n");
            }
            else if (Info(P) == 5 || Info(P) == 6)
            {
                printf("Senter Pengecil Hoki\n");
            }
            else if (Info(P) == 7)
            {
                printf("Mesin Penukar Posisi\n");
            }
            else
            {
                printf("Teknologi Gagal\n");
            }
            P = Next(P);
            i = i + 1;
        }
    }
    else
    {
        printf("\nSkill kosong\n");
    }
};

int NbElmt(List L)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
    int count = 0;
    if (!IsEmpty(L))
    {
        address P = First(L);
        while (Next(P) != Nil)
        {
            count = count + 1;
            P = Next(P);
        }
        count = count + 1;
    }
    return count;
}

/*** Prekondisi untuk Max/Min/rata-rata : List tidak kosong ***/
infotype Max(List L)
/* Mengirimkan nilai Info(P) yang maksimum */
{
    address P = First(L);
    infotype max = Info(P);
    while (Next(P) != Nil)
    {
        P = Next(P);
        if (Info(P) > max)
        {
            max = Info(P);
        }
    }
    return max;
}

/****************** PROSES TERHADAP LIST ******************/
void Konkat1(List *L1, List *L2, List *L3)
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */
{
    CreateEmpty(L3);
    if (!IsEmpty(*L1))
    {
        address P = First(*L1);
        First(*L3) = P;
        while (Next(P) != Nil)
        {
            P = Next(P);
        }
        Next(P) = First(*L2);
    }
    else
    {
        First(*L3) = First(*L2);
    }
    CreateEmpty(L1);
    CreateEmpty(L2);
};

int random(int x)
{
    int randoms;
    time_t t;
    srand((unsigned)(time(&t)));
    for (int i = 1; i < 10; i++)
    {
        randoms = rand() % 10;
    }
    randoms = (randoms + x) % 10;
    return randoms;
}
void IsPembesarHoki(List L, int X)
{
    address P = First(L);
}
void PrintSkillKe(List L, int X)
{
    address P = First(L);
    if (X == 1)
    {
        if (Info(P) == 1)
        {
            printf("Pintu Ga Ke Mana Mana\n");
        }
        else if (Info(P) == 2)
        {
            printf("Cermin Pengganda\n");
        }
        else if (Info(P) == 3 || Info(P) == 4)
        {
            printf("Senter Pembesar Hoki\n");
        }
        else if (Info(P) == 5 || Info(P) == 6)
        {
            printf("Senter Pengecil Hoki\n");
        }
        else if (Info(P) == 7)
        {
            printf("Mesin Penukar Posisi\n");
        }
        else
        {
            printf("Teknologi Gagal\n");
        }
    }
    else
    {
        for (int i = 1; i < X; i++)
        {
            P = Next(P);
        }
        if (Info(P) == 1)
        {
            printf("Pintu Ga Ke Mana Mana\n");
        }
        else if (Info(P) == 2)
        {
            printf("Cermin Pengganda\n");
        }
        else if (Info(P) == 3 || Info(P) == 4)
        {
            printf("Senter Pembesar Hoki\n");
        }
        else if (Info(P) == 5 || Info(P) == 6)
        {
            printf("Senter Pengecil Hoki\n");
        }
        else if (Info(P) == 7)
        {
            printf("Mesin Penukar Posisi\n");
        }
        else
        {
            printf("Teknologi Gagal\n");
        }
    }
};

void PrintMenuSkill(List L)
{
    PrintSkill(L);
    printf("\nTekan 0 untuk keluar. Masukkan bilangan negatif untuk membuang skill.\n");
}

// void skill(List *L)
// {
//     int inputs;
//     PrintMenuSkill(*L);
//     printf("\nMasukkan skill: ");
//     scanf("%d", &inputs);
//     if (inputs > 0)
//     {
//         printf("\nPlayer memakai skill ");
//         PrintSkillKe(*L, inputs);
//         printf("\n");
//         DeleteSkill(L, inputs);
//     }
//     else if (inputs < 0)
//     {
//         inputs = inputs * (-1);
//         printf("\nPlayer membuang skill ");
//         PrintSkillKe(*L, inputs);
//         printf("\n");
//         DeleteSkill(L, inputs);
//     }
//     else
//     {
//         printf("\nPlayer keluar dari menu Skill\n");
//         // Masuk main menu command
//         printf("Masukkan Command: ");
//         STARTKATA();
//     }
// }

void RandomSkill(List *L, int X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    int r;
    r = random(X);
    address P = Alokasi(r);
    if (P != Nil)
    {
        if (NbElmt(*L) < 10)
        {

            InsertLast(L, P);
        }
        else
        {
            printf("Skill sudah penuh\n");
        }
    }
};

int PrintInfoKe(List L, int X)
{
    address P = First(L);
    if (X == 1)
    {
        if (Info(P) == 1)
        {
            return 1;
        }
        else if (Info(P) == 2)
        {
            return 2;
        }
        else if (Info(P) == 3)
        {
            return 3;
        }
        else if (Info(P) == 4)
        {
            return 4;
        }
        else if (Info(P) == 5)
        {
            return 5;
        }
        else if (Info(P) == 6)
        {
            return 65;
        }
        else if (Info(P) == 7)
        {
            return 7;
        }
    }
    else
    {
        for (int i = 1; i < X; i++)
        {
            P = Next(P);
        }
        if (Info(P) == 1)
        {
            return 1;
        }
        else if (Info(P) == 2)
        {
            return 2;
        }
        else if (Info(P) == 3)
        {
            return 3;
        }
        else if (Info(P) == 4)
        {
            return 4;
        }
        else if (Info(P) == 5)
        {
            return 5;
        }
        else if (Info(P) == 6)
        {
            return 65;
        }
        else if (Info(P) == 7)
        {
            return 7;
        }
    }
};

void InjectSkill(List *L, int infoSkill)
{
    address P = Alokasi(infoSkill);
    if (P != Nil)
    {
        if (NbElmt(*L) < 10)
        {

            InsertLast(L, P);
        }
        else
        {
            printf("Skill sudah penuh\n");
        }
    }
}