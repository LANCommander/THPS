/* Pack_Init640x480__Fv (0x800497d4) */
int DAT_800d1a60,DAT_800d1a64,DAT_800d1a68,DAT_800d1a74,DAT_800d1a78;
void*Pack_NewFree__Fiiii(int,int,int,int);
void Pack_Init640x480__Fv(void){
  DAT_800d1a68=0;
  DAT_800d1a74=640;
  DAT_800d1a60=0;
  DAT_800d1a64=0;
  Pack_NewFree__Fiiii(640,256,384,256);
  Pack_NewFree__Fiiii(640,0,384,256);
  DAT_800d1a78=1;
}
