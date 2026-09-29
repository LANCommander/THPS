extern unsigned char DAT_800c0b9c[];
extern unsigned short DAT_800c0ba0[];
void f(unsigned char a, unsigned char b){
  DAT_800c0b9c[(a&0xff)*0x16c + (b&0xff)] = 0;
  DAT_800c0ba0[(a&0xff)*0xb6 + (b&0xff)] = 0;
}
