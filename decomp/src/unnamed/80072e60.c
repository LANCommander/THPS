/* FUN_80072e60 (0x80072e60) */
extern char DAT_800a24a8[];
void FUN_80024238(void*p);
void FUN_80072e60(char*p,int f){*(char**)(p+0)=DAT_800a24a8;if(f&1)FUN_80024238(p);}
