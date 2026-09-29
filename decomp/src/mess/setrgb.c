unsigned DAT_800d15f4;
void f(unsigned r, unsigned g, unsigned b, int flag){
  unsigned rr=r&0xff, gg=g&0xff, bb=b&0xff;
  unsigned c = (bb<<16) | (gg<<8) | rr;
  DAT_800d15f4 = c;
  DAT_800d15f4 = c | (flag ? 0x2e000000u : 0x2c000000u);
}
