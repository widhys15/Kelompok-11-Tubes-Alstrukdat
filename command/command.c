#include "command.h"
#include "../array/array.c"
#include "../player/player.c"

void PrintLokasiPlayer(Map M, Player p)
/*
I.S. M sebuah Map yang terdefinisi
I.F. Menampilkan Map yang terdefinisi
*/
// KALO MAKE POINTER, YG ORIGINAL BAKAL BERUBAH
{
    int lokasi = Posisi(p);
    PrintNamePlayer(p);
    printf(": ");
    Petak((M).map[lokasi - 1]) = '*';
    for (int i = 0; i < (M).Neff; i++)
    {
        printf("%c", Petak((M).map[i]));
    }
    printf(" %d", lokasi);
}

void MAP(Map M, Players ps)
/*
I.S. M sebuah Map yang terdefinisi
I.F. Menampilkan Map yang terdefinisi
*/
// KALO MAKE POINTER, YG ORIGINAL BAKAL BERUBAH
{
    int total = JumlahPlayer(ps);
    for (int i = 0; i < total; i++)
    {
        PrintLokasiPlayer(M, ArrayPlayer(ps)[i]);
        puts("");
    }
}
char InfoPetak(Map M, int Petak)
{
    return Petak((M).map[Petak - 1]);
}
void INSPECT(Map M, int Petak)
/*
I.S. M sebuah Map yang terdefinisi
I.F. Mereturn nilai tp pada petak yang ditentukan
*/
{
    if (InfoPetak(M, Petak) == '#')
    {
        printf("Petak %d merupakan petak terlarang.", Petak);
    }
    else
    {
        int outTP = Tp((M).map[Petak - 1]);
        if (outTP != -1)
        {
            printf("Petak %d memiliki teleporter menuju %d.", Petak, outTP);
        }
        else
        {
            printf("Petak %d merupakan petak kosong", Petak);
        }
    }
}

void Teleport(Player *p, int currentPosition, Map M)
{
    int outTP = Tp((M).map[currentPosition - 1]);
    if (outTP == -1)
    {
        PrintNamePlayer(*p);
        printf(" tidak menemukan teleport.\n");
    }
    else
    {
        PrintNamePlayer(*p);
        printf(" menemukan teleport.\n");
        if (ImmuneTP(*p) == true)
        {
            printf("Apakah ");
            PrintNamePlayer(*p);
            printf(" ingin teleport (Y/N) ? ");
            STARTKATA();
            // ### CEK VALID INPUT START ###
            boolean valid = false;
            do
            {
                if ((CKata.TabKata[1] != 'N') && (CKata.TabKata[1] != 'Y'))
                {
                    puts("Jawab antara Y atau N");
                    printf(" ingin teleport (Y/N) ? ");
                    STARTKATA();
                }
                else
                {
                    valid = true;
                }
            } while (!valid);
            // ### CEK VALID INPUT END ###
            if (CKata.TabKata[1] == 'N')
            {
                PrintNamePlayer(*p);
                printf(" tidak teleport.\n");
                // Set buff teleport menjadi false karena telah digunakan
                ImmuneTP(*p) = false;
                puts("Buff imunitas teleport hilang.");
            }
            else if (CKata.TabKata[1] == 'Y')
            {
                // Pindah tempat
                Posisi(*p) = outTP;
                PrintNamePlayer(*p);
                printf(" teleport ke petak %d.\n", outTP);
            }
        }
        else if (ImmuneTP(*p) == false)
        {
            // Pindah tempat
            Posisi(*p) = outTP;
            PrintNamePlayer(*p);
            printf(" teleport ke petak %d.\n", outTP);
        }
    }
}

void ROLL(int minRoll, int maxRoll, int maxPetak, Player *p, Map M)
{
    if (BuffPengecil(*p) == true)
    {
        printf("\nMaxRoll sebelum dibuff menggunakan senter pengecil hoki %d", maxRoll);
        maxRoll = floor(maxRoll / 2);
        printf("MaxRoll sesudah dibuff menggunakan senter pengecil hoki %d", maxRoll);
    }
    else if (BuffPembesar(*p) == true)
    {
        printf("\nMinRoll sebelum dibuff menggunakan senter pembesar hoki %d\n", minRoll);
        minRoll = floor(maxRoll / 2);
        printf("MinRoll sesudah dibuff menggunakan senter pembesar hoki %d\n", minRoll);
    }

    srand(time(0));
    int num = (rand() % (maxRoll - minRoll + 1)) + minRoll;
    PrintNamePlayer(*p);
    printf(" mendapatkan angka %d.\n", num);
    int CPosisi = Posisi(*p);
    int forward = CPosisi + num;
    int backward = CPosisi - num;
    // Lokasi Player di tengah, Petak Maju dan Mundur adalah Valid
    if ((forward <= maxPetak) && (backward > 0))
    {
        // Dapat bergerak Maju dan Mundur
        if ((InfoPetak(M, forward) != '#') && (InfoPetak(M, backward) != '#'))
        {
            PrintNamePlayer(*p);
            printf(" dapat maju dan mundur.\n");
            printf("Ke mana ");
            PrintNamePlayer(*p);
            puts(" mau bergerak: ");
            printf("1.%d\n", forward);
            printf("2.%d\n", backward);
            printf("Masukkan pilihan: ");
            STARTKATA();
            int pilihan = KataInt(CKata);
            // ### CEK VALID INPUT START ###
            boolean valid = false;
            do
            {
                if ((pilihan < 1) || (pilihan > 2))
                {
                    puts("Pilih antar 1 atau 2");
                    printf("Masukkan pilihan: ");
                    STARTKATA();
                    pilihan = KataInt(CKata);
                }
                else
                {
                    valid = true;
                }
            } while (!valid);
            // ### CEK VALID INPUT END ###
            if (pilihan == 1)
            {
                PrintNamePlayer(*p);
                printf(" maju %d langkah.\n", forward);
                // Change currentPosition Player
                Posisi(*p) = forward;
                PrintNamePlayer(*p);
                printf(" berada di petak %d.\n", Posisi(*p));
                // printf("HARUSNYA NEXT MASUK KE FUNGSI TELEPORT\n");
                Teleport(p, Posisi(*p), M);
            }
            else if (pilihan == 2)
            {
                PrintNamePlayer(*p);
                printf(" mundur %d langkah.\n", backward);
                // Change currentPosition Player
                Posisi(*p) = backward;
                PrintNamePlayer(*p);
                printf(" berada di petak %d.\n", Posisi(*p));
                // printf("HARUSNYA NEXT MASUK KE FUNGSI TELEPORT\n");
                Teleport(p, Posisi(*p), M);
            }

        } // Dapat bergerak Maju
        else if ((InfoPetak(M, forward) != '#') && (InfoPetak(M, backward) == '#'))
        {
            PrintNamePlayer(*p);
            printf(" dapat maju.\n");
            PrintNamePlayer(*p);
            printf(" maju %d langkah.\n", forward);
            // Change currentPosition Player
            Posisi(*p) = forward;
            PrintNamePlayer(*p);
            printf(" berada di petak %d.\n", Posisi(*p));
            // printf("HARUSNYA NEXT MASUK KE FUNGSI TELEPORT\n");
            Teleport(p, Posisi(*p), M);
        }
        // Mundur
        else if ((InfoPetak(M, forward) == '#') && (InfoPetak(M, backward) != '#'))
        {

            PrintNamePlayer(*p);
            printf(" dapat mundur.\n");
            PrintNamePlayer(*p);
            printf(" mundur %d langkah.\n", backward);
            // Change currentPosition Player
            Posisi(*p) = backward;
            PrintNamePlayer(*p);
            printf(" berada di petak %d.\n", Posisi(*p));
            Teleport(p, Posisi(*p), M);
        }
        else if ((InfoPetak(M, forward) == '#') && (InfoPetak(M, backward) == '#'))
        {
            PrintNamePlayer(*p);
            printf(" tidak dapat bergerak.\n");
        }
    }
    else if ((forward <= maxPetak) && (backward <= 0))
    {
        if ((InfoPetak(M, forward) == '#'))
        {
            PrintNamePlayer(*p);
            printf(" tidak dapat bergerak.\n");
        }
        else
        {
            PrintNamePlayer(*p);
            printf(" dapat maju.\n");
            PrintNamePlayer(*p);
            printf(" maju %d langkah.\n", forward);
            // Change currentPosition Player
            Posisi(*p) = forward;
            PrintNamePlayer(*p);
            printf(" berada di petak %d.\n", Posisi(*p));
            // printf("HARUSNYA NEXT MASUK KE FUNGSI TELEPORT\n");
            Teleport(p, Posisi(*p), M);
        }
    }
    else if ((forward > maxPetak) && (backward > 0))
    {
        if ((InfoPetak(M, backward) == '#'))
        {
            PrintNamePlayer(*p);
            printf(" tidak dapat bergerak.\n");
        }
        else
        {
            PrintNamePlayer(*p);
            printf(" dapat mundur.\n");
            PrintNamePlayer(*p);
            printf(" mundur %d langkah.\n", backward);
            // Change currentPosition Player
            Posisi(*p) = backward;
            PrintNamePlayer(*p);
            printf(" berada di petak %d.\n", Posisi(*p));
            // printf("HARUSNYA NEXT MASUK KE FUNGSI TELEPORT\n");
            Teleport(p, Posisi(*p), M);
        }
    }
}

void Buff(Players p, int currentPlayer)
{
    printf("Kamu memiliki buff:\n");
    if (ImmuneTP(ArrayPlayer(p)[currentPlayer]) == true)
    {
        printf("Imunitas Teleport\n");
    }
    if (Cermin(ArrayPlayer(p)[currentPlayer]) == true)
    {
        printf("Cermin Pengganda\n");
    }
    if (BuffPembesar(ArrayPlayer(p)[currentPlayer]) == true)
    {
        printf("Senter Pembesar Hoki\n");
    }
    if (BuffPengecil(ArrayPlayer(p)[currentPlayer]) == true)
    {
        printf("Senter Pengecil Hoki\n");
    }
    if ((ImmuneTP(ArrayPlayer(p)[currentPlayer]) == false) && (Cermin(ArrayPlayer(p)[currentPlayer]) == false) && (BuffPembesar(ArrayPlayer(p)[currentPlayer]) == false) && (BuffPengecil(ArrayPlayer(p)[currentPlayer]) == false))
    {
        printf("Tidak ada Buff\n");
    }
}
// ### SKILL ###
void UseSkill(Players *p, int inputs, int currentPlayer)
{
    int info = PrintInfoKe(PlayerSkills(ArrayPlayer(*p)[currentPlayer]), inputs);
    if (info == 1)
    {
        (ImmuneTP(ArrayPlayer(*p)[currentPlayer])) = true;
        DeleteSkill(&(PlayerSkills(ArrayPlayer(*p)[currentPlayer])), inputs);
        // nyalain buff immunity teleport di adt player
        // delete elemen di skill
    }
    else if (info == 2)
    {
        if (NbElmt(PlayerSkills(ArrayPlayer(*p)[currentPlayer])) < 10 && (Cermin(ArrayPlayer(*p)[currentPlayer]) == false))
        {
            Cermin(ArrayPlayer(*p)[currentPlayer]) = true;
            RandomSkill(&(PlayerSkills(ArrayPlayer(*p)[currentPlayer])), 3);
            RandomSkill(&(PlayerSkills(ArrayPlayer(*p)[currentPlayer])), 5);
            DeleteSkill(&(PlayerSkills(ArrayPlayer(*p)[currentPlayer])), inputs);
        }
        else
        {
            printf("\nMaaf Skill Cermin Pengganda tidak dapat dipakai.\n");
        }
        // ngecek elemennya ada berapa sekarang (< 9, +2 =10)
        // delete elemen sekarang
        // random ke listskill 2 kali
    }
    else if (info == 3 || info == 4)
    {
        if (BuffPengecil(ArrayPlayer(*p)[currentPlayer]) == true || BuffPembesar(ArrayPlayer(*p)[currentPlayer]) == true)
        {
            printf("\nMaaf skill Senter Pembesar Hoki tidak dapat dipakai karena Senter Pengecil Hoki aktif\n");
        }
        else
        {
            BuffPembesar(ArrayPlayer(*p)[currentPlayer]) = true;
            DeleteSkill(&(PlayerSkills(ArrayPlayer(*p)[currentPlayer])), inputs);
        }
        // ngecek boolean di adt player senter pengecil hoki nyala ato ngga
        // kalo nyala keluarin prompt gabisa pake skill
        // kalo ga nyala pake boolean senter pembesar hoki nyala
        // udh gitu delete skill
    }
    else if (info == 5 || info == 6)
    {
        if (BuffPembesar(ArrayPlayer(*p)[currentPlayer]) == true || BuffPengecil(ArrayPlayer(*p)[currentPlayer]) == true)
        {
            printf("\nMaaf skill Senter Pengecil Hoki tidak dapat dipakai karena Senter Pembesar Hoki aktif\n");
        }
        else
        {
            BuffPengecil(ArrayPlayer(*p)[currentPlayer]) = true;
            DeleteSkill(&(PlayerSkills(ArrayPlayer(*p)[currentPlayer])), inputs);
        }
        // ngecek boolean di adt player senter pembesar hoki nyala ato ngga
        // kalo nyala keluarin prompt gabisa pake skill
        // kalo ga nyala pake boolean senter pengecil hoki nyala
        // udh gitu delete skill
    }
    else if (info == 7)
    {
        int chosenPlayer;
        if (currentPlayer == JumlahPlayer(*p) - 1)
        {
            chosenPlayer = 0;
        }
        else
        {
            chosenPlayer = currentPlayer + 1;
        }
        int temp = Posisi(ArrayPlayer(*p)[currentPlayer]);
        Posisi(ArrayPlayer(*p)[currentPlayer]) = Posisi(ArrayPlayer(*p)[chosenPlayer]);
        Posisi(ArrayPlayer(*p)[chosenPlayer]) = temp;
        DeleteSkill(&(PlayerSkills(ArrayPlayer(*p)[currentPlayer])), inputs);
        //belum beres
        // bikin variabel posisi sekarang
        // bikin temp
        // masukin variabel posisi sekarang ke temp
        // masukin variabel posisi sekarang dari player selanjutnya
        // masukin variabel posisi player selanjutnya dari temp
    }
    else
    {
        DeleteSkill(&(PlayerSkills(ArrayPlayer(*p)[currentPlayer])), inputs);
    }
}
void skill(Players *p, int currentPlayer)
{
    /*
    (PlayerSkills(ArrayPlayer(*p)[currentPlayer]))
    {ITU BUAT NGAMBIL SKILL DI PLAYER TERTENTU}
    */
    int inputs;
    PrintMenuSkill((PlayerSkills(ArrayPlayer(*p)[currentPlayer])));
    printf("\nMasukkan skill: ");
    STARTKATA();
    inputs = KataInt(CKata);
    boolean done = false;
    while (inputs != 0)
    {
        if (inputs > 0)
        {
            puts("");
            PrintNamePlayer((ArrayPlayer(*p)[currentPlayer]));
            printf(" memakai skill ");
            PrintSkillKe((PlayerSkills(ArrayPlayer(*p)[currentPlayer])), inputs);
            printf("\n");
            UseSkill(p, inputs, currentPlayer);
            // DeleteSkill(&(PlayerSkills(*p)), inputs);
        }
        else if (inputs < 0)
        {
            inputs = inputs * (-1);
            puts("");
            PrintNamePlayer((ArrayPlayer(*p)[currentPlayer]));
            printf(" membuang skill ");
            PrintSkillKe((PlayerSkills(ArrayPlayer(*p)[currentPlayer])), inputs);
            printf("\n");
            DeleteSkill(&(PlayerSkills(ArrayPlayer(*p)[currentPlayer])), inputs);
        }
        // STARTKATA();
        // inputs = KataInt(CKata);
        PrintMenuSkill((PlayerSkills(ArrayPlayer(*p)[currentPlayer])));
        printf("\nMasukkan skill: ");
        STARTKATA();
        inputs = KataInt(CKata);
    };
    if (inputs == 0)
    {
        puts("");
        PrintNamePlayer((ArrayPlayer(*p)[currentPlayer]));
        printf(" keluar dari command SKILL\n");
    }
}
void oldSkill(Player *p)
{
    int inputs;

    PrintMenuSkill((PlayerSkills(*p)));
    printf("\nMasukkan skill: ");
    STARTKATA();
    inputs = KataInt(CKata);
    boolean done = false;
    while (inputs != 0)
    {
        if (inputs > 0)
        {
            puts("");
            PrintNamePlayer(*p);
            printf(" memakai skill ");
            PrintSkillKe((PlayerSkills(*p)), inputs);
            printf("\n");
            // InsBuff(&(PlayerBuffs(*p)), inputs);
            DeleteSkill(&(PlayerSkills(*p)), inputs);
        }
        else if (inputs < 0)
        {
            inputs = inputs * (-1);
            puts("");
            PrintNamePlayer(*p);
            printf(" membuang skill ");
            PrintSkillKe((PlayerSkills(*p)), inputs);
            printf("\n");
            DeleteSkill(&(PlayerSkills(*p)), inputs);
        }
        // STARTKATA();
        // inputs = KataInt(CKata);
        PrintMenuSkill((PlayerSkills(*p)));
        printf("\nMasukkan skill: ");
        STARTKATA();
        inputs = KataInt(CKata);
    };
    if (inputs == 0)
    {
        puts("");
        PrintNamePlayer(*p);
        printf(" keluar dari command SKILL\n");
    }
}

// void CopyArrayPlayer(Players copy, Players *paste)
// {
//     (*paste) = copy;
// }

// int test2(List L, int x)
// {
// }
// void test(Players *p, int inputs, int currentPlayer)
// {
//     test2(PlayerSkills((ArrayPlayer(*p)[currentPlayer])), 1);

//     PlayerSkills((ArrayPlayer(*p)[currentPlayer]));
//     Posisi((ArrayPlayer(*p)[currentPlayer]));
// }