/* Vibrate__6CBruceiii (0x8002f8f0) */
typedef struct{char _0[0x870];int pad;}CBruce;
struct S{int _[0x252];int v;};
extern int DAT_800d16a4 __attribute__((section(".data"))),DAT_800d179c __attribute__((section(".data")));
extern int DAT_800a6844[];
extern int DAT_800bf318[],DAT_800bf3d8[];
extern void Pad_ActuatorOn__FUcUsUcUc(unsigned char,unsigned short,unsigned char,unsigned char);
void Vibrate(CBruce*b,int a,int c,int d){
  int p=b->pad;
  if(DAT_800d16a4==7) p^=DAT_800d179c;
  { int* q = DAT_800a6844; int* r = q + 0x252; r = r + p; if (*r==0) return; }
  if(DAT_800bf318[0]==2) return;
  if(DAT_800bf3d8[0]==2) return;
  Pad_ActuatorOn__FUcUsUcUc(p,a,c,d);
}
