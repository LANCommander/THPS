/* Competition_NewHeat__Fv (0x800764a4) */
typedef struct { int pad[4]; int a, b, c, pad2, d, e; char pad3[0xc0 - 0x28]; unsigned char heat; } SComp;
extern SComp DAT_800c0fdc;
int Competition_NewHeat(void){
  DAT_800c0fdc.b = 0;
  DAT_800c0fdc.a = 0;
  DAT_800c0fdc.c = 0;
  DAT_800c0fdc.d = 0;
  DAT_800c0fdc.e = 0;
  return ++DAT_800c0fdc.heat < 3;
}
