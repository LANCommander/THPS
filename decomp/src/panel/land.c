/* Land__10CPanelData (0x8006e8ec) */
/* PANEL.CPP, as C (demo twin). Banks a landed combo: sums the trick scores, applies the multiplier
   (combo length plus a level bonus), keeps the best combo's names, and ends the replay highlight. */
struct Q{char pad[0x32c];int lvl;};
typedef struct{int v;int pad[4];}E;
typedef struct{
  struct Q*q;int i4;char p0[2];unsigned short s0a;char p1[2];unsigned short s0e;unsigned m10;char b14[0x78-0x14];char b78[0xdc-0x78];char bdc[0x140-0xdc];
  int i140;int i144;int i148;char p2[0x154-0x14c];int i154;int i158;char p3[0x1fc-0x15c];E e[1];char p4[0x388-0x210];int n;char b38c[0x4f4-0x38c];int i4f4;
}B;
extern int DAT_800a71fc[];
extern int DAT_800d16a4;
int FUN_8008e904(char*,char*);
void Video_HighlightEnd__FP6CBrucei(struct Q*,int);
void FUN_8006e8ec(B*p){
  int i,a,t,m;unsigned u;
  p->i154=0;
  p->i158=0;
  if(p->n>0){
    p->i144=0;
    p->s0a=p->s0a+(unsigned short)p->n;
    for(i=0;i<p->n;i++)p->i144=p->i144+p->e[i].v;
    t=p->q->lvl;
    m=p->n*2;
    if(t<3)a=m+t;else a=m+(t*2-2);
    p->i148=a;
    u=(unsigned)(p->i144*a)>>1;
    p->i140=p->i140+u;
    if(p->m10<u){
      p->m10=u;
      p->s0e=p->n;
      FUN_8008e904((char*)p+0x14,(char*)p+0x38c);
      FUN_8008e904((char*)p+0x78,(char*)p+0x3f0);
      FUN_8008e904((char*)p+0xdc,(char*)p+0x454);
    }
    p->n=0;
    p->i4f4=40;
    if(DAT_800a71fc[0]==0)p->i4f4=0;
    if(DAT_800d16a4==2&&p->i144!=0)p->i4=0;
  }
  Video_HighlightEnd__FP6CBrucei(p->q,p->i140);
}
