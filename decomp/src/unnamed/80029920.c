/* FUN_80029920 (0x80029920) */
extern char DAT_8009f770[];
int BASEF(char*p,int a);void FUN_80027d70(void*p);
void FUN_80029920(char*p,int f){*(char**)(p+68)=DAT_8009f770;BASEF(p,0);if(f&1)FUN_80027d70(p);}
