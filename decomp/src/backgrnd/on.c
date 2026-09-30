/* Backgrnd_On__FUs (0x800780f0) */
char* DAT_800d1fe4;
void Backgrnd_On__FUs(unsigned short id){
  char* p;
  for (p = DAT_800d1fe4; p; p = *(char**)(p+0x1c)) {
    if (*(unsigned short*)(p+0x134) == id) {
      *(unsigned short*)p &= ~1;
      return;
    }
  }
}
