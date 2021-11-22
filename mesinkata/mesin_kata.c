#include <stdio.h>
#include <string.h>
#include "mesin_kata.h"

boolean EndKata;
Kata CKata;

/*###### Config Start ######*/
void C_STARTKATA(char *c)
{
    C_START(c);
    IgnoreBlank();
    C_SalinKata();
}
void C_ADVKATA()
{
    while ((CC == BLANK) || (CC == MARK))
    {
        C_ADV();
    }
    C_SalinKata();
}
void C_SalinKata()
{
    int i = 1;
    while ((CC != MARK) && (CC != BLANK))
    {
        CKata.TabKata[i] = CC;
        C_ADV();
        i++;
    }
    CKata.Length = i - 1;
}
void C_IgnoreBlank()
{
    while ((CC == BLANK) || (CC == MARK))
    {
        C_ADV();
    }
}
/*###### Config End ######*/

void IgnoreBlank()
{
    while ((CC == BLANK) && (CC != MARK))
    {
        ADV();
    }
}

void SalinKata()
{
    int i = 1;
    while ((CC != MARK) && (CC != BLANK))
    {
        CKata.TabKata[i] = CC;
        ADV();
        i++;
    }
    CKata.Length = i - 1;
}

void STARTKATA()
{
    START();
    IgnoreBlank();
    if (CC == MARK)
    {
        EndKata = true;
    }
    else
    {
        EndKata = false;
        SalinKata();
    }
}

void ADVKATA()
{
    IgnoreBlank();
    if (CC == MARK)
    {
        EndKata = true;
    }
    else
    {
        SalinKata();
    }
}
Kata AskCommand()
{
    STARTKATA();
    while (!EndKata)
    {
        ADVKATA();
    }
    return CKata;
}

boolean STRCOMP(Kata k1, char k2[100])
{
    int i = 1;
    int lengthk2 = strlen(k2);
    boolean sama = true;
    // (k1.Length == lengthk2) &&
    while ((sama) && (i < lengthk2))
    {
        // printf("MASUK KE CEK KATA\n");
        // printf("K1 CKata = %c\n", k1.TabKata[i]);
        // printf("K2 CKata = %c\n", k2[i - 1]);
        if (k1.TabKata[i] == k2[i - 1])
        {

            sama = true;
        }
        else
        {
            // printf("SALAH\n");
            sama = false;
            break;
        }
        i++;
    }
    return sama;
}

boolean IsNumber(Kata k)
{
    int i;
    if (CKata.TabKata[1] == '-')
    {
        i = 2;
    }
    else
    {
        i = 1;
    }
    boolean number = true;
    while (number && i <= k.Length)
    {
        switch (k.TabKata[i])
        {
        case '0':
            break;
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            break;
        case '6':
            break;
        case '7':
            break;
        case '8':
            break;
        case '9':
            break;
        default:
            number = false;
        };
        i++;
    }
    return number;
}
int KataInt(Kata k)
{
    int i;
    if (CKata.TabKata[1] == '-')
    {
        i = 2;
    }
    else
    {
        i = 1;
    }
    int val = 0;

    while (i <= k.Length)
    {
        val = val * 10;
        switch (k.TabKata[i])
        {
        case '0':
            val += 0;
            break;
        case '1':
            val += 1;
            break;
        case '2':
            val += 2;
            break;
        case '3':
            val += 3;
            break;
        case '4':
            val += 4;
            break;
        case '5':
            val += 5;
            break;
        case '6':
            val += 6;
            break;
        case '7':
            val += 7;
            break;
        case '8':
            val += 8;
            break;
        case '9':
            val += 9;
            break;
        };
        i++;
    }
    if (CKata.TabKata[1] == '-')
    {
        val = val * (-1);
    }
    return val;
}
void KataMap(Kata k, char importMap[100])
{
    for (int i = 1; i <= k.Length; i++)
    {
        importMap[i - 1] = k.TabKata[i];
    }
}
void KataPlayer(Kata k, char namaPlayer[20])
{
    for (int i = 1; i <= k.Length; i++)
    {
        namaPlayer[i - 1] = k.TabKata[i];
    }
}
void printKata(Kata kata)
{
    for (int i = 1; i <= kata.Length; i++)
    {
        printf("%c", kata.TabKata[i]);
    }
    puts("");
}