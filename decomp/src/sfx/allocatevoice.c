/* allocateVoice__Fv (0x8004bef4) */
unsigned DAT_800d1abc;
int allocateVoice(void){
  int i;
  for(i=0;i<24;i++){
    if(DAT_800d1abc&(1<<i)) return i;
  }
  return -1;
}
