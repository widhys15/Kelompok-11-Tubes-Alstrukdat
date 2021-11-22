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

        // ### TEST GAME ###
        List SkillPlayer1;
        boolean EndGame = false;
        int currentPlayer = 0;
        int RondeKe = 1;
        Players PR1;
        while (!EndGame)
        {
            if (currentPlayer == JumlahPlayer(ArrPlayer))
            {
                RondeKe++;
                currentPlayer = 0;
            }
            // ### TEST COPY PASTE DATA START ###
            if (RondeKe == 1)
            {
                printf("COPY DATA DI AKHIR RONDE KE 1\n");
                CreateEmpty(&SkillPlayer1);
                int tmp = NbElmt((PlayerSkills(ArrayPlayer(ArrPlayer)[0])));
                for (int i = 1; i <= tmp; i++)
                {
                    int infoSkill = PrintInfoKe((PlayerSkills(ArrayPlayer(ArrPlayer)[0])), i);
                    // MASUKIN DATA SKILL KE SkillPlayer1
                    address P = Alokasi(infoSkill);
                    if (P != Nil)
                    {
                        if (NbElmt(SkillPlayer1) < 10)
                        {

                            InsertLast(&SkillPlayer1, P);
                        }
                        else
                        {
                            printf("Skill sudah penuh\n");
                        }
                    }
                }
            }
            if (RondeKe == 3)
            {
                (PlayerSkills(ArrayPlayer(ArrPlayer)[1])) = SkillPlayer1;
                printf("\nENDGAME\n");
                EndGame = true;
                break;
            }
            // ### TEST COPY PASTE DATA END ###
            printf("\nRonde Ke-%d\n", RondeKe);
            puts("|--------- POSISI PLAYER SEKARANG ---------|");
            MAP(lvl, ArrPlayer);
            printf("|----------------------------------------|\n");

            //### Display Giliran Player Start ###
            printf("\nGiliran kamu ");
            PrintNamePlayer(ArrayPlayer(ArrPlayer)[currentPlayer]);
            //### Display Giliran Player End ###
            // InjectSkill(&(PlayerSkills(ArrayPlayer(ArrPlayer)[currentPlayer])), 1);
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
                    skill(&ArrPlayer, currentPlayer);
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
                printf("\nMasukkan Command: ");
                STARTKATA();
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
        puts("### DATA RONDE KE 1 ###");
        PrintMenuSkill(SkillPlayer1);
        // if (ImmuneTP(ArrayPlayer(PR1)[0]))
        // {
        //     printf("ADA IMMUNE TP DI AKHIR RONDE 1\n");
        // }
        // else
        // {
        //     printf("GK ADA IMMUNE DI AKHIR RONDE 1 \n");
        // }
        puts("### DATA RONDE KE 2 ###");
        PrintMenuSkill((PlayerSkills(ArrayPlayer(ArrPlayer)[1])));
        // if (ImmuneTP(ArrayPlayer(ArrPlayer)[0]))
        // {
        //     printf("ADA IMMUNE TP\n");
        // }
        // else
        // {
        //     printf("GK ADA IMMUNE\n");
        // }

    } // END IF
    else
    {
        puts("TERIMA KASIH MAU MENCOBA GAME INI ^.^");
    }
}
