/* FUN_80061270 (0x80061270) */
int DAT_800d1d84;
int DAT_800d1d88;
short DAT_800d1d8c,DAT_800d1d8e;
extern char DAT_800a200c[],DAT_800a2024[],DAT_800a2048[];
void FUN_8006b240(void);
void FUN_80061ea0(void);
void draw__6Spriteiiiiii(int,int,int,int,int,int,int);
void Mess_SetRGB__FUcUcUci(int,int,int,int);
void FUN_8001d250(int);
void FUN_8001f1b4(int);
void Mess_SetFontScale__FUi(int);
void FUN_8001e114(int,int,char*,int,int,int,int);
void FUN_8006b26c(void);
void FUN_8008eebc(int);
void FUN_80061270(int a){
  int i;
  if(a!=DAT_800d1d84){
    DAT_800d1d84=a;
    for(i=0;i<2;i++){
      FUN_8006b240();
      FUN_80061ea0();
      draw__6Spriteiiiiii(DAT_800d1d88,DAT_800d1d8c,DAT_800d1d8e,0,-1,-1,-1);
      Mess_SetRGB__FUcUcUci(128,128,128,0);
      FUN_8001d250(0);
      FUN_8001f1b4(4);
      if(a==0){
        Mess_SetFontScale__FUi(192);
        FUN_8001e114(320,357,DAT_800a200c,1,0,256,0);
      }else if(a==1){
        Mess_SetFontScale__FUi(144);
        FUN_8001e114(320,341,DAT_800a2024,1,0,256,0);
        FUN_8001e114(320,373,DAT_800a2048,1,0,256,0);
      }
      FUN_8006b26c();
    }
    Mess_SetFontScale__FUi(255);
    FUN_8008eebc(0);
  }
}
