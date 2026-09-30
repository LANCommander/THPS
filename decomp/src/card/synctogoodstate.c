/* SyncToGoodState__Fv (0x80014424) */
int DAT_800d1394,DAT_800d1384,DAT_800d1390,DAT_800d1380;
void FUN_8008eebc(int);
int Card_CheckStatus__Fii(int,int);
int SyncToGoodState__Fv(void){
  int n=200;
  DAT_800d1394=0;
  DAT_800d1384=0;
  for(;;){
    FUN_8008eebc(0);
    Card_CheckStatus__Fii(0,0);
    if(DAT_800d1384==1)break;
    if(--n<0){
      DAT_800d1390=0;
      DAT_800d1380=0;
      return 1;
    }
  }
  DAT_800d1390=1;
  DAT_800d1380=1;
  return 0;
}
