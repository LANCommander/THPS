/* Display_Viewport__FP9SViewporti (0x80024ce4) */
/* MAIN.CPP, as C (demo twin). Renders one viewport: points the OT at its layer block, sets up the
   camera, then renders the item lists, skaters (with their shadow tint), bits and background. */
typedef struct{char p[0x358];int f358;char q[0x734-0x35c];int f734;}B;
extern char DAT_800c119c[];
int DAT_800d16d0,DAT_800d16d4;
extern int DAT_800d1618,DAT_800d1eec,DAT_800d1fe4,DAT_800d2048,DAT_800d1998,DAT_800d19a4,DAT_800d19b0;
int DAT_800d173c;
B* DAT_800d17cc;
extern short DAT_800d214c,DAT_800d214e;
typedef struct{char pad[140];unsigned long Layer[8192];unsigned long*pCurrent;}OTB;
extern OTB* DAT_800d1a48;
B* DAT_800d17c8;
void FUN_8002ab20(void);
void FUN_8002efa4(B*);
void FUN_800831f8(char*,int,char*);
void FUN_80083774(void);
void FUN_80083838(int);
void M3d_RenderBackground__FPv(int);
void TempRestore__6CBruce(B*);
void FUN_80024ce4(int a,int b){
  short s1,s0;
  DAT_800d2048=b;
  FUN_800831f8(DAT_800c119c+b*164,a,(char*)(DAT_800d1a48->pCurrent=&DAT_800d1a48->Layer[b*4096]));
  DAT_800d16d4=DAT_800d16d0;
  FUN_80083838(DAT_800d1eec);
  DAT_800d16d4=0;
  FUN_80083838(DAT_800d19b0);
  FUN_8002efa4(DAT_800d17c8);
  if(DAT_800d17cc) FUN_8002efa4(DAT_800d17cc);
  s1=DAT_800d214c;
  s0=DAT_800d214e;
  if(DAT_800d17c8->f734&&DAT_800d17c8->f358==0){
    DAT_800d214c=128;
    DAT_800d214e=128;
  }else{
    DAT_800d214c=0;
    DAT_800d214e=0;
  }
  FUN_80083838(DAT_800d19a4);
  TempRestore__6CBruce(DAT_800d17c8);
  if(DAT_800d17cc) TempRestore__6CBruce(DAT_800d17cc);
  DAT_800d214c=s1;
  DAT_800d214e=s0;
  FUN_8002ab20();
  FUN_80083838(DAT_800d1998);
  FUN_80083838(DAT_800d1618);
  if(DAT_800d173c==0) M3d_RenderBackground__FPv(DAT_800d1fe4);
  FUN_80083774();
}
