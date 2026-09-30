/* FUN_8001f0dc (0x8001f0dc) */
struct S{int a;char r[32];};
extern struct S DAT_800a6124[];int DAT_800d15e4;
void Mess_UnloadFont__Fv(void);
void FUN_8001f0dc(void){int i;for(i=0;i<10;i++){if(DAT_800a6124[i].a){DAT_800d15e4=i;Mess_UnloadFont__Fv();}}}
