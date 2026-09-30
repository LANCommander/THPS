/* Load8BitBMP__FPcPPcPiT2PUs (0x80061654) */
extern char DAT_800a208c[];
extern char DAT_800a20a0[];
int FUN_8004c8a4(char*);
char*FUN_8004d068(int,int,int);
void FUN_8004cb10(char*);
void FUN_8004cdd0(void);
void FUN_8008c190(char*,char*);
void Load8BitBMP2__FPcPPcPiT2PUs(char*,char**,int*,int*,unsigned short*);
int Load8BitBMP__FPcPPcPiT2PUs(char*name,char**a,int*b,int*c,unsigned short*d){
  int r=FUN_8004c8a4(name);
  char*p;
  if(r<=0){
    FUN_8008c190(DAT_800a208c,name);
    return 0;
  }
  p=FUN_8004d068(r,1,1);
  if(p){
    FUN_8004cb10(p);
    FUN_8004cdd0();
    Load8BitBMP2__FPcPPcPiT2PUs(p,a,b,c,d);
    return 1;
  }
  FUN_8008c190(DAT_800a20a0,name);
  return 0;
}
