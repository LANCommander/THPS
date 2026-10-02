/* FUN_80065fec (0x80065fec) */
typedef struct { void *a; int p4[5]; int f18; int sz; int f20; } E;
typedef struct { int p0[2]; int n; int pc; E e[1]; } S;
extern int FUN_8004d3a4(int a);
extern int FUN_8004d068(int a,int b,int c);
extern int FUN_8004d5d0(void *a);
extern int Mem_Copy__FPvT0i(void *a,void *b,int c);
void FUN_80065fec(S *s){
  int tmp[32];
  int i;
  for(i=0;i<s->n;i++){
    if(s->e[i].f20 && !s->e[i].f18){
      tmp[i]=FUN_8004d3a4(s->e[i].sz);
      Mem_Copy__FPvT0i((void*)tmp[i],s->e[i].a,s->e[i].sz);
      FUN_8004d5d0(s->e[i].a);
    }
  }
  for(i=0;i<s->n;i++){
    if(s->e[i].f20 && !s->e[i].f18){
      s->e[i].a=(void*)FUN_8004d068(s->e[i].sz,1,1);
      Mem_Copy__FPvT0i(s->e[i].a,(void*)tmp[i],s->e[i].sz);
      FUN_8004d5d0((void*)tmp[i]);
    }
  }
}
