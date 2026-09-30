/* IncFrameWithWrap__7CFT4Bit (0x800281c0) */
extern int DAT_800d1774 __attribute__((section(".data")));
typedef struct{char p[0x50]; char* base; char* cur; char pad; unsigned char n; signed char f; unsigned char sf; short speed;}B;
void IncFrameWithWrap__7CFT4Bit(B* t){
  short v = (t->f<<8) | t->sf;
  v += (t->speed * DAT_800d1774) >> 8;
  t->f = v >> 8;
  t->sf = v;
  if (t->f >= t->n) t->f = 0;
  t->cur = t->base + t->f*8;
}
