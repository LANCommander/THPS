/* Competition_JudgeDisplay__Fv (0x800747b0) */
typedef struct {
  char _0[16]; unsigned i16; char _14[12]; int i32; char _24[44]; short x[5]; unsigned char b90, b91; char _5c[100]; unsigned char b192;
} J;
extern J DAT_800c0fdc;
extern char DAT_800a33f0[], DAT_800a3400[], DAT_800a3410[], DAT_800a3424[], DAT_800a3430[], DAT_800d1fd8[];
extern char* DAT_800a5edc[];
void Mess_DeleteAll__Fv(void);
void Mess_SetScale__Fi(int);
void FUN_8001d250(int);
void Mess_SetRGB__FUcUcUci(unsigned char, unsigned char, unsigned char, int);
int FUN_8008b900(char*, char*, ...);
int FUN_8001e114(int, int, char*, int, int, int, int);
void FUN_8004b250(int, int, int);
void Front_PrintCentredPrompt__FPCc(char*);
void Competition_JudgeDisplay__Fv(void){
  char buf[16];
  J* p = &DAT_800c0fdc;
  int i, t, c, sum, k;
  unsigned s;
  Mess_DeleteAll__Fv();
  Mess_SetScale__Fi(256);
  FUN_8001d250(0);
  Mess_SetRGB__FUcUcUci(182, 132, 36, 0);
  FUN_8008b900(buf, DAT_800a33f0, p->b192 + 1);
  FUN_8001e114(256, 40, buf, 0, 0, 256, 0);
  FUN_8001e114(256, 70, DAT_800a3400, 0, 0, 256, 0);
  Mess_SetRGB__FUcUcUci(122, 122, 122, 0);
  FUN_8001d250(1);
  t = 0;
  if (p->i16 >= 76) t = (p->i16 - 75) << 2;
  if (t > 100) t = 100;
  c = (122 - t) & 255;
  for (i = 0; i < 5; i++) {
    s = i * 15;
    if (p->i16 == s + 1) FUN_8004b250(52, 8192, 0);
    if (s < p->i16) {
      FUN_8008b900(buf, DAT_800a3410, i + 1, p->x[i] / 10, p->x[i] % 10);
    } else {
      FUN_8008b900(buf, DAT_800a3424, i + 1);
    }
    if (i == p->b91 || i == p->b90) Mess_SetRGB__FUcUcUci(c, c, c, 0);
    else Mess_SetRGB__FUcUcUci(122, 122, 122, 0);
    FUN_8001e114(150, i * 20 + 90, buf, 0, 0, 256, 0);
  }
  if (t >= 100) {
    if (p->i32 == 0) FUN_8004b250(51, 8192, 0);
    FUN_8001d250(0);
    Mess_SetRGB__FUcUcUci(182, 132, 36, 0);
    sum = 0;
    for (k = 0; k < 5; k++)
      if (k != p->b91 && k != p->b90) sum += p->x[k];
    sum = sum / 3;
    FUN_8001d250(0);
    FUN_8008b900(buf, DAT_800a3430, p->b192 + 1);
    FUN_8001e114(200, 195, buf, 0, 0, 256, 0);
    FUN_8008b900(buf, DAT_800d1fd8, sum / 10, sum % 10);
    Mess_SetScale__Fi(384);
    FUN_8001e114(335, 195, buf, 0, 0, 256, 0);
    p->i32 = 1;
  } else {
    p->i32 = 0;
  }
  Mess_SetScale__Fi(256);
  Front_PrintCentredPrompt__FPCc(DAT_800a5edc[0]);
}
