/* Front_PrintDemo__Fv (0x800160bc) */
int DAT_800d13ec;
extern int DAT_800d1780;
extern char DAT_8009e2e0[];
void FUN_8001d250(int);
void Mess_SetScale__Fi(int);
void Mess_SetRGB__FUcUcUci(unsigned char, unsigned char, unsigned char, int);
void FUN_8001e114(int, int, const char*, int, int, int, int);
void Front_PrintDemo(void){
  if (--DAT_800d13ec == 0) DAT_800d13ec = 48;
  if (DAT_800d13ec >= 13) {
    if (DAT_800d1780 == 2) {
      FUN_8001d250(0);
      Mess_SetScale__Fi(255);
      Mess_SetRGB__FUcUcUci(150, 100, 25, 0);
      FUN_8001e114(128, 35, DAT_8009e2e0, 1, 0, 256, 0);
      FUN_8001e114(384, 35, DAT_8009e2e0, 1, 0, 256, 0);
    } else {
      FUN_8001d250(0);
      Mess_SetScale__Fi(255);
      Mess_SetRGB__FUcUcUci(150, 100, 25, 0);
      FUN_8001e114(256, 35, DAT_8009e2e0, 1, 0, 256, 0);
    }
  }
}
