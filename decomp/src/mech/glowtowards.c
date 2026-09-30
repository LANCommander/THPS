/* GlowTowards__Fiii (0x80042474) */
int GlowTowards__Fiii(int a, int b, int s){
  if (a < b) {
    if (a + s > b) return b;
    return a + s;
  }
  if (a - s < b) return b;
  return a - s;
}
