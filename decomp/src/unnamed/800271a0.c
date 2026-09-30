/* FUN_800271a0 (0x800271a0) */
extern char DAT_8009f670[];extern int DAT_800d18f4;
void FUN_8004d5d0(int a);void DeleteFrom__4CBitPv(char*p,int*q);int BASEF(char*p,int a);void FUN_80027d70(void*p);
void FUN_800271a0(char*p,int f){*(char**)(p+68)=DAT_8009f670;FUN_8004d5d0(*(int*)(p+80));DeleteFrom__4CBitPv(p,&DAT_800d18f4);BASEF(p,0);if(f&1)FUN_80027d70(p);}
