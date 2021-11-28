#include <stdio.h>
#include "stacklist.h"
#include "stacklist.c"

int main()
{
    Stack Round;
    CreateEmptyStack(&Round);
    // ### Set Players ###
    Players ArrPlayer;
    CreateEmptyArrayPlayer(&ArrPlayer);
    printf("\nBerapa Player: ");
    STARTKATA();
    boolean valid = false;
    int jumlahPlayer = KataInt(CKata);
    // Validasi input jumlah player
    valid = false;
    do
    {
        if ((jumlahPlayer <= 1) || (jumlahPlayer > 4))
        {
            puts("Minimum Player 2 dan Maximum Player 4");
            printf("Berapa Player: ");

            STARTKATA();
            jumlahPlayer = KataInt(CKata);
        }
        else
        {
            valid = true;
        }
    } while (!valid);
    puts("");
    AddPlayer(&ArrPlayer, jumlahPlayer);

    Push(&Round, ArrPlayer);
    for (int i = 0; i < jumlahPlayer; i++)
    {
        printf("Menu skill Player ke %d\n", i + 1);
        PrintMenuSkill((PlayerSkills(ArrayPlayer(ArrPlayer)[i])));
        puts("");
    }
    // ### Penambahan Skill ###
    for (int i = 0; i < jumlahPlayer; i++)
    {
        RandomSkill(&(PlayerSkills(ArrayPlayer(ArrPlayer)[i])), i);
    }
    for (int i = 0; i < jumlahPlayer; i++)
    {
        printf("Menu skill Player ke %d\n", i + 1);
        PrintMenuSkill((PlayerSkills(ArrayPlayer(ArrPlayer)[i])));
        puts("");
    }
    puts("### KETIKA RONDE 1 BERAKHIR ###");
    puts("MELAKUKAN PUSH");
    Push(&Round, ArrPlayer);

    puts("### Melakukan input Skill kembali ###");
    for (int i = 0; i < jumlahPlayer; i++)
    {
        RandomSkill(&(PlayerSkills(ArrayPlayer(ArrPlayer)[i])), i);
    }
    for (int i = 0; i < jumlahPlayer; i++)
    {
        printf("Menu skill Player ke %d\n", i + 1);
        PrintMenuSkill((PlayerSkills(ArrayPlayer(ArrPlayer)[i])));
        puts("");
    }
    puts("### KETIKA RONDE 2 BERAKHIR ###");
    puts("MELAKUKAN PUSH");
    Push(&Round, ArrPlayer);

    printf("InfoRonde pada Stack %d\n", InfoRonde(Round));
    for (int i = 0; i < jumlahPlayer; i++)
    {
        printf("Menu skill Player ke %d\n", i + 1);
        PrintMenuSkill((PlayerSkills(ArrayPlayer(ArrPlayer)[i])));
        puts("");
    }
    puts("### Melakukan UNDO ###");
    Pop(&Round, &ArrPlayer);
    printf("InfoRonde pada Stack %d\n", InfoRonde(Round));
    for (int i = 0; i < jumlahPlayer; i++)
    {
        printf("Menu skill Player ke %d\n", i + 1);
        PrintMenuSkill((PlayerSkills(ArrayPlayer(ArrPlayer)[i])));
        puts("");
    }
    puts("### Melakukan UNDO ###");
    Pop(&Round, &ArrPlayer);
    printf("InfoRonde pada Stack %d\n", InfoRonde(Round));
    for (int i = 0; i < jumlahPlayer; i++)
    {
        printf("Menu skill Player ke %d\n", i + 1);
        PrintMenuSkill((PlayerSkills(ArrayPlayer(ArrPlayer)[i])));
        puts("");
    }
    puts("### Melakukan UNDO ###");
    Pop(&Round, &ArrPlayer);
    printf("InfoRonde pada Stack %d\n", InfoRonde(Round));
    for (int i = 0; i < jumlahPlayer; i++)
    {
        printf("Menu skill Player ke %d\n", i + 1);
        PrintMenuSkill((PlayerSkills(ArrayPlayer(ArrPlayer)[i])));
        puts("");
    }
}