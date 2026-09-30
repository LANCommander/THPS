/* Panel_ReplayInstructions__Fv (0x8006d858) */
extern int DAT_800bf318[];
extern int DAT_800d1cb0;
extern int DAT_800d13e8;
extern const char *DAT_800a5ed4[];
void Mess_SetRGB__FUcUcUci(unsigned char, unsigned char, unsigned char, int);
void Mess_SetScale__Fi(int);
void FUN_8001d250(int);
int Mess_DrawPanelText__FiiPCciUii(int, int, const char*, int, unsigned, int);
void Panel_ReplayInstructions(void){
  if (DAT_800bf318[0] == 2 && DAT_800d1cb0 && DAT_800d13e8 != 20 && DAT_800d13e8 != 22 && DAT_800d13e8 != 21) {
    int m = DAT_800bf318[19];
    if ((m == 0 && (unsigned)(DAT_800bf318[7] - DAT_800bf318[8]) < 90) || m == 1) {
      Mess_SetRGB__FUcUcUci(128, 128, 128, 0);
      Mess_SetScale__Fi(188);
      FUN_8001d250(0);
      Mess_DrawPanelText__FiiPCciUii(256, 220, DAT_800a5ed4[0], 0, 0, 256);
    }
  }
}
