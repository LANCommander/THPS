/* Font_String__FUsUsPcUcUcUcUc (0x8004c1a8) */
typedef struct{int a;short x,y;char*s;int col;unsigned char z,w;char pad[14];}SFont;
SFont*DAT_800d1aec;
int DAT_800d1ae0;
void Font_String__FUsUsPcUcUcUcUc(unsigned short x,unsigned short y,char*s,unsigned char c0,unsigned char c1,unsigned char c2,unsigned char c3){
  SFont*p=DAT_800d1aec;
  p->z=0;
  p->a=0;
  p->x=x;
  p->y=y;
  DAT_800d1aec->w=c3;
  DAT_800d1aec->col=DAT_800d1ae0|(c2<<16)|(c1<<8)|c0;
  DAT_800d1aec->s=s;
  DAT_800d1aec++;
  DAT_800d1aec->a=1;
}
