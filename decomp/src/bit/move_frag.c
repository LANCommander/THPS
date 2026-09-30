/* Move__5CFrag (0x80029c8c) */
typedef struct{
  char _0[8]; unsigned short life; unsigned short maxlife; char _c[0xc];
  int px,py,pz; int vx,vy,vz; int ax,ay,az; char _3c[0];
  unsigned char sx, sy, sz; unsigned char _3f; char _40[0x59-0x40]; unsigned char max; signed char cnt;
}Frag;
void FUN_80027e18(Frag*);
void Move__5CFrag(Frag* t){
  t->px += t->vx;
  t->py += t->vy;
  t->pz += t->vz;
  t->vx += t->ax;
  t->vy += t->ay;
  t->vz += t->az;
  t->vx -= t->vx >> t->sx;
  t->vy -= t->vy >> t->sy;
  t->vz -= t->vz >> t->sz;
  t->cnt++;
  if (t->cnt >= t->max) t->cnt = t->max - 1;
  t->life++;
  if ((short)t->life >= t->maxlife) FUN_80027e18(t);
}
