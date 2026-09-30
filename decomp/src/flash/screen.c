/* Flash_Screen__FUcUcUciUci (0x8001f334) */
int DAT_800d160c,DAT_800d1608,DAT_800d2208,DAT_800d220c,DAT_800d2210,DAT_800d2214,DAT_800d2218,DAT_800d221c;
unsigned char DAT_800d1604;
void Flash_Screen__FUcUcUciUci(unsigned char r,unsigned char g,unsigned char b,int n,unsigned char c,int d){
  if(c>=DAT_800d1604&&n!=0){
    unsigned R=r<<16,G=g<<16,B=b<<16;
    unsigned nn=n;
    DAT_800d2208=R;
    DAT_800d220c=G;
    DAT_800d2210=B;
    DAT_800d160c=n;
    DAT_800d1604=c;
    DAT_800d1608=d;
    DAT_800d2214=R/nn;
    DAT_800d2218=G/nn;
    DAT_800d221c=B/nn;
  }
}
