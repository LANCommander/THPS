/* FUN_8001da44 (0x8001da44) */
typedef struct E{char p0[0x14];struct E*f14;char p1[2];unsigned short f1a;int f1c;int f20;}E;
extern E DAT_800a6110[];
int DAT_800d15e4;
unsigned char DAT_800d1602;
int FUN_8001d340(void);
int FUN_8001ddfc(int);
int FUN_8001da44(unsigned char*s0){
  int n,idx;unsigned char*s;
  if(DAT_800d1602==0) return FUN_8001d340();
  s=s0;
  n=0;
  if(*s){
    do{
      idx=FUN_8001ddfc(*s);
      if((unsigned)(idx-250)>=5){
        if(idx==255){
          n+=((DAT_800a6110[DAT_800d15e4].f20+DAT_800a6110[DAT_800d15e4].f1c)*DAT_800a6110[DAT_800d15e4].f1a)>>8;
        }else{
          n+=(((DAT_800a6110[DAT_800d15e4].f14+idx)->f20+DAT_800a6110[DAT_800d15e4].f1c)*DAT_800a6110[DAT_800d15e4].f1a)>>8;
        }
      }
      s++;
    }while(*s);
  }
  return n;
}
