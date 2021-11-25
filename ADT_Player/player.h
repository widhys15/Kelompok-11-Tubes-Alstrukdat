#ifndef player_H
#define player_H

#include "../boolean.h"
#include "../ADT_Mesinkata/mesin_kata.h"
#include "../ADT_Mesinkar/mesin_kar.h"
#include "../ADT_Skill/listlinier.h"
#include <stdlib.h>
#define MaxName 20

typedef struct
{
    char name[MaxName];
    int nameLength;
    int currentPosition;
    boolean ImmuneTP;
    boolean pembesar;
    boolean pengecil;
    boolean cermin;
    List ListSkills;
} Player;
typedef struct
{
    int jumlahPlayer;
    Player players[4];
} Players;

// Define Players
#define JumlahPlayer(PS) (PS).jumlahPlayer
#define ArrayPlayer(PS) (PS).players
#define SkillInPlayerKe(PS, i) (PS, i).

// Define Player
#define Name(P) (P).name
#define Posisi(P) (P).currentPosition
#define NameLength(P) (P).nameLength
#define PlayerSkills(P) (P).ListSkills
#define ImmuneTP(P) (P).ImmuneTP
#define BuffPembesar(P) (P).pembesar
#define BuffPengecil(P) (P).pengecil
#define Cermin(P) (P).cermin

// Define Skill
#define InfoSkill(S) (S).First->infoSkill
#define NextSkill(S) (S)->Next

void CreateEmptyArrayPlayer(Players *p);
/* I.S. sembarang             */
/* F.S. Terbentuk array players kosong */

void AddPlayer(Players *p, int jumlahPlayer);
/* I.S. p terdefinisi */
/* F.S. Menambahkan player sejumlah input ke dalam array players */

void CreatePlayer(Player *p, int playerKe);
/* I.S. p terdefinisi */
/* F.S. Mengisi data-data seperti nama, posisi, dan list skill ke dalam player */

void PrintNamePlayer(Player p);
/* I.S. p terdefinisi */
/* F.S. Menampilkan nama player */

void PrintRanking(Players ps);
/* I.S. ps terdefinisi */
/* F.S. Menampilkan Ranking pemain yang menang */

#endif
