/* FUN_800444bc (0x800444bc) */
typedef struct{int x,y,z;}V;
struct VT{char pad[8];short off;short pad2;void(*fn)(char*,int);};
typedef struct O{char p0[4];V pos;char p1[0x1c-0x10];struct O*next;char p2[0x48-0x20];struct VT*vt;char p3[0x52-0x4c];unsigned short f52;char p4[0xe8-0x54];unsigned fe8;}O;
typedef struct{char p[4];V pos;char q[0x1c-0x10];O*f1c;}P;
extern P* DAT_800d19a4;
extern int DAT_800d1780;
unsigned DAT_800d19c0;
void FlashUpdate__5CItem(O*);
void FUN_80043a14(O*,O**);
void FUN_800440ec(O*);
void UpdateShadow__5CBody(O*);
unsigned Utils_CrapDist__FRC7CVectorT0(V*,V*);
void FUN_800444bc(O**a){
  O*m;O*n;V*v;unsigned d,t;
  m=*a;
  if(!m) return;
  n=m->next;
  for(;;){
    FlashUpdate__5CItem(m);
    if(m->f52&0x40){
      if(m->f52&0x80){
        if(m) m->vt->fn((char*)m+m->vt->off,3);
      }else m->f52=m->f52|0x80;
    }else{
      v=&m->pos;
      d=Utils_CrapDist__FRC7CVectorT0(&DAT_800d19a4->pos,v);
      if(DAT_800d1780==2){
        t=Utils_CrapDist__FRC7CVectorT0(&DAT_800d19a4->f1c->pos,v);
        if(t<d) d=t;
      }
      m->fe8=d;
      if((m->f52&2)&&DAT_800d19c0<d){
        FUN_80043a14(m,a);
      }else{
        FUN_800440ec(m);
        UpdateShadow__5CBody(m);
      }
    }
    m=n;
    if(n) n=n->next; else break;
  }
}
