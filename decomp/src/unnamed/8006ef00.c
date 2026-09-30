/* FUN_8006ef00 (0x8006ef00) */
struct T{char pad[12];int*tab;char q[48];};
extern struct T DAT_800bf7a8[];
int FUN_8006ef00(char*p){return DAT_800bf7a8[p[27]].tab[*(unsigned short*)(p+22)];}
