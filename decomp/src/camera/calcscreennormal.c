/* CalcScreenNormal__FP11SCalcBufferRiT1i (0x8002dad8) */
typedef struct{short x0,y0; char _4[0x14]; int f18; short x1c,y1e; char _20[0x14]; int f34;}SCalcBuffer;
void CalcScreenNormal(SCalcBuffer* b, int* nx, int* ny, int minlen){
  int dx, dy, t, a, len;
  if (b->f18 || b->f34) { *ny = 0; *nx = 0; return; }
  dx = b->x1c - b->x0;
  dy = b->y1e - b->y0;
  t = (dx * 320) / 512;
  *nx = dy;
  *ny = -t;
  if (t < 0) t = -t;
  a = dy;
  if (a < 0) a = -a;
  if (a < t) len = t + a / 2; else len = a + t / 2;
  if (len >= minlen) {
    *nx = (*nx << 6) / len;
    *ny = (*ny << 6) / len;
    *nx = (*nx << 9) / 10;
    return;
  }
  *ny = 0; *nx = 0;
}
