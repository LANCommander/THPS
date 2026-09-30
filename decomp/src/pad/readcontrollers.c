/* ReadControllers__Fv (0x80070d10) */
extern char DAT_800c0d64[], DAT_800c0d20[];
void ReadController__FP14ControllerDataPUc(char*, char*);
void ReadControllers__Fv(void){
  int i;
  for (i = 0; i < 2; i++) {
    if ((unsigned char)DAT_800c0d20[i * 34 + 1] == 0x80) {
      ReadController__FP14ControllerDataPUc(DAT_800c0d64 + i * 32, DAT_800c0d20 + 2 + i * 34);
      ReadController__FP14ControllerDataPUc(DAT_800c0d64 + 8 + i * 32, DAT_800c0d20 + 10 + i * 34);
      ReadController__FP14ControllerDataPUc(DAT_800c0d64 + 16 + i * 32, DAT_800c0d20 + 18 + i * 34);
      ReadController__FP14ControllerDataPUc(DAT_800c0d64 + 24 + i * 32, DAT_800c0d20 + 26 + i * 34);
    } else {
      ReadController__FP14ControllerDataPUc(DAT_800c0d64 + i * 32, DAT_800c0d20 + i * 34);
      DAT_800c0d64[9 + i * 32] = 0;
      DAT_800c0d64[17 + i * 32] = 0;
      DAT_800c0d64[25 + i * 32] = 0;
    }
  }
}
