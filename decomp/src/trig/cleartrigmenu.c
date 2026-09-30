/* Trig_ClearTrigMenu__Fv (0x800447f4) */
extern int DAT_800a8828[];
int DAT_800d19f4;
void Trig_ClearTrigMenu(void){
  int i;
  for (i = 0; i < 40; i++) DAT_800a8828[i] = 0;
  DAT_800d19f4 = 0;
}
