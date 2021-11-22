#ifndef player_H
#define player_H

#include "../boolean.h"
#include "../mesinkata/mesin_kata.h"
#include "../mesinkar/mesin_kar.h"
#include "../skill/listlinier.h"
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
// DEFINE SKILLS
#define InfoSkill(S) (S).First->infoSkill
#define NextSkill(S) (S)->Next

void CreateEmptyArrayPlayer(Players *p);
void AddPlayer(Players *p, int jumlahPlayer);
void CreatePlayer(Player *p, int playerKe);
void PrintNamePlayer(Player p);
#endif
