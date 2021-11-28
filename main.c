#include <stdio.h>
#include <unistd.h>
#include "command/command.h"
#include "command/command.c"
#include "ART/art.c"

int main()
{
    int menu;
BMENU:
    MainMenu();
    puts("");
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
        // ### Cek command Undo Allowed or Not START ###

        boolean UndoAllowed = VotingUndo(ArrPlayer);
        puts("\n|------------------- HASIL VOTING --------------------|");
        if (UndoAllowed == true)
        {
            puts("Command UNDO dapat digunakan");
        }
        else
        {
            puts("Command UNDO tidak dapat digunakan");
        }
        boolean UndoAgain;
        // ### Cek command Undo Allowed or Not END ###
        Map lvl;

        // VERSI MINTA DARI INPUT USER START
        printf("\nMasukkan config yang ingin dipakai: ");
        char conf[100];
        scanf("%[^\n]%*c", conf);
        boolean filefound = false;
        do
        {
            if (access(conf, F_OK) != -1)
            {
                filefound = true;
                break;
            }
            else
            {
                printf("file configuration is not found\n");
                printf("\nMasukkan config yang ingin dipakai: ");
                scanf("%[^\n]%*c", conf);
            }
        } while (!filefound);

        // STARTKATA();
        // KataChar(CKata, conf);
        // VERSI MINTA DARI INPUT USER END
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
        while (!EndGame)
        {
            if (currentPlayer == JumlahPlayer(ArrPlayer))
            {
                Push(&Round, ArrPlayer);
                RondeKe++;
                currentPlayer = 0;
            }
        STARTGAME:
            printf("\nRonde Ke-%d\n", RondeKe);
            puts("|--------- POSISI PLAYER SEKARANG ---------|");
            MAP(lvl, ArrPlayer);
            printf("|------------------------------------------|\n");
            //### Display Giliran Player Start ###
            printf("\nGiliran kamu ");
            PrintNamePlayer(ArrayPlayer(ArrPlayer)[currentPlayer]);
            //### Display Giliran Player End ###
            RandomSkill(&(PlayerSkills(ArrayPlayer(ArrPlayer)[currentPlayer])), currentPlayer);
            puts("");
            Command();
            puts("");
            printf("-> ");
            STARTKATA();
            // ### command YANG BISA SAAT FASE ROLL BLOM DIJALANKAN START ###
            while (!STRCOMP(CKata, "ROLL"))
            {
                if (STRCOMP(CKata, "INSPECT"))
                {
                    printf("\nMasukkan petak: ");
                    STARTKATA();
                    int petak = KataInt(CKata);
                    // CEK VALIDASI INPUT INSPECT START
                    valid = false;
                    do
                    {
                        if ((petak <= 0) || (petak > maxPetak))
                        {
                            printf("Masukkan nilai petak antara 1 sampai %d\n", maxPetak);
                            printf("Masukkan petak: ");
                            STARTKATA();
                            petak = KataInt(CKata);
                        }
                        else
                        {
                            valid = true;
                        }
                    } while (!valid);
                    // CEK VALIDASI INPUT INSPECT END
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
                else if (STRCOMP(CKata, "UNDO") && UndoAllowed)
                {
                    RondeKe = InfoRonde(Round) + 1;
                    UNDO(&Round, &ArrPlayer);
                    currentPlayer = 0;
                    printf("\nRonde Ke-%d\n", RondeKe);
                    puts("|--------- POSISI PLAYER SEKARANG ---------|");
                    MAP(lvl, ArrPlayer);
                    printf("|------------------------------------------|\n");
                    UndoAgain = true;
                    while (UndoAgain)
                    {
                        printf("\nApakah Anda ingin melakukan UNDO lagi? (Y/N): ");
                        STARTKATA();
                        // ### CEK VALID INPUT START ###
                        boolean valid = false;
                        do
                        {
                            if ((CKata.TabKata[1] != 'N') && (CKata.TabKata[1] != 'Y'))
                            {
                                puts("Jawab antara Y atau N");
                                printf("Apakah Anda ingin melakukan UNDO lagi? (Y/N): ");
                                STARTKATA();
                            }
                            else
                            {
                                valid = true;
                            }
                        } while (!valid);
                        // ### CEK VALID INPUT END ###
                        if (CKata.TabKata[1] == 'Y')
                        {
                            // Pindah tempat
                            RondeKe = InfoRonde(Round) + 1;
                            UNDO(&Round, &ArrPlayer);
                            currentPlayer = 0;
                            printf("\nRonde Ke-%d\n", RondeKe);
                            puts("|--------- POSISI PLAYER SEKARANG ---------|");
                            MAP(lvl, ArrPlayer);
                            printf("|------------------------------------------|\n");
                        }
                        else if (CKata.TabKata[1] == 'N')
                        {
                            UndoAgain = false;
                            break;
                        }
                    }
                    goto STARTGAME;
                }
                else if (STRCOMP(CKata, "UNDO") && !UndoAllowed)
                {
                    puts("Dari hasil voting, UNDO tidak dapat digunakan");
                }
                else if (STRCOMP(CKata, "ENDTURN"))
                {
                    puts("Command ENDTURN dilakukan setelah ROLL!!!");
                }
                Command();
                puts("");
                printf("-> ");
                STARTKATA();
            }
            // ### command YANG BISA SAAT FASE ROLL BLOM DIJALANKAN END ###
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
                Command();
                puts("");
                printf("-> ");
                STARTKATA();
            }
            // ### command YANG BISA SAAT FASE ROLL SUDAH DIJALANKAN START ###
            while (!STRCOMP(CKata, "ENDTURN"))
            {
                if (STRCOMP(CKata, "INSPECT"))
                {
                    printf("\nMasukkan petak: ");
                    STARTKATA();
                    int petak = KataInt(CKata);
                    // CEK VALIDASI INPUT INSPECT START
                    valid = false;
                    do
                    {
                        if ((petak <= 0) || (petak > maxPetak))
                        {
                            printf("Masukkan nilai petak antara 1 sampai %d\n", maxPetak);
                            printf("Masukkan petak: ");
                            STARTKATA();
                            petak = KataInt(CKata);
                        }
                        else
                        {
                            valid = true;
                        }
                    } while (!valid);
                    // CEK VALIDASI INPUT INSPECT END
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
                else if (STRCOMP(CKata, "UNDO") && UndoAllowed)
                {
                    RondeKe = InfoRonde(Round) + 1;
                    UNDO(&Round, &ArrPlayer);
                    currentPlayer = 0;
                    printf("\nRonde Ke-%d\n", RondeKe);
                    puts("|--------- POSISI PLAYER SEKARANG ---------|");
                    MAP(lvl, ArrPlayer);
                    printf("|------------------------------------------|\n");
                    UndoAgain = true;
                    while (UndoAgain)
                    {
                        printf("\nApakah Anda ingin melakukan UNDO lagi? (Y/N): ");
                        STARTKATA();
                        // ### CEK VALID INPUT START ###
                        boolean valid = false;
                        do
                        {
                            if ((CKata.TabKata[1] != 'N') && (CKata.TabKata[1] != 'Y'))
                            {
                                puts("Jawab antara Y atau N");
                                printf("Apakah Anda ingin melakukan UNDO lagi? (Y/N): ");
                                STARTKATA();
                            }
                            else
                            {
                                valid = true;
                            }
                        } while (!valid);
                        // ### CEK VALID INPUT END ###
                        if (CKata.TabKata[1] == 'Y')
                        {
                            // Pindah tempat
                            RondeKe = InfoRonde(Round) + 1;
                            UNDO(&Round, &ArrPlayer);
                            currentPlayer = 0;
                            printf("\nRonde Ke-%d\n", RondeKe);
                            puts("|--------- POSISI PLAYER SEKARANG ---------|");
                            MAP(lvl, ArrPlayer);
                            printf("|------------------------------------------|\n");
                        }
                        else if (CKata.TabKata[1] == 'N')
                        {
                            UndoAgain = false;
                            break;
                        }
                    }
                    goto STARTGAME;
                }
                else if (STRCOMP(CKata, "UNDO") && !UndoAllowed)
                {
                    puts("Dari hasil voting, UNDO tidak dapat digunakan");
                }
                else if (STRCOMP(CKata, "ROLL") || STRCOMP(CKata, "SKILL"))
                {
                    puts("Command ROLL dan SKILL tidak bisa digunakan setelah ROLL!!!");
                }
                Command();
                puts("");
                printf("-> ");

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
            // ### command YANG BISA SAAT FASE ROLL SUDAH DIJALANKAN END ###
        }
        if (EndGame == true)
        {
            printf("SELAMAT ");
            PrintNamePlayer(ArrayPlayer(ArrPlayer)[currentPlayer]);
            printf(" MEMENANGKAN GAME MOBILE LEGEND ULAR TANGGA ^.^\n");
            puts("");
            printf("Peringkat Player: \n");
            PrintRanking(ArrPlayer);
            puts("");
            goto BMENU;
        }
    } // END IF
    else
    {
        puts("TERIMA KASIH MAU MENCOBA GAME INI ^.^");
    }
}
