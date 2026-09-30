/* Pad_ClearAllOne__Fi (0x80070960) */
extern char DAT_800c0a48[];
extern void Pad_Clear__FP8SControl(char*);
void Pad_ClearAllOne(int i){
  int o = i * 0x16c;
  char* p = DAT_800c0a48 + o;
  Pad_Clear__FP8SControl(p);
  *(int*)(DAT_800c0a48 + o + 0x150) = 0;
  p[0x14b] = 0;
  p[0x14a] = 0;
  p[0x149] = 0;
  p[0x148] = 0;
}
