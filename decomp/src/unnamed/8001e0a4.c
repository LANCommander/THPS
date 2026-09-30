/* FUN_8001e0a4 (0x8001e0a4) */
int DAT_800d15e8;
void Mess_SetScale__Fi(int a);void Mess_SetRGB__FUcUcUci(unsigned char r,unsigned char g,unsigned char b,int a);
void FUN_8001e0a4(char*p,int f){if(f){Mess_SetScale__Fi(*(unsigned short*)(p+68));Mess_SetRGB__FUcUcUci(255,48,48,0);DAT_800d15e8=(int)p;}else DAT_800d15e8=0;}
