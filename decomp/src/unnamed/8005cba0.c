/* FUN_8005cba0 (0x8005cba0) */
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
typedef struct{char p[12];int f;char q[0x78-16];}E;
extern E DAT_800a5398[];
extern char DAT_800c0a48[];
int DAT_800d1cf0,DAT_800d1cf4;
unsigned DAT_800d1cf8;
void Pad_ClearTriggers__FP8SControl(char*);
DRAWENV* FUN_80092e70(DRAWENV*,int,int,int,int);
DISPENV* FUN_800914fc(DISPENV*,int,int,int,int);
int FUN_8008c5ec(RECT*,int,int,int);
void FUN_8008eebc(int);
void FUN_8008c94c(DRAWENV*);
void FUN_8008ca0c(DISPENV*);
void FUN_8005cd14();
void FUN_8005d00c();
void FUN_8005d28c();
void FUN_8005cba0(void){
  DISPENV de;
  DRAWENV dr;
  RECT r;
  DAT_800d1cf0=0;
  Pad_ClearTriggers__FP8SControl(DAT_800c0a48);
  Pad_ClearTriggers__FP8SControl(DAT_800c0a48+364);
  FUN_80092e70(&dr,0,0,512,240);
  FUN_800914fc(&de,0,0,512,240);
  r.x=0;
  r.y=0;
  r.w=512;
  r.h=240;
  FUN_8008c5ec(&r,0,0,0);
  FUN_8008eebc(0);
  FUN_8008c5ec(&r,0,0,0);
  dr.dfe=0;
  dr.isbg=0;
  dr.r0=255;
  dr.g0=0;
  dr.b0=0;
  FUN_8008c94c(&dr);
  FUN_8008ca0c(&de);
  if(DAT_800d1cf8<6){
    switch(DAT_800d1cf8){
    case 0:
      if(DAT_800a5398[DAT_800d1cf4].f!=0){
        FUN_8005cd14();
        return;
      }
      FUN_8005d00c();
      return;
    case 1:
    case 3:
    case 5:
      FUN_8005cd14();
      return;
    case 2:
      FUN_8005d28c();
      break;
    }
  }
}
