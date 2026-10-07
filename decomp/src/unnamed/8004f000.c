/* FUN_8004f000 (0x8004f000) */
/* EXP module. 146/147: the only residue is the zero return after FUN_8004eed8: cse follows the
   single-use `goto out` and folds `return ret` to `v0 = 0`, which reorg copies into the `beq`
   slot (retail: nop). Giving `out` a second user (`if(!s0){ret=1;goto out;}`, retail's
   `j; li v0,1` shape) fixes that but then reorg fills the final `beq s1,zero` slot from the
   target (`v0 = 3`) instead of the fall-through (142/147). FUN_8006eb18 takes one argument;
   FUN_8004b250 returns int. */
typedef struct N{char p0[4];int f4;unsigned short s8;unsigned char cA,cB;unsigned short sC;char p1[2];struct N*f10;void*f14;}N;
typedef struct B{unsigned short f0;char p0[0x20-2];int f20;char p1[0x1d4-0x24];struct B*f1d4;char p2[0x1f0-0x1d8];int f1f0;int f1f4;char p3[0x924-0x1f8];int f924;}B;
N* DAT_800d1b70;
extern B* DAT_800d17c8;
extern int DAT_800d16a4;
int DAT_800d1b8c,DAT_800d1b90;
int FUN_8006ef00(B*);
int FUN_8004eed8(unsigned short);
int FUN_8004b250(int,short,int);
void FUN_8006eb18(int*);
void FUN_80068f40(int,int);
unsigned short* Trig_GetLinksPointer__Fi(unsigned short);
void Trig_SendPulse__FPUs(unsigned short*);
int FUN_8004f000(B*a,B*b,int c){
  unsigned char s5;
  int s3,s1,v,ret;
  N*s0;
  s5=2;
  if(b==DAT_800d17c8) s5=1;
  v=FUN_8006ef00(a);
  s3=0;
  s0=DAT_800d1b70;
  while(s0&&s0->f4!=v){
    s0=s0->f10;
    s3++;
  }
  if(!s0) return 1;
  if(c==-1){
    ret=FUN_8004eed8(s0->s8);
    if(!ret) goto out;
  }
  if(s0->cA){
    if(DAT_800d16a4!=8) return 3;
    if(s0->cB==s5) return 3;
  }
  s1=0;
  if(FUN_8004eed8(s0->s8)){
    if(DAT_800d16a4==1){
      FUN_8004b250(20,0x2000,0);
      a->f20=0x202020;
      s1=1;
      a->f0|=0x400;
      goto L122;
    }
  }
  if(DAT_800d16a4==8&&c>=s0->sC){
    s0->sC=c;
    a->f20=0x202020;
    a->f0|=0x400;
    b->f1f0++;
    FUN_8004b250(24,0x2000,0);
    if(s0->cA){
      b->f1d4->f1f0--;
      b->f1f4++;
      FUN_8006eb18(&b->f924);
      FUN_8004b250(25,0x2000,0);
    }
    s0->cB=s5;
    s1=1;
  }
L122:
  if(s1){
    DAT_800d1b8c=s5;
    DAT_800d1b90=c;
    FUN_80068f40(s5,s3);
    Trig_SendPulse__FPUs(Trig_GetLinksPointer__Fi(s0->s8));
    s0->cA=1;
    s0->f14=a;
  }
  return 3;
out:
  return ret;
}
