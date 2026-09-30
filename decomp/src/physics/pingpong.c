/* PingPong__Fiii (0x8002eed8) -- near-miss: needs cc1 -mno-split-addresses + a nop after a dependent mfhi (see report) */
extern int DAT_800d1770[];
int PingPong(int lo,int hi,int speed){
  int t=DAT_800d1770[0]/(60/speed);
  int range=hi-lo;
  int r=t%(range*2);
  if(range<r) r=range*2-r;
  return lo+r;
}
