/* Move__15CSmokeGenerator (0x80027450) */
typedef struct{ int x,y,z; }V;
typedef struct{
  char _0[8]; unsigned short life; unsigned short maxlife; char _c[0xc];
  char pos[0x30]; int count; char _4c[0]; 
}S;
int Redbook_Rnd__Fi(int n);
char* FUN_80027d08(int n);
char* FUN_80029a0c(char*, char*, V*, char*, int, int, int);
void SetTint__7CFT4BitUcUcUc(char*, int, int, int);
void FUN_80027e18(void*);
extern char DAT_800d1860[];
void Move__15CSmokeGenerator(char* t){
  int i;
  char* o;
  V v; short c = 100;
  v.x = 0; v.y = 0; v.z = 0;
  for (i = 0; i < *(int*)(t+0x48); i++) {
    v.y = -(*(int*)(t+0x50) + Redbook_Rnd__Fi(*(int*)(t+0x54))) << 12;
    o = FUN_80027d08(0x70);
    if (o) {
      int r = Redbook_Rnd__Fi(*(int*)(t+0x5c));
      o = FUN_80029a0c(o, t+0x18, &v, DAT_800d1860, *(int*)(t+0x58) + r, 0, 10);
    }
    *(short*)(o+0x40) = c;
    *(short*)(o+0x60) = Redbook_Rnd__Fi(4096);
    SetTint__7CFT4BitUcUcUc(o, *(unsigned char*)(t+0x4c), *(unsigned char*)(t+0x4d), *(unsigned char*)(t+0x4e));
  }
  {
    S* s = (S*)t;
    s->life++;
    if ((short)s->life == s->maxlife && s->life != 0xffff) FUN_80027e18(t);
  }
}
