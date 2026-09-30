/* FUN_80071acc (0x80071acc) */
extern char DAT_800a2460[];
void FUN_80024238(void*p);
void FUN_80071acc(char*p,int f){*(char**)(p+0)=DAT_800a2460;if(f&1)FUN_80024238(p);}
