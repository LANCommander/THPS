/* M3dInit_SetFoggingParams__FiiUi (0x80082158) */
extern int DAT_800d2168 __attribute__((section(".data"))),DAT_800d216c __attribute__((section(".data"))),DAT_800d2170 __attribute__((section(".data")));
int DAT_800d2134,DAT_800d2138,DAT_800d213c;
void M3dInit_SetFoggingParams(int a,int nearz,unsigned range){
  DAT_800d216c=nearz;
  DAT_800d2168=nearz+range;
  DAT_800d2170=0;
  while(range<4096){ range<<=1; DAT_800d2170++; }
  while(range>4096){ range>>=1; DAT_800d2170--; }
  DAT_800d2134=DAT_800d2168;
  DAT_800d2138=DAT_800d216c;
  DAT_800d213c=DAT_800d2170;
}
