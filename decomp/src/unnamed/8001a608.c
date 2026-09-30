/* FUN_8001a608 (0x8001a608) */
struct T{char pad[12];int f;char q[104];};
extern int DAT_800a42f4[];extern struct T DAT_800a5398[];extern int DAT_800d1e28;extern int DAT_800d16a4;int DAT_800d13e8;
int FUN_8007409c(void);void FUN_8001a128(void);
void FUN_8001a608(void){int v;if(DAT_800a42f4[0]==0&&DAT_800a5398[DAT_800d1e28].f!=0&&DAT_800d16a4==1&&FUN_8007409c()==0)v=25;else{v=16;if(DAT_800a42f4[0]==0)v=15;}DAT_800d13e8=v;FUN_8001a128();}
