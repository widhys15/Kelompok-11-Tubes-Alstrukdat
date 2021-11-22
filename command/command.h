#ifndef command_H
#define command_H
#include "../boolean.h"
#include "../array/array.h"
#include "../player/player.h"
#include <time.h>
void PrintLokasiPlayer(Map M, Player p);
void MAP(Map M, Players ps);
char InfoPetak(Map M, int Petak);
void INSPECT(Map M, int Petak);
void Teleport(Player *p, int currentPosition, Map M);
void ROLL(int minRoll, int maxRoll, int maxPetak, Player *p, Map M);
void UseSkill(Players *p, int inputs, int currentPlayer);
void skill(Players *p, int currentPlayer);
void oldSkill(Player *p);
void Buff(Players p, int currentPlayer);
// void CopyArrayPlayer(Players copy, Players *paste);
#endif