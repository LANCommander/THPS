/* FUN_8005cae8 (0x8005cae8) */
struct VT{char pad[8];short off;short pad2;void(*fn)(char*,int);};
struct O{struct VT*vt;};
extern struct O* DAT_800d1b10;extern char DAT_800a1abc[];
void FUN_8008c190(char*a);
void FUN_8005cae8(void){if(DAT_800d1b10)FUN_8008c190(DAT_800a1abc);if(DAT_800d1b10)DAT_800d1b10->vt->fn((char*)DAT_800d1b10+DAT_800d1b10->vt->off,3);DAT_800d1b10=0;}
