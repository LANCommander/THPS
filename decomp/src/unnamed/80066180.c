/* FUN_80066180 (0x80066180) */
extern char DAT_800a2120[];extern char DAT_800a21b0[];
void FUN_8004d5d0(int a);void FUN_80024238(void*p);
void FUN_80066180(int*p,int f){int i;p[0]=(int)DAT_800a2120;for(i=0;i<16;i++){if(p[1+i])FUN_8004d5d0(p[1+i]);}p[0]=(int)DAT_800a21b0;if(f&1)FUN_80024238(p);}
