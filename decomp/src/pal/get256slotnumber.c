/* Get256SlotNumber__FUs (0x8004ae50) */
int DAT_800d1a8c,DAT_800d1a90;
unsigned short FUN_8008f70c(int,int);
int Get256SlotNumber__FUs(unsigned short clut){
  int i;
  for(i=0;i<75;i++)
    if(FUN_8008f70c(DAT_800d1a8c,DAT_800d1a90+i)==clut)break;
  return i;
}
