/* Mess_GetScale__Fv (0x8001d290) */
unsigned char DAT_800d1602;
unsigned short DAT_800d15f8;
extern int Mess_GetFontScale__Fv(void);
int Mess_GetScale(void){
  if(DAT_800d1602) return Mess_GetFontScale__Fv();
  return DAT_800d15f8;
}
