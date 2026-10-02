/* FUN_800154f4 (0x800154f4) */
struct B{int w[628];};
extern int DAT_800a5880[];
typedef struct{char n[40];}E;
extern E DAT_800a58bc[];
extern struct B DAT_800a6844;
extern char DAT_800a4308[];
extern int DAT_800d10f4,DAT_800d10f8;
void FUN_80010000(void);
int SyncToGoodState__Fv(void);
void FUN_80061270(int);
void Card_GetDirAndFreeBlocks__Fii(int,int);
int FUN_8004d068(int,int,int);
void Card_SetSelectedFile__FPc(E*);
int Card_Load__F9EFileTypePUlT1(int,int,int);
int FUN_8008eebc(int);
void Front_ExtractASCIINameFromSJIS__FPcT0(char*,char*);
void FUN_8004d5d0(int);
void FUN_800103a4(void);
void FUN_800101e4(void);
int FUN_800154f4(void){
  struct B buf;
  int i,r,s2,s4,p;
  E*name;
  struct B*d;
  r=0;
  FUN_80010000();
  if(SyncToGoodState__Fv()==0){
    FUN_80061270(0);
    Card_GetDirAndFreeBlocks__Fii(0,0);
    s4=-1;
    s2=0;
    i=0;
    do{
      if(DAT_800a5880[i]==0){
        p=FUN_8004d068(3200,1,1);
        Card_SetSelectedFile__FPc(&DAT_800a58bc[i]);
        if(Card_Load__F9EFileTypePUlT1(0,p,0)==0){
          if(s2==0)s2=FUN_8008eebc(-1);
          FUN_80061270(1);
          DAT_800d10f4=1;
          DAT_800d10f8=0;
          r=1;
          buf=*(struct B*)(p+640);
          d=&DAT_800a6844;
          if(((unsigned short*)&buf)[1047]>=((unsigned short*)d)[1047]){
            *d=buf;
            s4=i;
            Front_ExtractASCIINameFromSJIS__FPcT0((char*)(p+32),DAT_800a4308);
          }
        }
        FUN_8004d5d0(p);
      }
      i++;
    }while(i<15);
    if(s4>=0){
      Card_SetSelectedFile__FPc(&DAT_800a58bc[s4]);
      FUN_800103a4();
      FUN_800101e4();
    }
    while(s2!=0&&FUN_8008eebc(-1)<s2+60);
    return r;
  }
  return 0;
}
