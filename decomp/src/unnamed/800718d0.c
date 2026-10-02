/* FUN_800718d0 (0x800718d0) */
extern unsigned char DAT_800c0a48[];
int FUN_800718d0(void){
  int i;
  for(i=0;i<2;i++){
    if(DAT_800c0a48[i*364+0x1]||DAT_800c0a48[i*364+0x11]||DAT_800c0a48[i*364+0x41]||DAT_800c0a48[i*364+0x51]||DAT_800c0a48[i*364+0x61]||DAT_800c0a48[i*364+0x71]||DAT_800c0a48[i*364+0x81]||DAT_800c0a48[i*364+0x91]||DAT_800c0a48[i*364+0xa1]||DAT_800c0a48[i*364+0xb1]||DAT_800c0a48[i*364+0x21]||DAT_800c0a48[i*364+0xf1]) return 1;
  }
  return i<2;
}
