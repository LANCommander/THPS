/* Front_PrintGoBack__Fv (0x800178e4) */
typedef struct { int pad[2]; } SAnimFrame;
SAnimFrame *DAT_800d1420;
extern const char *DAT_800a5ef0[];
void FUN_8001d250(int);
void Mess_SetScale__Fi(int);
void Mess_SetRGB__FUcUcUci(unsigned char, unsigned char, unsigned char, int);
void FUN_8001e114(int, int, const char*, int, int, int, int);
void *FUN_8006c4f0(SAnimFrame*);
void Panel_SetStretchedScreenCoords__FiiP8POLY_FT4P10SAnimFrame(int, int, void*, SAnimFrame*);
void Front_PrintGoBack(void){
  void *p;
  FUN_8001d250(1);
  Mess_SetScale__Fi(192);
  Mess_SetRGB__FUcUcUci(150, 100, 25, 0);
  FUN_8001e114(92, 214, DAT_800a5ef0[0], 0, 0, 256, 0);
  FUN_8001d250(0);
  p = FUN_8006c4f0(DAT_800d1420 + 1);
  if (p) Panel_SetStretchedScreenCoords__FiiP8POLY_FT4P10SAnimFrame(64, 211, p, DAT_800d1420 + 1);
}
