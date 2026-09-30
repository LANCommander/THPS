/* FUN_80012600 (0x80012600) */
extern unsigned char DAT_800a42d0[];
int FUN_80012600(void){int i;for(i=0;i<10;i++){if(DAT_800a42d0[i]==0)return 1;if(DAT_800a42d0[i]!=32)return 0;}return 1;}
