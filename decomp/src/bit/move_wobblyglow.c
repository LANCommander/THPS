/* Move__11CWobblyGlow (0x80029270) */
typedef struct{int a,b;}E;
extern short DAT_800c9670[] __attribute__((section(".data")));
void Move__11CWobblyGlow(char* t){
  unsigned i;
  for (i = 0; i < *(unsigned*)(t+0x50); i++) {
    ((int*)(t+0x88))[i] += ((int*)(t+0x68))[i];
    (*(E**)(t+0x48))[i].a = *(int*)(t+0xac) + *(int*)(t+0xa8) * DAT_800c9670[(((int*)(t+0x88))[i] & 0xfff)*2] / 4096;
  }
}
