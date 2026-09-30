/* SquirtPos__5CBodyPs (0x800439ac) */
typedef struct{int x,y,z;}V;
short* SquirtPos__5CBodyPs(char* t, short* p){
  V* v = (V*)p;
  *(int*)(t+0x4) = *(int*)(t+0xfc) = v->x << 12;
  *(int*)(t+0x8) = *(int*)(t+0x100) = v->y << 12;
  *(int*)(t+0xc) = *(int*)(t+0x104) = v->z << 12;
  return (short*)(v+1);
}
