/* FUN_8004169c (0x8004169c) */
typedef struct{int x,y,z;}V;
typedef struct{char p[8];short off;short pad;void(*fn)(void*,int);}VT;
typedef struct{V v;char c,d,e;}Q;
typedef struct{char p0[0x42];char f42;char p1;VT*vt;char p2[0x4c-0x48];Q*f4c;V f50;unsigned char f5c,f5d,f5e;}O;
typedef struct{char p0[4];V pos;int f10;char p1[0x1ac-0x14];int f1ac;unsigned short*f1b0;char p2[0x220-0x1b4];unsigned short f220;char p3;char p4;char*f224;O*f228;unsigned f22c;int f230;int f234;}S;
extern int DAT_800d1acc;
typedef struct{int pad;V pos;}OB;
extern OB* DAT_800d19a4;
extern int DAT_800d186c;
extern char* DAT_800d2044;
void SFX_Stop__FUi(unsigned);
unsigned FUN_8004b250(unsigned short,int,int);
unsigned FUN_8004b464(unsigned short,void*,int,unsigned short);
O* FUN_80027d08(int);
O* FUN_8002725c(O*,int);
unsigned short FUN_80040c68(S*);
char* FUN_8004d068(int,int,int);
int Redbook_Rnd__Fi(int);
void SetSemiTransparent__10CGPolyLine(O*,Q*);
O* __9CSmokeJetRC7CVectorRC8CSVectoriUsiiiiUcUi(O*,V*,int*,int,unsigned short,int,int,int,int,int,unsigned);
void __apl__7CVectorRC7CVector(V*,V*);
void __mi__FRC7CVectorT0(V*,V*,char*);
void __pl__FRC7CVectorT0(V*,V*,V*);
void __rs__FRC7CVectorRCi(V*,char*,int*);
int FUN_8003fcdc(S*,int);
static inline void VI(V*p,int x,int y,int z){p->x=x;p->y=y;p->z=z;}
int FUN_8004169c(S*p,unsigned short a1){
  switch(a1){
  case 0x4507:{unsigned a;
    a=p->f22c;
    if(a)SFX_Stop__FUi(a);
    p->f22c=FUN_8004b250(*p->f1b0++,0x2000,0);
    p->f234=DAT_800d1acc;
    p->f230=-1;
    break;}
  case 0x4508:{unsigned a;
    a=p->f22c;
    if(a)SFX_Stop__FUi(a);
    {unsigned short x=*p->f1b0++;unsigned short y=*p->f1b0++;
    p->f230=y;
    p->f22c=FUN_8004b464(x,&p->pos,0,y);}
    p->f234=DAT_800d1acc;
    break;}
  case 0x4509:{unsigned a;
    a=p->f22c;
    if(a)SFX_Stop__FUi(a);
    p->f22c=0;
    break;}
  case 0x4506:
    if(DAT_800d19a4){
      p->pos=DAT_800d19a4->pos;
      break;
    }
    break;
  case 0x4700:
    if(*p->f1b0++)p->f1ac|=0x100;
    else p->f1ac&=~0x100;
    break;
  case 0x4504:
    p->f1b0=(unsigned short*)((char*)p->f1b0+8);
  case 0x429b:{O*o;
    o=FUN_80027d08(0x16c);
    if(o){
      unsigned short*t=p->f1b0;
      o=__9CSmokeJetRC7CVectorRC8CSVectoriUsiiiiUcUi(o,&p->pos,&p->f10,t[0],0xffff,t[1],t[2],t[3],t[4],((unsigned char*)t)[10],0xcce0187c);
    }
    p->f228=o;
    o->f42=1;
    p->f1b0=(unsigned short*)((char*)p->f1b0+12);
    break;}
  case 0x42a1:{O*o;
    o=FUN_80027d08(0x16c);
    if(o){
      unsigned short*t=p->f1b0;
      o=__9CSmokeJetRC7CVectorRC8CSVectoriUsiiiiUcUi(o,&p->pos,&p->f10,t[0],0xffff,t[1],t[2],t[3],t[4],((unsigned char*)t)[10],0x68b7b136);
    }
    p->f228=o;
    p->f1b0=(unsigned short*)((char*)p->f1b0+12);
    break;}
  case 0x429f:{O*o;
    o=p->f228;
    if(o){
      VT*vt=o->vt;
      vt->fn((char*)o+vt->off,3);
    }
    p->f228=0;
    break;}
  case 0x4503:{
    V c,v40,v50,v60,v70;int n;
    int i;V*e;char*ed;
    O*ob;Q*q;
    int s1,s0,s2;int k16;V*rp;
    p->f220=FUN_80040c68(p);
    p->f224=FUN_8004d068(p->f220*16,0,1);
    DAT_800d186c=0;
    c=DAT_800d19a4->pos;
    i=0;
    if(p->f220!=0){
      k16=16;
      rp=&v50;
      do{
        ed=p->f224+i*16;
        e=(V*)ed;
        VI(&v40,(Redbook_Rnd__Fi(2400)-1200)<<12,(Redbook_Rnd__Fi(400)-1200)<<12,(Redbook_Rnd__Fi(2400)-1200)<<12);
        __apl__7CVectorRC7CVector(&v40,&c);
        VI(e,(Redbook_Rnd__Fi(16)-8)<<12,(Redbook_Rnd__Fi(48)+48)<<12,(Redbook_Rnd__Fi(16)-8)<<12);
        ob=FUN_80027d08(100);
        if(ob)ob=FUN_8002725c(ob,1);
        *(O**)(ed+12)=ob;
        ob->f42=1;
        ob->f50=v40;
        q=ob->f4c;
        __mi__FRC7CVectorT0(&v60,&v40,ed);
        n=1;
        __rs__FRC7CVectorRCi(&v70,DAT_800d2044+0x6c,&n);
        __pl__FRC7CVectorT0(rp,&v60,&v70);
        q->v=v50;
        ob->f5c=0x40;ob->f5d=0x40;ob->f5e=0x50;
        ob->f4c->c=k16;
        ob->f4c->d=k16;
        {Q*t=ob->f4c;t->e=32;
        SetSemiTransparent__10CGPolyLine(ob,t);}
        i++;
      }while(i<p->f220);
    }
    DAT_800d186c=1;
    break;}
  default:
    return FUN_8003fcdc(p,a1);
  }
  return 1;
}
