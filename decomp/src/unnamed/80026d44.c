/* FUN_80026d44 (0x80026d44) */
extern volatile unsigned char DAT_800c0a48[];
int DAT_800d1780;
void FUN_80092044(void);
void Options_Init__Fv(void);
void FUN_80010000(void);
void FUN_80071f84(int);
void Init_Restart__F13EPackInitTypei(int,int);
void FUN_800491e8(void);
void FUN_80070ff4(void);
void FUN_80022c1c(int);
void FUN_8006b01c(int);
void FUN_8006b3f8(void);
int FUN_80026d44(void){
  volatile unsigned char*p;
  FUN_80092044();
  Options_Init__Fv();
  FUN_80010000();
  FUN_80071f84(1);
  Init_Restart__F13EPackInitTypei(0,16);
  FUN_800491e8();
  FUN_80070ff4();
  p=DAT_800c0a48;
  if(p[224]==0&&(p[64]==0||p[80]==0))FUN_80022c1c(-1);
  FUN_80070ff4();
  p=DAT_800c0a48;
  if(p[224]==0&&(p[64]==0||p[80]==0))FUN_80022c1c(-2);
  FUN_80070ff4();
  p=DAT_800c0a48;
  if(p[224]==0&&(p[64]==0||p[80]==0))FUN_80022c1c(-25);
  Init_Restart__F13EPackInitTypei(0,16);
  FUN_800491e8();
  DAT_800d1780=1;
  Init_Restart__F13EPackInitTypei(1,16);
  FUN_8006b01c(1);
  FUN_8006b3f8();
  return 0;
}
