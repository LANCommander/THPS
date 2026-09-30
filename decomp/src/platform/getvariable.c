/* GetVariable__9CPlatformUs (0x8003f624) */
int FUN_80040f50(char*, unsigned short);
int GetVariable__9CPlatformUs(char* t, unsigned short v){
  if (v == 0x2200) return *(short*)(t+0x240);
  return FUN_80040f50(t, v);
}
