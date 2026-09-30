/* CycleAnim__6CSuperiSc (0x80043f24) */
typedef struct{char p[0x18]; char* anims; char q[0x40-0x1c];}R;
extern R DAT_800bf7a8[] __attribute__((section(".data")));
void CycleAnim__6CSuperiSc(char* t, int a, signed char c){
  unsigned char k;
  *(unsigned short*)(t+0x146) = a;
  k = DAT_800bf7a8[(unsigned char)t[0x1b]].anims[*(unsigned short*)(t+0x146)*8 + 8];
  t[0x148] = 1;
  t[0x149] = c;
  *(short*)(t+0x144) = 0;
  *(short*)(t+0x14c) = 0;
  t[0x14f] = 0;
  t[0x14e] = k;
}
