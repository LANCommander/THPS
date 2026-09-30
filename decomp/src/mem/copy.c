/* Mem_Copy__FPvT0i (0x8004d8b4) */
void Mem_Copy__FPvT0i(int*d,int*s,int n){
  int w=n>>2;
  char*dc,*sc;
  n&=3;
  while(w>0){
    *d++=*s++;
    w--;
  }
  dc=(char*)d;sc=(char*)s;
  while(n>0){
    *dc++=*sc++;
    n--;
  }
}
