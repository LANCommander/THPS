/* FUN_8002566c (0x8002566c) */
struct E{char p[0x48];int f48,f4c,f50;char*n[64];};
extern struct E DAT_800a44fc[];
extern unsigned char DAT_800a706c[];
struct GA{char pad[0x826];unsigned char b826,b827;};
extern struct GA DAT_800a6844;
extern short DAT_800a679c[],DAT_800a67b0[],DAT_800a67c4[],DAT_800a67d8[],DAT_800a67ec[],DAT_800a6800[],DAT_800a6814[],DAT_800a6828[],DAT_800a683c[];
extern int DAT_800d1114;
extern char DAT_800d1ff0;
extern int DAT_800d1f14,DAT_800d1f18;
int DAT_800d16d8,DAT_800d16e0,DAT_800d16e4,DAT_800d16e8,DAT_800d1770,DAT_800d1780,DAT_800d1784,DAT_800d1790,DAT_800d1794,DAT_800d1798,DAT_800d17e8,DAT_800d17ec,DAT_800d1838,DAT_800d183c,DAT_800d1840,DAT_800d1844;
extern volatile int DAT_800d1a20,DAT_800d1a24;
void FUN_8007ef30(void);
void FUN_8008e904(char*,char*);
int Mess_LoadFont__FPciii(char*,int,int,int);
void Pad_ClearAll__Fv(void);
void Redbook_InitialRand__Fi(int);
void ReplaceTexture__FUiPc(int,char*);
void FUN_8002566c(void){
  char nm[2][16];int i,j,k;
  DAT_800d17e8=0;DAT_800d17ec=0;
  FUN_8008e904(nm[0],DAT_800a44fc[DAT_800d1114].n[DAT_800a6844.b826<<3]);
  FUN_8008e904(nm[1],DAT_800a44fc[DAT_800d16d8].n[DAT_800a6844.b827<<3]);
  for(i=0;i<2;i++)nm[i][1]=95;
  ReplaceTexture__FUiPc(DAT_800a44fc[DAT_800d1114].f48,nm[0]);
  if(DAT_800d1780==2)ReplaceTexture__FUiPc(DAT_800a44fc[DAT_800d16d8].f48,nm[1]);
  {char*tab[15]={"W1blue01.bmp","W1blue02.bmp","W1blue03.bmp","W1blue04.bmp","W1brow01.bmp","W1dark01.bmp","W1gree01.bmp","W1gree02.bmp","W1gree03.bmp","W1oran01.bmp","W1purp01.bmp","W1red_01.bmp","W1red_02.bmp","W1whit01.bmp","W1yell01.bmp"};
  for(j=0;j<2;j++){
    char*t=tab[DAT_800a706c[j]];
    FUN_8008e904(nm[j],t);
    nm[j][1]=95;
  }
  }
  ReplaceTexture__FUiPc(DAT_800a44fc[DAT_800d1114].f4c,nm[0]);
  if(DAT_800d1780==2)ReplaceTexture__FUiPc(DAT_800a44fc[DAT_800d16d8].f4c,nm[1]);
  for(k=0;k<2;k++)nm[k][1]=84;
  ReplaceTexture__FUiPc(DAT_800a44fc[DAT_800d1114].f50,nm[0]);
  if(DAT_800d1780==2)ReplaceTexture__FUiPc(DAT_800a44fc[DAT_800d16d8].f50,nm[1]);
  DAT_800a679c[0]=3413;DAT_800a67b0[0]=2275;DAT_800a67c4[0]=2275;DAT_800a67d8[0]=3413;DAT_800a67ec[0]=3413;
  DAT_800a6800[0]=2275;DAT_800a6814[0]=2275;DAT_800a6828[0]=2275;DAT_800d1784=0;DAT_800a683c[0]=2275;
  DAT_800d1a20=0;DAT_800d1a24=0;DAT_800d1838=0;DAT_800d1770=0;DAT_800d16e4=0;DAT_800d16e8=0;
  DAT_800d1ff0=0;
  DAT_800d1844=DAT_800d1a24;
  Pad_ClearAll__Fv();
  DAT_800d1f14=0;DAT_800d1f18=0;DAT_800d183c=0;DAT_800d1840=0;DAT_800d16e0=0;
  Redbook_InitialRand__Fi(0x12a6cc58);
  FUN_8007ef30();
  DAT_800d1794=Mess_LoadFont__FPciii("time.fnt",-1,-1,0);
  DAT_800d1798=Mess_LoadFont__FPciii("score.fnt",-1,-1,0);
  DAT_800d1790=Mess_LoadFont__FPciii("ingame1.fnt",2,2,-1);
}
