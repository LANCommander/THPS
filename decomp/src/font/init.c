/* Font_Init__Fv (0x8004c14c) */
extern char DAT_800a1270[];
extern char DAT_800d1ae4[];
int DAT_800d1ad8,DAT_800d1adc;
int Spool_FindAnim__FPc(char*);
void Font_Init__Fv(void){
  DAT_800d1ad8=Spool_FindAnim__FPc(DAT_800a1270);
  DAT_800d1adc=Spool_FindAnim__FPc(DAT_800d1ae4);
}
