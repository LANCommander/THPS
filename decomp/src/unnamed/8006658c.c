/* FUN_8006658c (0x8006658c) */
extern char DAT_800a21c0[];int DAT_800d2368;int DAT_800d1dc4;
void Mess_SetCurrentFont__FPc(char*p);void Mess_SetRGB__FUcUcUci(unsigned char r,unsigned char g,unsigned char b,int a);void Mess_SetFontScale__FUi(unsigned a);void FUN_8001d250(int a);void FUN_8001f1b4(int a);void FUN_80066d7c(void);
int FUN_8006658c(int a){DAT_800d2368=a;Mess_SetCurrentFont__FPc(DAT_800a21c0);Mess_SetRGB__FUcUcUci(128,128,128,0);Mess_SetFontScale__FUi(256);FUN_8001d250(1);FUN_8001f1b4(4);FUN_80066d7c();return DAT_800d1dc4;}
