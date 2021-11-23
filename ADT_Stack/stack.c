/*
NIM : 18220096
Nama : Aufa Fauqi Ardhiqi
Tanggal : 28/9/2021
Topik Praktikum : Queue dan Stack
Deskripsi : Implemntasikan stack.h 
*/
#include <stdio.h>
#include "stack.h"
#include "../ADT_Player/player.c"

void CreateEmptyStack(Stack *S)
{
    Top(*S) = NilStack;
}

boolean IsEmptyStack(Stack S)
{
    return (Top(S) == NilStack);
}
boolean IsFullStack(Stack S)
{
    return (Top(S) == MaxEl);
}
void CopyArrayPlayer(Players copy, Players *paste)
{
    (*paste) = copy;
}
//  if (RondeKe == 1)
//                 {
//                     printf("COPY DATA DI AKHIR RONDE KE 1\n");
//                     CopyArrayPlayer(ArrayPlayer(ArrPlayer)[0], &PR1);
//                     CreateEmpty(&SkillPlayer1);
//                     int tmp = NbElmt((PlayerSkills(ArrayPlayer(ArrPlayer)[0])));
//                     for (int i = 1; i <= tmp; i++)
//                     {
//                         int infoSkill = PrintInfoKe((PlayerSkills(ArrayPlayer(ArrPlayer)[0])), i);
//                         // MASUKIN DATA SKILL KE SkillPlayer1
//                         address P = Alokasi(infoSkill);
//                         if (P != Nil)
//                         {
//                             if (NbElmt(SkillPlayer1) < 10)
//                             {

//                                 InsertLast(&SkillPlayer1, P);
//                             }
//                             else
//                             {
//                                 printf("Skill sudah penuh\n");
//                             }
//                         }
//                     }
//                     (PlayerSkills(PR1)) = SkillPlayer1;
//                 }

void Push(Stack *S, Players ps)
{
    Top(*S) += 1;
    ArrPlayerStack(*S) = ps;
    // ArrayPlayer(ArrPlayerStack(*S))[0] ## INI AKSES Playeke dari Stack
    // Ngatur List Skill START
    List TmpSkill;
    int TotalPlayer = JumlahPlayer(ArrPlayerStack(*S));
    for (int i = 0; i < TotalPlayer; i++)
    {
        CreateEmpty(&TmpSkill);
        int tmp = NbElmt((PlayerSkills(ArrayPlayer(ArrPlayerStack(*S))[i])));
        for (int j = 1; j <= tmp; j++)
        {
            int infoSkill = PrintInfoKe((PlayerSkills(ArrayPlayer(ArrPlayerStack(*S))[i])), j);
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
        PlayerSkills(ArrayPlayer(ArrPlayerStack(*S))[i]) = TmpSkill;
    }
}
void Pop(Stack *S, Players *ps)
{
    if (Top(*S) > 0)
    {
        CopyArrayPlayer(ArrPlayerStack(*S), ps);
        Top(*S) -= 1;
    }
    else
    {
        CopyArrayPlayer(ArrPlayerStack(*S), ps);
    }
}