/* Free16Slot__FUs (0x8004ad38) */
extern unsigned char DAT_800d2a10[];
int DAT_800d1a84,DAT_800d1a88;
unsigned short FUN_8008f70c(int,int);
void Free16Slot__FUs(unsigned short clut){
  int i;
  for(i=0;i<256;i++)
    if(FUN_8008f70c(DAT_800d1a84,DAT_800d1a88+i)==clut)break;
  DAT_800d2a10[i]=1;
}
