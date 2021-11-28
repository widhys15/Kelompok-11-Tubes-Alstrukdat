#include "mesin_kata.h"
#include <stdio.h>
#include "mesin_kata.c"
#include "../ADT_Mesinkar/mesin_kar.h"
#include "../ADT_Mesinkar/mesin_kar.c"
int main()
{
    // ### Cek Fungsi STRCOMP ###
    puts("### Cek Fungsi STRCOMP ###");
    puts("STR yangg dicompare adalah INSPECT");
    STARTKATA();
    if (STRCOMP(CKata, "INSPECT"))
    {
        printf("STR SAMA\n");
    }
    else
    {
        printf("STR BEDA\n");
    }
    // ### Cek Fungsi IsNumber ###
    puts("\n### Cek Fungsi IsNumber ###");
    for (int i = 0; i < 3; i++)
    {
        printf("Masukkan kata = ");
        STARTKATA();
        printf("char = ");
        printKata(CKata);
        if (IsNumber(CKata))
        {
            printf("Ini Angka\n");
        }
        else
        {
            printf("Ini bukan Angka\n");
        }
    }
    // ### Cek Fungsi KataInt ###
    puts("\n### Cek Fungsi KataInt ###");
    printf("Masukkan Angka = ");
    STARTKATA();
    int angka = KataInt(CKata);
    printf("Setelah diconvert angkanya = %d\n", angka);

    // ### Cek Fungsi KataMap ###
    puts("\n### Cek Fungsi KataMap ###");
    char map[100];
    int maxPetak = 5;
    printf("Masukkan Map dengan maxPetak 5:\n");
    printf("-> ");
    STARTKATA();
    KataMap(CKata, map);
    puts("Hasil Convert:");
    for (int i = 0; i < maxPetak; i++)
    {
        printf("%c", map[i]);
    }
    puts("### Cek Fungsi Selesai ###");

    /*
    NOTE:
    1. Untuk fungsi sisanya sudah digunakan di percobaan fungsi
    2. Untuk fungsi KataPlayer mirip-mirip dengan KataMap, yang membeakan
       hanya jumlah charnya saja.
    */
}
