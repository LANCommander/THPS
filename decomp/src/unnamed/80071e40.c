/* FUN_80071e40 (0x80071e40) */
extern int DAT_800be09c[];extern int DAT_800dc94c;
void FUN_8004cf7c(void);
void FUN_80071e40(int a){int v=DAT_800dc94c;DAT_800be09c[3]=0x801fe000;DAT_800be09c[0]=v;v+=a;DAT_800be09c[1]=v;DAT_800be09c[2]=v;FUN_8004cf7c();}
