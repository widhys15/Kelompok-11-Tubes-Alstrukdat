#include <stdio.h>
#include <unistd.h>
// #include "array/array.h"
// #include "array/array.c"
// Include mesinkata dan mesin kar
// #include "mesinkata/mesin_kata.h"
// #include "mesinkata/mesin_kata.c"
// #include "mesinkar/mesin_kar.h"
// #include "mesinkar/mesin_kar.c"
// Include Player
// #include "player/player.h"
// #include "player/player.c"
// #include "ADT_Skill/listlinier.c"
// #include "ADT_Skill/listlinier.h"
#include "command/command.h"
#include "command/command.c"

int main()
{
    int menu;
    printf("WELCOME TO MOBILE LEGENDS ULAR TANGGA!!!\n");
    puts("1.New Game");
    puts("2.Exit");
    printf("-> ");
    STARTKATA();
    // Validasi input
    boolean valid = false;
    menu = KataInt(CKata);
    do
    {
        if ((menu < 1) || (menu > 2))
        {
            puts("Input tidak valid");
            printf("-> ");
            STARTKATA();
            menu = KataInt(CKata);
        }
        else
        {
            valid = true;
        }
    } while (!valid);

    if (menu == 1)
    {
        // ### SET PLAYER ###
        Players ArrPlayer;
        CreateEmptyArrayPlayer(&ArrPlayer);
        printf("\nBerapa Player: ");
        STARTKATA();
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
        Map lvl;
        char conf[20] = "config.txt";
        char importMap[100];

        // Import MaxPetak start
        C_STARTKATA(conf);
        int maxPetak = KataInt(CKata);
        // Import MaxPetak end

        // ImportMap start
        C_ADVKATA();
        KataMap(CKata, importMap);
        CreateMap(&lvl, maxPetak, importMap);
        // ImportMap end

        // Import MaxRoll start
        C_ADVKATA();
        int maxRoll = KataInt(CKata);
        int minRoll = 1;
        // Import MaxRoll emd
        // Import setTeleport start
        C_ADVKATA();
        int MaxTP = KataInt(CKata);
        for (int i = 0; i < MaxTP; i++)
        {
            C_ADVKATA();
            int in = KataInt(CKata);
            C_ADVKATA();
            int out = KataInt(CKata);
            SetTeleport(&lvl, in, out);
        }
        // Import setTeleport end

        // Decalare Stack for Undo
        Stack Round;
        CreateEmptyStack(&Round);
        Push(&Round, ArrPlayer); // Untuk Round 0 atau awal game

        // ### TEST GAME ###
        boolean EndGame = false;
        int currentPlayer = 0;
        int RondeKe = 1;
        int PlayerUsedUndo;
        while (!EndGame)
        {
            if (currentPlayer == JumlahPlayer(ArrPlayer))
            {
                puts("### NEXNYA FUNGSI PUSH ###");
                Push(&Round, ArrPlayer);
                RondeKe++;
                currentPlayer = 0;
            }
        Z:
            printf("\nRonde Ke-%d\n", RondeKe);
            puts("|--------- POSISI PLAYER SEKARANG ---------|");
            MAP(lvl, ArrPlayer);
            printf("|------------------------------------------|\n");

            //### Display Giliran Player Start ###
            printf("\nGiliran kamu ");
            PrintNamePlayer(ArrayPlayer(ArrPlayer)[currentPlayer]);
            //### Display Giliran Player End ###
            InjectSkill(&(PlayerSkills(ArrayPlayer(ArrPlayer)[currentPlayer])), 25);
            InjectSkill(&(PlayerSkills(ArrayPlayer(ArrPlayer)[currentPlayer])), 8);
            RandomSkill(&(PlayerSkills(ArrayPlayer(ArrPlayer)[currentPlayer])), currentPlayer);
            puts("");
            printf("\nMasukkan Command: ");
            STARTKATA();

            // ### COMMEND YANG BISA SAAT FASE ROLL BLOM DIJALANKAN START ###
            while (!STRCOMP(CKata, "ROLL"))
            {
                if (STRCOMP(CKata, "INSPECT"))
                {
                    printf("\nMasukkan petak: ");
                    STARTKATA();
                    int petak = KataInt(CKata);
                    INSPECT(lvl, petak);
                    puts("");
                }
                else if (STRCOMP(CKata, "SKILL"))
                {
                    PlayerSkills((ArrayPlayer(ArrPlayer)[currentPlayer]));
                    skill(&ArrPlayer, currentPlayer, minRoll, maxRoll, lvl, maxPetak);
                    // oldSkill(&ArrayPlayer(ArrPlayer)[currentPlayer]);
                }
                else if (STRCOMP(CKata, "MAP"))
                {
                    puts("");
                    puts("|--------- POSISI PLAYER SEKARANG ---------|");
                    MAP(lvl, ArrPlayer);
                    printf("|----------------------------------------|\n");
                }
                else if (STRCOMP(CKata, "BUFF"))
                {
                    Buff(ArrPlayer, currentPlayer);
                }
                else if (STRCOMP(CKata, "UNDO"))
                {
                    puts("INI FUNGSI UNDO");
                    PlayerUsedUndo = currentPlayer;
                    RondeKe = InfoRonde(Round) + 1;
                    UNDO(&Round, &ArrPlayer);
                    currentPlayer = 0;
                    goto Z;
                }
                else if (STRCOMP(CKata, "TMP"))
                {
                    puts("TEST LIST SKILL");
                    printf("INDEX DI TOP = %d", InfoRonde(Round));
                    PrintMenuSkill((PlayerSkills(ArrayPlayer(ArrayPlayerStack(Round))[0])));
                }
                printf("\nMasukkan Command: ");
                CKata.TabKata[1] = '.';
                STARTKATA();
                printKata(CKata);
            }
            // ### COMMEND YANG BISA SAAT FASE ROLL BLOM DIJALANKAN END ###

            if (STRCOMP(CKata, "ROLL")) // Kelar Roll atau kelar turn
            {
                ROLL(minRoll, maxRoll, maxPetak, &(ArrayPlayer(ArrPlayer)[currentPlayer]), lvl);
                puts("");
                // ### CEK APAKAH ADA PLAYER YANG SUDAH FINIS START ###
                if (Posisi(ArrayPlayer(ArrPlayer)[currentPlayer]) == maxPetak)
                {
                    EndGame = true;
                    break;
                }
                // ### CEK APAKAH ADA PLAYER YANG SUDAH FINIS END ###
                printf("\nMasukkan Command: ");
                STARTKATA();
            }

            // ### COMMEND YANG BISA SAAT FASE ROLL SUDAH DIJALANKAN START ###
            while (!STRCOMP(CKata, "ENDTURN"))
            {
                if (STRCOMP(CKata, "INSPECT"))
                {
                    printf("\nMasukkan petak: ");
                    STARTKATA();
                    int petak = KataInt(CKata);
                    INSPECT(lvl, petak);
                    puts("");
                }
                else if (STRCOMP(CKata, "MAP"))
                {
                    puts("|--------- POSISI PLAYER SEKARANG ---------|");
                    MAP(lvl, ArrPlayer);
                    printf("|----------------------------------------|\n");
                }
                else if (STRCOMP(CKata, "BUFF"))
                {
                    Buff(ArrPlayer, currentPlayer);
                }
                else if (STRCOMP(CKata, "UNDO"))
                {
                    puts("INI FUNGSI UNDO");
                    PlayerUsedUndo = currentPlayer;
                    RondeKe = InfoRonde(Round) + 1;
                    UNDO(&Round, &ArrPlayer);
                    currentPlayer = 0;
                    goto Z;
                }
                else if (STRCOMP(CKata, "TMP"))
                {
                    puts("TEST LIST SKILL");
                    printf("INDEX DI TOP = %d", InfoRonde(Round));
                    PrintMenuSkill((PlayerSkills(ArrayPlayer(ArrayPlayerStack(Round))[0])));
                }
                printf("\nMasukkan Command: ");
                STARTKATA();
            }
            if (STRCOMP(CKata, "ENDTURN"))
            {
                BuffPembesar((ArrayPlayer(ArrPlayer)[currentPlayer])) = false;
                BuffPengecil((ArrayPlayer(ArrPlayer)[currentPlayer])) = false;
                if (Cermin((ArrayPlayer(ArrPlayer)[currentPlayer])) == true)
                {
                    Cermin((ArrayPlayer(ArrPlayer)[currentPlayer])) = false;
                }
                currentPlayer++;
            }
            // ### COMMEND YANG BISA SAAT FASE ROLL SUDAH DIJALANKAN END ###
        }
        if (EndGame == true)
        {
            printf("SELAMAT ");
            PrintNamePlayer(ArrayPlayer(ArrPlayer)[currentPlayer]);
            printf(" MEMENANGKAN GAME MOBILE LEGEND ULAR TANGGA ^.^\n");
        }
        // ### TEST MAP ###
        // printf("Masukkan Command: ");
        // STARTKATA();
        // if (STRCOMP(CKata, "MAP"))
        // {
        //     MAP(lvl, ArrPlayer);
        // }

        // ### TEST INSPECT ####
        // printf("Masukkan Command: ");
        // STARTKATA();
        // if (STRCOMP(CKata, "INSPECT"))
        // {
        //     printf("Masukkan petak: ");
        //     STARTKATA();
        //     int petak = KataInt(CKata);
        //     INSPECT(lvl, petak);
        // }

        // ### TEST ROLL ###
        // printf("Masukkan Command: ");
        // STARTKATA();
        // if (STRCOMP(CKata, "ROLL"))
        // {
        //     ROLL(1, maxRoll, maxPetak, &Player1, lvl);
        // }

        // ### TEST LIST SKILLS ###
        //     (PlayerSkills(ArrayPlayer(ArrPlayer)[1])); // Alamat list player
        //     First((PlayerSkills(ArrayPlayer(ArrPlayer)[0]))) == Nil;
        //     RandomSkill(&(PlayerSkills(ArrayPlayer(ArrPlayer)[0])), 2);
        //     if (First((PlayerSkills(ArrayPlayer(ArrPlayer)[1]))) == Nil)
        //     {
        //         printf("Skill ente kosong gblk\n");
        //     }
        //     else
        //     {
        //         printf("ADA ISINYA KNTL\n");
        //     }
        //     PrintSkill((PlayerSkills(ArrayPlayer(ArrPlayer)[0])));
        //     PrintSkill((PlayerSkills(ArrayPlayer(ArrPlayer)[1])));

        // ### TEST COPY DATA PLAYERS ###
        // puts("### DATA RONDE KE 1 ###");
        // PrintMenuSkill(PlayerSkills(PR1));
        // puts("Print Buff: \n");
        // if (ImmuneTP(PR1) == true)
        // {
        //     printf("Imunitas Teleport\n");
        // }
        // if (Cermin(PR1) == true)
        // {
        //     printf("Cermin Pengganda\n");
        // }
        // if (BuffPembesar(PR1) == true)
        // {
        //     printf("Senter Pembesar Hoki\n");
        // }
        // if (BuffPengecil(PR1) == true)
        // {
        //     printf("Senter Pengecil Hoki\n");
        // }
        // // if (ImmuneTP(ArrayPlayer(PR1)[0]))
        // // {
        // //     printf("ADA IMMUNE TP DI AKHIR RONDE 1\n");
        // // }
        // // else
        // // {
        // //     printf("GK ADA IMMUNE DI AKHIR RONDE 1 \n");
        // // }
        // puts("### DATA RONDE KE 2 ###");
        // PrintMenuSkill((PlayerSkills(ArrayPlayer(ArrPlayer)[0])));
        // Buff(ArrPlayer, 0);
        // // if (ImmuneTP(ArrayPlayer(ArrPlayer)[0]))
        // // {
        // //     printf("ADA IMMUNE TP\n");
        // // }
        // // else
        // // {
        // //     printf("GK ADA IMMUNE\n");
        // // }

    } // END IF
    else
    {
        puts("TERIMA KASIH MAU MENCOBA GAME INI ^.^");
    }
}
