/* FUN_80066768 (0x80066768) */
typedef struct{char p[0x24];int f24;char q[0x78-0x28];}E;
extern E DAT_800a5398[];
extern int DAT_800d1afc;
int DAT_800d2360,DAT_800d2374,DAT_800d2378,DAT_800d237c,DAT_800d2380,DAT_800d2390;
extern int DAT_800d3810[],DAT_800d3840[];
extern char DAT_800a21cc[];
void FUN_8004cc18(void);
int FUN_8004cb10(int);
int FUN_8004c8a4(char*);
int FUN_8004d068(int,int,int);
void FUN_8008c190(char*,char*);
void FUN_8008e904(char*,int);
void FUN_80066768(void){
  char buf[16];
  int n,t,one;
  FUN_8004cc18();
  if(DAT_800d1afc==0&&DAT_800d2380==0&&DAT_800d2390<4){
    t=DAT_800d2374;
    one=1;
    if(t>=0){
      DAT_800d2390++;
      DAT_800d3840[DAT_800d2360]=one;
    }else{
      DAT_800d2374=DAT_800d2374+1;
      goto L50;
    }
    if(t<DAT_800d237c/2) DAT_800d2374=DAT_800d237c-t-1;
    else{
      if(DAT_800d237c/2>=t){
        DAT_800d2380=one;
        return;
      }
      DAT_800d2374=DAT_800d237c-t;
    }
L50:
    DAT_800d2360=DAT_800d2374+DAT_800d2378;
    if(DAT_800d2360>=DAT_800d237c) DAT_800d2360-=DAT_800d237c;
    FUN_8008e904(buf,DAT_800a5398[DAT_800d2360].f24);
    n=FUN_8004c8a4(buf);
    if(n<=0){
      FUN_8008c190(DAT_800a21cc,buf);
      return;
    }
    t=FUN_8004d068(n,1,1);
    DAT_800d3810[DAT_800d2360]=t;
    FUN_8004cb10(t);
  }
}
