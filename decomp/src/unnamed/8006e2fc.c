/* FUN_8006e2fc (0x8006e2fc) */
typedef struct{char p[0x38];int f38;char q[0x78-0x3c];}E;
extern E DAT_800a5398[];
extern char *DAT_800a5d7c[],*DAT_800a5d80[],*DAT_800a5d84[],*DAT_800a5d8c[];
extern int DAT_800a5d88[];
extern char DAT_800a6070[];
extern char DAT_800d3868[];
extern int DAT_800d1e28;
int DAT_800d1e5c;
void FUN_80010724(int,int);
int FUN_8004b250(int,int,int);
void FUN_8008b900(char*,int,int);
void Mess_Message__FPCcP12SMessageProgbss(char*,char*,int,int,int);
void FUN_8006e2fc(int a){
  DAT_800d1e5c=40;
  FUN_80010724(DAT_800d1e28,a);
  switch(a){
    case 2:
      Mess_Message__FPCcP12SMessageProgbss(DAT_800a5d7c[0],DAT_800a6070,1,0,0);
      break;
    case 0:
      FUN_8004b250(19,0x2000,0);
      Mess_Message__FPCcP12SMessageProgbss(DAT_800a5d80[0],DAT_800a6070,1,0,0);
      break;
    case 4:
      FUN_8004b250(19,0x2000,0);
      Mess_Message__FPCcP12SMessageProgbss(DAT_800a5d84[0],DAT_800a6070,1,0,0);
      break;
    case 1:
      FUN_8004b250(19,0x2000,0);
      FUN_8008b900(DAT_800d3868,DAT_800a5d88[0],DAT_800a5398[DAT_800d1e28].f38);
      Mess_Message__FPCcP12SMessageProgbss(DAT_800d3868,DAT_800a6070,1,0,0);
      break;
    case 3:
      FUN_8004b250(159,0x2000,0);
      Mess_Message__FPCcP12SMessageProgbss(DAT_800a5d8c[0],DAT_800a6070,1,0,0);
      break;
  }
}
