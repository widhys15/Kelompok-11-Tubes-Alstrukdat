/* File         : command.h */
/* Deskripsi    : Header file untuk command */

#ifndef command_H
#define command_H
#include "../boolean.h"
#include "../ADT_Map/array.h"
#include "../ADT_Stack/stacklist.h"
#include <time.h>

void PrintLokasiPlayer(Map M, Player p);
/* I.S. Player dan Map terdefinisi */
/* F.S. Menampilkan lokasi player dari map yang terdefinisi */

void MAP(Map M, Players ps);
/* I.S. Player dan map terdefinisi */
/* F.S. Menampilkan Map yang terdefinisi */

char InfoPetak(Map M, int Petak);
/* Menampilkan info petak dari input integer */

void INSPECT(Map M, int Petak);
/* I.S. Map terdefinisi */
/* F.S. Mereturn nilai teleport pada petak yang ditentukan dari input */

void Teleport(Player *p, int currentPosition, Map M);
/* I.S. Posisi player sekarang terdefinisi dari player dan map */
/* F.S. Posisi player teleport sesuai map */

void ROLL(int minRoll, int maxRoll, int maxPetak, Player *p, Map M);
/* I.S. Player dan map terdefinisi */
/* F.S. Posisi player berpindah sebesar roll yang didapat dan nilai roll berubah sesuai buff yang dimiliki player */

void UseSkill(Players *p, int inputs, int currentPlayer, int minRoll, int maxRoll, Map M, int maxPetak);
/* I.S. List skill di dalam player terdefinisi */
/* F.S. Memakai skill yang diinput oleh player dan menjalankan fungsi sesuai skillnya */

void skill(Players *p, int currentPlayer, int minRoll, int maxRoll, Map M, int maxPetak);
/* I.S. List skill di dalam player terdefinisi */
/* F.S. Menampilkan skill player dan menerima input user untuk melakukan aksi seperti memakai atau membuang skill */

void Buff(Players p, int currentPlayer);
/* I.S. Player terdefinisi */
/* F.S. Menampilkan buff yang aktif berdasarkan nilai boolean yang ada di player */

void UNDO(Stack *s, Players *ps);
/* I.S. Stack s terdefinisi */
/* F.S. Mengembalikan game ke state sebelumnya */

boolean VotingUndo(Players ps);
/* I.S. Player terdefinisi */
/* F.S. Menghasilkan boolean, bila true maka UNDO dapat digunakan */
#endif