/* Horse_Reset__Fv (0x800162bc) */
int DAT_800d14f4;
extern int DAT_800d179c, DAT_800d17a0, DAT_800d17a4, DAT_800d17a8, DAT_800d17ac,
  DAT_800d17b0, DAT_800d17b4, DAT_800d17b8, DAT_800d16cc, DAT_800d17c0;
void Horse_Reset(void){
  DAT_800d14f4 = 0;
  DAT_800d179c = 0; DAT_800d17a0 = 0; DAT_800d17a4 = 0; DAT_800d17a8 = 0;
  DAT_800d17ac = 0; DAT_800d17b0 = 0; DAT_800d17b4 = 0; DAT_800d17b8 = 0;
  DAT_800d16cc = 0;
  DAT_800d17c0 = 1;
}
