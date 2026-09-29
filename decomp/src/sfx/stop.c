unsigned DAT_800d1aa4,DAT_800d1ab8,DAT_800d1ab0,DAT_800d1aa8,DAT_800d1aac;
void SFX_Stop(unsigned m){
  unsigned inv = ~m;
  DAT_800d1aa4 &= inv; DAT_800d1ab8 &= inv; DAT_800d1ab0 &= inv; DAT_800d1aa8 &= inv;
  DAT_800d1aac |= m;
}
