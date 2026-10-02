/* FUN_800565ac (0x800565ac) */
typedef struct{char p[0x13];unsigned char b13;signed char b14;char q[0x154-0x15];}E;
extern E DAT_800a44fc[];
int DAT_800d2304[2];
int DAT_800d231c[2];
extern int DAT_800d3758[];
extern int DAT_800d1724,DAT_800d2120,DAT_800d2130;
void FUN_80059618(int);
void FUN_8004982c(int,int,int,short*,short*,int,int,int);
void FUN_8006ed2c(int);
void FUN_8006f290(int);
void Pack_Unpack__Fss(short,short);
void FUN_800565ac(void){
  short ab[4];E*e;
  int i,n;
  FUN_80059618(0);
  n=2;
  if(DAT_800d2304[0]==DAT_800d2304[1]&&DAT_800d231c[0]&&DAT_800d231c[1]) n=1;
  for(i=0;i<n;i++){
    if(n==2){
      if(i==0) FUN_8004982c(0,128,256,&ab[0],&ab[2],16,0,0);
      else Pack_Unpack__Fss(ab[0],ab[2]);
    }
    if(DAT_800d231c[i]){
      FUN_8006ed2c(DAT_800d3758[DAT_800d2304[i]]);
      if(DAT_800d1724){
        e=DAT_800a44fc+DAT_800d2304[i];
        DAT_800d2130=e->b14;
        DAT_800d2120=e->b13;
      }
      FUN_8006f290(DAT_800d3758[DAT_800d2304[i]]);
      DAT_800d2120=-1;
    }
  }
}
