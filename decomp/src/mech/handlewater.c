/* HandleWater__6CBruce (0x80043258) */
typedef struct { int x, y, z; } V;
typedef struct { char _0[4]; V pos; } B;
extern int DAT_800d1780, DAT_800d16f0, DAT_800d16f4, DAT_800d16e4;
typedef struct { short a, b; } T;
extern T DAT_800c9670[] __attribute__((section(".data")));
int DAT_800d19a4;
int Redbook_Rnd__Fi(int);
void FUN_8004b250(int, int, int);
char* FUN_80027d08(int);
void FUN_8004ea54(char*, V*, int, int, int, int, int, int);
void HandleWater__6CBruce(B* t){
  int s1, r, idx;
  V v;
  char* o;
  T* e;
  if (DAT_800d1780 != 2) {
    if ((int)t == DAT_800d19a4) s1 = DAT_800d16f0;
    else s1 = DAT_800d16f4;
    if (s1 < t->pos.y + 0x19000) {
      if (!(*(unsigned short*)t & 8)) FUN_8004b250(43, 8192, 0);
      *(unsigned short*)t |= 8;
      if (!(DAT_800d16e4 & 3)) {
        v = t->pos;
        v.y = s1;
        Redbook_Rnd__Fi(24);
        r = Redbook_Rnd__Fi(24) + 16;
        idx = Redbook_Rnd__Fi(4096) & 0xfff;
        e = &DAT_800c9670[idx];
        v.x += r * e->a;
        v.z += r * e->b;
        o = FUN_80027d08(116);
        if (o) {
          r = Redbook_Rnd__Fi(24) + 40;
          FUN_8004ea54(o, &v, r, 221, 238, 255, 12, Redbook_Rnd__Fi(3) + 4);
        }
      }
    } else {
      *(unsigned short*)t &= ~8;
    }
  }
}
