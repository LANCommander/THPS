/* Mess_GetFontScale__Fv (0x8001f22c) */
typedef struct{char pad[0x1a];unsigned short scale;char pad2[8];}Font;
unsigned char DAT_800d1602;
int DAT_800d15e4;
extern Font DAT_800a6110[];
int Mess_GetFontScale(void){
  if(!DAT_800d1602) return 0;
  return (DAT_800d15e4+DAT_800a6110)->scale;
}
