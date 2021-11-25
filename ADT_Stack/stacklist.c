#include <stdio.h>
#include "stacklist.h"
#include "../ADT_Player/player.c"
/* Prototype manajemen memori */
void CopyArrayPlayer(Players copy, Players *paste)
/* I.S. players terdefinisi */
/* F.S. Data players terdefinisi ke dalam list baru */
{
    (*paste) = copy;
}

void CopyPasteListSkill(List copy, List *paste)
/* I.S. list skill terdefinisi */
/* F.S. list skill terdefinisi ke dalam list baru */
{
    List TmpSkill;
    CreateEmpty(&TmpSkill);
    int tmp = NbElmt(copy);
    for (int i = 1; i <= tmp; i++)
    {
        int infoSkill = PrintInfoKe(copy, i);
        // MASUKIN DATA SKILL KE SkillPlayer1
        address P = Alokasi(infoSkill);
        if (P != Nil)
        {
            if (NbElmt(TmpSkill) < 10)
            {

                InsertLast(&TmpSkill, P);
            }
            else
            {
                printf("Skill sudah penuh\n");
            }
        }
    }
    (*paste) = TmpSkill;
}

void DealokasiSkillPlayer(Players *ps)
/* I.S. players terdefinisi */
/* F.S. Skill dari players terdealokasi */
{
    int TotalPlayer = JumlahPlayer(*ps);
    for (int i = 0; i < TotalPlayer; i++)
    {

        int jumlahSkill = NbElmt(PlayerSkills(ArrayPlayer(*ps)[i]));
        for (int j = 1; j <= jumlahSkill; j++)
        {
            DeleteSkill(&(PlayerSkills(ArrayPlayer(*ps)[i])), 1);
        }
    }
}

void AlokasiStack(addressStack *P, Players ps)
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
{
    *P = (ElmtStack *)malloc(sizeof(ElmtStack));
    if ((*P) != Nil)
    {
        ArrayPlayerElmtStack(*P) = ps;
        int TotalPlayer = JumlahPlayer(ps);
        for (int i = 0; i < TotalPlayer; i++)
        {

            CopyPasteListSkill(PlayerSkills(ArrayPlayer(ps)[i]), &(PlayerSkills(ArrayPlayer(ArrayPlayerElmtStack(*P))[i])));
        }
        NextStack(*P) = Nil;
    }
}

void DealokasiStack(addressStack P)
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
{
    NextStack(P) = Nil;
    free(P);
}

/* ********* PROTOTYPE REPRESENTASI LOJIK STACK ***************/
boolean IsEmptyStack(Stack S)
/* Mengirim true jika Stack kosong: TOP(S) = Nil */
{
    return (Top(S) == Nil);
}

void CreateEmptyStack(Stack *S)
/* I.S. sembarang */
/* F.S. Membuat sebuah stack S yang kosong */
{
    Top(*S) = Nil;
    InfoRonde(*S) = -1;
}

void Push(Stack *S, Players ps)
/* Menambahkan X sebagai elemen Stack S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TOP yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */
{
    addressStack p;
    AlokasiStack(&p, ps);
    if (p != Nil)
    {
        InfoRonde(*S) = InfoRonde(*S) + 1;
        NextStack(p) = Top(*S);
        Top(*S) = p;
    }
}

void Pop(Stack *S, Players *ps)
/* Menghapus X dari Stack S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, */
/*      elemen TOP yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */
{
    if (InfoRonde(*S) > 0)
    {
        // Dealokasi ps ListSkill yang akan diganti START
        DealokasiSkillPlayer(ps);
        // Dealokasi ps ListSkill yang akan diganti END
        CopyArrayPlayer(ArrayPlayerStack(*S), ps);
        // Copy Skill START
        int TotalPlayer = JumlahPlayer(*ps);
        for (int i = 0; i < TotalPlayer; i++)
        {
            PlayerSkills(ArrayPlayer(ArrayPlayerStack(*S))[i]); // Akses List Skill dari Stack
            PlayerSkills((ArrayPlayer(*ps)[i]));                // Akses List Skill dari Players
            CopyPasteListSkill(PlayerSkills(ArrayPlayer(ArrayPlayerStack(*S))[i]), &(PlayerSkills((ArrayPlayer(*ps)[i]))));
        }
        // Copy Skill END
        // Dealokasi S ListSkill yang akan diganti START
        DealokasiSkillPlayer(&ArrayPlayerStack(*S));
        addressStack p;
        p = Top(*S);
        InfoRonde(*S) = InfoRonde(*S) - 1;
        Top(*S) = NextStack(Top(*S));
        DealokasiStack(p);
    }
    else
    {
        // Dealokasi ps ListSkill yang akan diganti START
        DealokasiSkillPlayer(ps);
        // Dealokasi ps ListSkill yang akan diganti END
        CopyArrayPlayer(ArrayPlayerStack(*S), ps);
        // Copy Skill START
        int TotalPlayer = JumlahPlayer(*ps);
        for (int i = 0; i < TotalPlayer; i++)
        {
            PlayerSkills(ArrayPlayer(ArrayPlayerStack(*S))[i]); // Akses List Skill dari Stack
            PlayerSkills((ArrayPlayer(*ps)[i]));                // Akses List Skill dari Players
            CopyPasteListSkill(PlayerSkills(ArrayPlayer(ArrayPlayerStack(*S))[i]), &(PlayerSkills((ArrayPlayer(*ps)[i]))));
        }
        // Copy Skill END
    }
}