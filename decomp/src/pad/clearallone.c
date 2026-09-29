extern int DAT_800c0a48[];
extern void Pad_Clear(int*);
void f(int i){
  int o = i*0x16c;
  Pad_Clear(DAT_800c0a48 + i*0x5b);
  *(int*)((char*)DAT_800c0a48 + o + 0x150) = 0;
  ((char*)DAT_800c0a48)[o + 0x14b] = 0;
  ((char*)DAT_800c0a48)[o + 0x14a] = 0;
  ((char*)DAT_800c0a48)[o + 0x149] = 0;
  ((char*)DAT_800c0a48)[o + 0x148] = 0;
}
