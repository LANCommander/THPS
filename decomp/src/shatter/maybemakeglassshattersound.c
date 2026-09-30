/* Shatter_MaybeMakeGlassShatterSound__Fv (0x80022440) */
int DAT_800d1628;
extern int DAT_800d1e28;
void FUN_8004b250(int,int,int);
void Shatter_MaybeMakeGlassShatterSound(void){
  int s;
  if (DAT_800d1628) {
    if (DAT_800d1e28 == 1) s = 0x3a; else { s = 0x3a; if (DAT_800d1e28 != 4) s = 0x2a; }
    FUN_8004b250(s, 0x2000, 0);
  }
  DAT_800d1628 = 0;
}
