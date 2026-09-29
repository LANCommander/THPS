int DAT_800d2238, DAT_800d223c, DAT_800d2240;
int Rnd(int n){
  int s = DAT_800d2238 * DAT_800d223c + DAT_800d2240;
  DAT_800d2238 = s;
  DAT_800d223c = (DAT_800d223c ^ s) + (s >> 4);
  DAT_800d2240 = DAT_800d2240 - 0x10101010 + (s >> 3);
  return (int)((s & 0xffff) * n) >> 16;
}
