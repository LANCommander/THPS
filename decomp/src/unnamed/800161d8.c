/* FUN_800161d8 (0x800161d8) */
extern char DAT_8009e2ec[];
extern char DAT_8009e2f8[];
extern volatile int DAT_800d1a1c;
void FUN_8006af64(void);
void Mess_LoadFont__FPciii(char*,int,int,int);
void FUN_8008c3d0(int);
void FUN_8006b240(void);
void FUN_80061ea0(void);
void FUN_80061e00(int,int,int,int);
void FUN_8001d250(int);
void Mess_SetScale__Fi(int);
void Mess_SetRGB__FUcUcUci(int,int,int,int);
void FUN_8001e114(int,int,char*,int,int,int,int);
void FUN_8006b26c(void);
void Mess_UnloadFont__Fv(void);
void FUN_800161d8(void){
  int i;
  FUN_8006af64();
  Mess_LoadFont__FPciii(DAT_8009e2ec,-1,-1,-1);
  FUN_8008c3d0(1);
  i=0;
  do{
    i++;
    FUN_8006b240();
    FUN_80061ea0();
    DAT_800d1a1c=0;
    FUN_80061e00(0,0,640,480);
    FUN_8001d250(0);
    Mess_SetScale__Fi(384);
    Mess_SetRGB__FUcUcUci(150,100,25,0);
    FUN_8001e114(320,240,DAT_8009e2f8,1,0,256,0);
    FUN_8006b26c();
  }while(i<2);
  Mess_UnloadFont__Fv();
}
