#include "command.h"
#include "../ADT_Map/array.c"
// #include "../ADT_Player/player.c"
#include "../ADT_Stack/stack.c"

void PrintLokasiPlayer(Map M, Player p)
/* I.S. Player dan Map terdefinisi */
/* F.S. Menampilkan lokasi player dari map yang terdefinisi */
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
/* I.S. Player dan map terdefinisi */
/* F.S. Menampilkan Map yang terdefinisi */
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
/* Menampilkan info petak dari input integer */
{
    return Petak((M).map[Petak - 1]);
}
void INSPECT(Map M, int Petak)
/* I.S. Map terdefinisi */
/* F.S. Mereturn nilai teleport pada petak yang ditentukan dari input */
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
/* I.S. Posisi player sekarang terdefinisi dari player dan map */
/* F.S. Posisi player teleport sesuai map */
{
    int outTP = Tp((M).map[currentPosition - 1]);
    if (outTP == -1)
    {
        PrintNamePlayer(*p);
        printf(" tidak menemukan teleport.");
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
                    printf("Apakah ");
                    PrintNamePlayer(*p);
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
                printf("Buff imunitas teleport hilang.");
            }
            else if (CKata.TabKata[1] == 'Y')
            {
                // Pindah tempat
                Posisi(*p) = outTP;
                PrintNamePlayer(*p);
                printf(" teleport ke petak %d.", outTP);
            }
        }
        else if (ImmuneTP(*p) == false)
        {
            // Pindah tempat
            Posisi(*p) = outTP;
            PrintNamePlayer(*p);
            printf(" teleport ke petak %d.", outTP);
        }
    }
}

void ROLL(int minRoll, int maxRoll, int maxPetak, Player *p, Map M)
/* I.S. Player dan map terdefinisi */
/* F.S. Posisi player berpindah sebesar roll yang didapat dan nilai roll berubah sesuai buff yang dimiliki player */
{
    if (BuffPengecil(*p) == true)
    {
        printf("\nMaxRoll sebelum dibuff menggunakan senter pengecil hoki %d\n", maxRoll);
        maxRoll = floor(maxRoll / 2);
        printf("MaxRoll sesudah dibuff menggunakan senter pengecil hoki %d\n", maxRoll);
    }
    else if (BuffPembesar(*p) == true)
    {
        printf("\nMinRoll sebelum dibuff menggunakan senter pembesar hoki %d\n", minRoll);
        minRoll = floor(maxRoll / 2);
        printf("MinRoll sesudah dibuff menggunakan senter pembesar hoki %d\n", minRoll);
    }

    srand(time(0));
    int num = (rand() % (maxRoll - minRoll + 1)) + minRoll;
    puts("");
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
                printf(" maju %d langkah.\n", num);
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
                printf(" mundur %d langkah.\n", num);
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
            printf(" maju %d langkah.\n", num);
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
            printf(" mundur %d langkah.\n", num);
            // Change currentPosition Player
            Posisi(*p) = backward;
            PrintNamePlayer(*p);
            printf(" berada di petak %d.\n", Posisi(*p));
            Teleport(p, Posisi(*p), M);
        }
        else if ((InfoPetak(M, forward) == '#') && (InfoPetak(M, backward) == '#'))
        {
            PrintNamePlayer(*p);
            printf(" tidak dapat bergerak.");
        }
    }
    else if ((forward <= maxPetak) && (backward <= 0))
    {
        if ((InfoPetak(M, forward) == '#'))
        {
            PrintNamePlayer(*p);
            printf(" tidak dapat bergerak.");
        }
        else
        {
            PrintNamePlayer(*p);
            printf(" dapat maju.\n");
            PrintNamePlayer(*p);
            printf(" maju %d langkah.\n", num);
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
            printf(" tidak dapat bergerak.");
        }
        else
        {
            PrintNamePlayer(*p);
            printf(" dapat mundur.\n");
            PrintNamePlayer(*p);
            printf(" mundur %d langkah.\n", num);
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
/* I.S. Player terdefinisi */
/* F.S. Menampilkan buff yang aktif berdasarkan nilai boolean yang ada di player */
{
    printf("\nKamu memiliki buff:\n");
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
void UseSkill(Players *p, int inputs, int currentPlayer, int minRoll, int maxRoll, Map M, int maxPetak)
/* I.S. List skill di dalam player terdefinisi */
/* F.S. Memakai skill yang diinput oleh player dan menjalankan fungsi sesuai skillnya */
{
    int info = PrintInfoKe(PlayerSkills(ArrayPlayer(*p)[currentPlayer]), inputs);
    if (info >= 1 && info <= 10)
    {
        (ImmuneTP(ArrayPlayer(*p)[currentPlayer])) = true;
        DeleteSkill(&(PlayerSkills(ArrayPlayer(*p)[currentPlayer])), inputs);
        // nyalain buff immunity teleport di adt player
        // delete elemen di skill
    }
    else if (info >= 11 && info <= 20)
        {
            int chosenPlayer;
            srand(time(0));
            int num = (rand() % (maxRoll - minRoll + 1)) + minRoll;
            if (JumlahPlayer(*p) == 2)
            {
                if (currentPlayer == JumlahPlayer(*p) - 1)
                {
                    chosenPlayer = 0;
                }
                else
                {
                    chosenPlayer = currentPlayer + 1;
                }
                int CPosisi = Posisi(ArrayPlayer(*p)[chosenPlayer]);
                int backward = CPosisi - num;
                if (InfoPetak(M, backward) != '#' && backward > 0)
                {
                    PrintNamePlayer((ArrayPlayer(*p)[chosenPlayer]));
                    printf(" dapat mundur.\n");
                    PrintNamePlayer((ArrayPlayer(*p)[chosenPlayer]));
                    printf(" mundur %d langkah.\n", num);
                    // Change posisi chosenPlayer
                    Posisi(ArrayPlayer(*p)[chosenPlayer]) = backward;
                    PrintNamePlayer((ArrayPlayer(*p)[chosenPlayer]));
                    printf(" berada di petak %d.\n", Posisi(ArrayPlayer(*p)[chosenPlayer]));
                    Teleport(&(ArrayPlayer(*p)[chosenPlayer]), Posisi(ArrayPlayer(*p)[chosenPlayer]), M);
                    puts("");
                    DeleteSkill(&(PlayerSkills(ArrayPlayer(*p)[currentPlayer])), inputs);
                }
                else if (InfoPetak(M, backward) == '#' || backward < 0)
                {
                    printf("Mundur %d\n", num);
                    PrintNamePlayer((ArrayPlayer(*p)[chosenPlayer]));
                    printf(" tidak dapat bergerak.\n");
                }           
            }
            else
            {
                int arrplayer[4] = {0, 1, 2, 3};  // MAX PLAYER
                int choice[JumlahPlayer(*p) - 1]; // Array yg bukan currentPlayer
                int j = 0;
                // Membuat array tanpa currentPlayer
                puts("Player yang ingin dimundurkan posisinya: ");
                for (int i = 0; i < 4; i++)
                {
                    if ((currentPlayer != arrplayer[i]) && (j < JumlahPlayer(*p) - 1))
                    {
                        choice[j] = arrplayer[i];
                        // Tampilan pilihan player

                        printf("%d. ", j + 1);
                        PrintNamePlayer((ArrayPlayer(*p)[choice[j]]));
                        puts("");
                        j++;
                    }
                }
                printf("\nMasukkan Player: ");
                STARTKATA();
                // ### CEK VALID INPUT START ###
                boolean valid = false;
                int jawaban = KataInt(CKata);
                do
                {
                    if ((jawaban < 1) && (jawaban >= JumlahPlayer(*p)))
                    {
                        printf("Jawab dengan nilai antara 1 sampai %d", JumlahPlayer(*p) - 1);
                        printf("Masukkan Player: ");
                        STARTKATA();
                        jawaban = KataInt(CKata);
                    }
                    else
                    {
                        valid = true;
                    }
                } while (!valid);
                // ### CEK VALID INPUT END ###
                chosenPlayer = choice[jawaban - 1];
                int CPosisi = Posisi(ArrayPlayer(*p)[chosenPlayer]);
                int backward = CPosisi - num;
                if (InfoPetak(M, backward) != '#' && backward > 0)
                {
                    PrintNamePlayer((ArrayPlayer(*p)[chosenPlayer]));
                    printf(" dapat mundur.\n");
                    PrintNamePlayer((ArrayPlayer(*p)[chosenPlayer]));
                    printf(" mundur %d langkah.\n", num);
                    // Change posisi chosenPlayer
                    Posisi(ArrayPlayer(*p)[chosenPlayer]) = backward;
                    PrintNamePlayer((ArrayPlayer(*p)[chosenPlayer]));
                    printf(" berada di petak %d.\n", Posisi(ArrayPlayer(*p)[chosenPlayer]));
                    Teleport(&(ArrayPlayer(*p)[chosenPlayer]), Posisi(ArrayPlayer(*p)[chosenPlayer]), M);
                    puts("");
                    DeleteSkill(&(PlayerSkills(ArrayPlayer(*p)[currentPlayer])), inputs);
                }
                else if (InfoPetak(M, backward) == '#' || backward < 0)
                {
                    printf("Mundur %d\n", num);
                    PrintNamePlayer((ArrayPlayer(*p)[chosenPlayer]));
                    printf(" tidak dapat bergerak.\n");
                } 
            }
        }
    else if (info >= 21 && info <= 30)
        {
            int chosenPlayer;
            srand(time(0));
            int num = (rand() % (maxRoll - minRoll + 1)) + minRoll;
            if (JumlahPlayer(*p) == 2)
            {
                if (currentPlayer == JumlahPlayer(*p) - 1)
                {
                    chosenPlayer = 0;
                }
                else
                {
                    chosenPlayer = currentPlayer + 1;
                }
                int CPosisi = Posisi(ArrayPlayer(*p)[chosenPlayer]);
                int forward = CPosisi + num;
                if (InfoPetak(M, forward) != '#' && forward < maxPetak)
                {
                    PrintNamePlayer((ArrayPlayer(*p)[chosenPlayer]));
                    printf(" dapat maju.\n");
                    PrintNamePlayer((ArrayPlayer(*p)[chosenPlayer]));
                    printf(" maju %d langkah.\n", num);
                    // Change posisi chosenPlayer
                    Posisi(ArrayPlayer(*p)[chosenPlayer]) = forward;
                    PrintNamePlayer((ArrayPlayer(*p)[chosenPlayer]));
                    printf(" berada di petak %d.\n", Posisi(ArrayPlayer(*p)[chosenPlayer]));
                    Teleport(&(ArrayPlayer(*p)[chosenPlayer]), Posisi(ArrayPlayer(*p)[chosenPlayer]), M);
                    puts("");
                    DeleteSkill(&(PlayerSkills(ArrayPlayer(*p)[currentPlayer])), inputs);
                }
                else if (InfoPetak(M, forward) == '#' || forward > maxPetak)
                {
                    printf("Harusnya maju %d\n", num);
                    PrintNamePlayer((ArrayPlayer(*p)[chosenPlayer]));
                    printf(" tidak dapat bergerak.\n");
                }           
            }
            else
            {
                int arrplayer[4] = {0, 1, 2, 3};  // MAX PLAYER
                int choice[JumlahPlayer(*p) - 1]; // Array yg bukan currentPlayer
                int j = 0;
                // Membuat array tanpa currentPlayer
                puts("Player yang ingin dimajukan posisinya: ");
                for (int i = 0; i < 4; i++)
                {
                    if ((currentPlayer != arrplayer[i]) && (j < JumlahPlayer(*p) - 1))
                    {
                        choice[j] = arrplayer[i];
                        // Tampilan pilihan player
                        printf("%d. ", j + 1);
                        PrintNamePlayer((ArrayPlayer(*p)[choice[j]]));
                        puts("");
                        j++;
                    }
                }
                printf("\nMasukkan Player: ");
                STARTKATA();
                // ### CEK VALID INPUT START ###
                boolean valid = false;
                int jawaban = KataInt(CKata);
                do
                {
                    if ((jawaban < 1) && (jawaban >= JumlahPlayer(*p)))
                    {
                        printf("Jawab dengan nilai antara 1 sampai %d", JumlahPlayer(*p) - 1);
                        printf("Masukkan Player: ");
                        STARTKATA();
                        jawaban = KataInt(CKata);
                    }
                    else
                    {
                        valid = true;
                    }
                } while (!valid);
                // ### CEK VALID INPUT END ###
                chosenPlayer = choice[jawaban - 1];
                int CPosisi = Posisi(ArrayPlayer(*p)[chosenPlayer]);
                int forward = CPosisi + num;
                if (InfoPetak(M, forward) != '#' && forward < maxPetak)
                {
                    PrintNamePlayer((ArrayPlayer(*p)[chosenPlayer]));
                    printf(" dapat maju.\n");
                    PrintNamePlayer((ArrayPlayer(*p)[chosenPlayer]));
                    printf(" maju %d langkah.\n", num);
                    // Change posisi chosenPlayer
                    Posisi(ArrayPlayer(*p)[chosenPlayer]) = forward;
                    PrintNamePlayer((ArrayPlayer(*p)[chosenPlayer]));
                    printf(" berada di petak %d.\n", Posisi(ArrayPlayer(*p)[chosenPlayer]));
                    Teleport(&(ArrayPlayer(*p)[chosenPlayer]), Posisi(ArrayPlayer(*p)[chosenPlayer]), M);
                    puts("");
                    DeleteSkill(&(PlayerSkills(ArrayPlayer(*p)[currentPlayer])), inputs);
                }
                else if (InfoPetak(M, forward) == '#' || forward > maxPetak)
                {
                    printf("Harusnya maju %d\n", num);
                    PrintNamePlayer((ArrayPlayer(*p)[chosenPlayer]));
                    printf(" tidak dapat bergerak.\n");
                } 
            }
        }
    else if (info >= 31 && info <= 36)
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
    else if (info >= 37 && info <= 51)
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
    else if (info >= 52 && info <= 66)
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
    else if (info >= 67 && info <= 70)
    {
        int chosenPlayer;
        int temp;
        if (JumlahPlayer(*p) == 2)
        {
            if (currentPlayer == JumlahPlayer(*p) - 1)
            {
                chosenPlayer = 0;
            }
            else
            {
                chosenPlayer = currentPlayer + 1;
            }
            temp = Posisi(ArrayPlayer(*p)[currentPlayer]);
            Posisi(ArrayPlayer(*p)[currentPlayer]) = Posisi(ArrayPlayer(*p)[chosenPlayer]);
            Posisi(ArrayPlayer(*p)[chosenPlayer]) = temp;
            DeleteSkill(&(PlayerSkills(ArrayPlayer(*p)[currentPlayer])), inputs);
        }
        else
        {
            int arrplayer[4] = {0, 1, 2, 3};  // MAX PLAYER
            int choice[JumlahPlayer(*p) - 1]; // Array yg bukan currentPlayer
            int j = 0;
            // Membuat array tanpa currentPlayer
            puts("Player yang ingin ditukar posisinya: ");
            for (int i = 0; i < 4; i++)
            {
                if ((currentPlayer != arrplayer[i]) && (j < JumlahPlayer(*p) - 1))
                {
                    choice[j] = arrplayer[i];
                    // Tampilan pilihan player

                    printf("%d. ", j + 1);
                    PrintNamePlayer((ArrayPlayer(*p)[choice[j]]));
                    puts("");
                    j++;
                }
            }
            printf("Masukkan Player: ");
            STARTKATA();
            // ### CEK VALID INPUT START ###
            boolean valid = false;
            int jawaban = KataInt(CKata);
            do
            {
                if ((jawaban < 1) && (jawaban >= JumlahPlayer(*p)))
                {
                    printf("Jawab dengan nilai antara 1 sampai %d", JumlahPlayer(*p) - 1);
                    printf("Masukkan Player: ");
                    STARTKATA();
                    jawaban = KataInt(CKata);
                }
                else
                {
                    valid = true;
                }
            } while (!valid);
            // ### CEK VALID INPUT END ###
            chosenPlayer = choice[jawaban - 1];
            temp = Posisi(ArrayPlayer(*p)[currentPlayer]);
            Posisi(ArrayPlayer(*p)[currentPlayer]) = Posisi(ArrayPlayer(*p)[chosenPlayer]);
            Posisi(ArrayPlayer(*p)[chosenPlayer]) = temp;
            DeleteSkill(&(PlayerSkills(ArrayPlayer(*p)[currentPlayer])), inputs);
        }
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
void skill(Players *p, int currentPlayer, int minRoll, int maxRoll, Map M, int maxPetak)
/* I.S. List skill di dalam player terdefinisi */
/* F.S. Menampilkan skill player dan menerima input user untuk melakukan aksi seperti memakai atau membuang skill */
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
    boolean kosong = IsEmpty((PlayerSkills(ArrayPlayer(*p)[currentPlayer])));
    boolean OutFungsi = false;
    boolean CekJenisNumber = IsNumber(CKata);
    // A
    do
    {
        if (!(CekJenisNumber) || (inputs > NbElmt((PlayerSkills(ArrayPlayer(*p)[currentPlayer])))) || (inputs < (-1 * NbElmt((PlayerSkills(ArrayPlayer(*p)[currentPlayer]))))))
        {
            puts("\nInput tidak valid!!!");
        }
        else
        {
            if (inputs > 0 && inputs <= NbElmt((PlayerSkills(ArrayPlayer(*p)[currentPlayer]))))
            {
                puts("");
                PrintNamePlayer((ArrayPlayer(*p)[currentPlayer]));
                printf(" memakai skill ");
                PrintSkillKe((PlayerSkills(ArrayPlayer(*p)[currentPlayer])), inputs);
                UseSkill(p, inputs, currentPlayer, minRoll, maxRoll, M, maxPetak);
                kosong = IsEmpty((PlayerSkills(ArrayPlayer(*p)[currentPlayer])));
                // DeleteSkill(&(PlayerSkills(*p)), inputs);
            }
            else if (inputs < 0 && inputs >= (-1 * NbElmt((PlayerSkills(ArrayPlayer(*p)[currentPlayer])))))
            {
                inputs = inputs * (-1);
                puts("");
                PrintNamePlayer((ArrayPlayer(*p)[currentPlayer]));
                printf(" membuang skill ");
                PrintSkillKe((PlayerSkills(ArrayPlayer(*p)[currentPlayer])), inputs);
                DeleteSkill(&(PlayerSkills(ArrayPlayer(*p)[currentPlayer])), inputs);
                kosong = IsEmpty((PlayerSkills(ArrayPlayer(*p)[currentPlayer])));
            }
            else if (kosong == true)
            {
                printf("\nSkill kosong sehingga tidak dapat dihapus atau dipakai\n");
                OutFungsi = true;
                break;
            }
            else if (inputs == 0)
            {
                puts("");
                PrintNamePlayer((ArrayPlayer(*p)[currentPlayer]));
                printf(" keluar dari command SKILL\n");
                OutFungsi = true;
                break;
            }
        }

        PrintMenuSkill((PlayerSkills(ArrayPlayer(*p)[currentPlayer])));
        printf("\nMasukkan skill: ");
        STARTKATA();
        CekJenisNumber = IsNumber(CKata);
        inputs = KataInt(CKata);
    } while (!OutFungsi);
    // ### CEK VALID INPUT END ###
}

void UNDO(Stack *s, Players *ps)
{
    Pop(s, ps);
}

// int test2(List L, int x)
// {
// }
// void test(Players *p, int inputs, int currentPlayer)
// {
//     test2(PlayerSkills((ArrayPlayer(*p)[currentPlayer])), 1);

//     PlayerSkills((ArrayPlayer(*p)[currentPlayer]));
//     Posisi((ArrayPlayer(*p)[currentPlayer]));
// }