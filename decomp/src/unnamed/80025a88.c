/* FUN_80025a88 (0x80025a88) */
struct L{char pad[12];int f;char q[104];};
struct E{char*a;char*b;char pad[4];int c;char pad2[0x40-0x10];char*s;char pad3[0x154-0x44];};
extern struct L DAT_800a5398[];
extern struct E DAT_800a44fc[];
#define EN(x) (*(struct E*)((char*)DAT_800a44fc+(x)*340))
#define EP(x) (ents[x])
extern int DAT_800a42f4[];
extern char DAT_800a8240[];
extern char DAT_800a8245[];
extern int DAT_800d1114;
int DAT_800d16a4;
int DAT_800d16d8;
int DAT_800d1780;
int DAT_800d179c;
char* DAT_800d17c8;
char* DAT_800d17cc;
extern int DAT_800d1de8;
extern int DAT_800d1e28;
char* FUN_800434d4(int);
char* FUN_80041e5c(char*);
char* FUN_800785f0(char*,char*,int);
void TrickTips_Init__Fv(void);
void StartCompetitionIntro__7CCamera(char*);
void InitItem__6CBrucePc(char*,char*);
void FUN_80041ce0(char*,int);
void FUN_80025a88(void){
  char*s1;char*s0;char*s2;struct E*e;struct E*ents;
  s1=FUN_800434d4(3612);
  if(s1)s1=FUN_80041e5c(s1);
  DAT_800d17c8=s1;
  DAT_800d17cc=0;
  *(int*)(s1+2160)=0;
  s0=FUN_800434d4(1712);
  if(s0)s0=FUN_800785f0(s0,s1,0);
  *(int*)(s0+1412)=1;
  TrickTips_Init__Fv();
  if(DAT_800a5398[DAT_800d1e28].f&&DAT_800d16a4==1&&DAT_800a42f4[0]==0&&DAT_800d1de8==0)StartCompetitionIntro__7CCamera(s0);
  if(DAT_800d16a4!=7||DAT_800d179c==0)*(int*)(s1+744)=DAT_800d1114;
  else *(int*)(s1+744)=DAT_800d16d8;
  *(char**)(s1+472)=s0;
  if(DAT_800d1780==2&&DAT_800d16a4!=7){e=DAT_800a44fc;e=(struct E*)((int)e+*(int*)(s1+744)*340);InitItem__6CBrucePc(s1,e->b);}
  else InitItem__6CBrucePc(s1,EN(*(int*)(s1+744)).a);
  if(*EN(*(int*)(s1+744)).s==82||*EN(*(int*)(s1+744)).s==114)*(int*)(s1+308)|=2;
  *(char**)(s1+408)=DAT_800a8240;
  FUN_80041ce0(s1,0);
  ents=DAT_800a44fc;
  if(EP(*(int*)(s1+744)).c==16384)*(int*)(s1+404)|=4096;
  if(DAT_800d1780==2&&DAT_800d16a4!=7){
    s0=FUN_800434d4(3612);
    if(s0)s0=FUN_80041e5c(s0);
    *(int*)(s0+2160)=1;
    s2=FUN_800434d4(1712);
    if(s2)s2=FUN_800785f0(s2,s0,0);
    *(int*)(s2+1412)=1;
    *(int*)(s0+744)=DAT_800d16d8;
    InitItem__6CBrucePc(s0,EP(DAT_800d16d8).b);
    if(*EP(*(int*)(s0+744)).s==82||*EP(*(int*)(s0+744)).s==114)*(int*)(s0+308)|=2;
    *(char**)(s1+468)=s0;
    *(char**)(s0+468)=s1;
    *(char**)(s0+472)=s2;
    DAT_800d17cc=s0;
    *(char**)(s0+408)=DAT_800a8245;
    FUN_80041ce0(s0,1);
  }
}
