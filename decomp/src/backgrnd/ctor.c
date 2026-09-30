/* __11CBackgroundUiRC8CSVector (0x80078188) */
extern char DAT_800a3494[];
extern char* DAT_800d19f0 __attribute__((section(".data")));
char* DAT_800d1fe4;
unsigned short DAT_800d1fe8;
void FUN_800437d4(char*, unsigned, void*);
void InitItem__5CItemPc(char*, char*);
int Spool_GetModel__FUii(unsigned, int);
void FUN_800438dc(char*, void*);
char* __11CBackgroundUiRC8CSVector(char* t, unsigned model, void* v){
  char* nm;
  FUN_800437d4(t, model, v);
  nm = DAT_800d19f0;
  *(char**)(t+0x48) = DAT_800a3494;
  InitItem__5CItemPc(t, nm);
  *(short*)(t+0x16) = Spool_GetModel__FUii(model, (unsigned char)t[0x1b]);
  *(unsigned short*)t &= ~2;
  *(unsigned short*)(t+0x52) &= ~6;
  FUN_800438dc(t, &DAT_800d1fe4);
  { unsigned short id = DAT_800d1fe8; *(unsigned short*)(t+0x134) = id; DAT_800d1fe8 = id + 1; }
  return t;
}
