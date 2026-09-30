/* FUN_8005d28c (0x8005d28c) */
extern char DAT_800a1b64[];extern char DAT_800a1b74[];extern char DAT_800c0a48[];
char* DAT_800d1d0c;int DAT_800d1cec;int DAT_800d1d14;
void FUN_8005c8dc(int a);void FUN_8005c97c(int a);void FUN_8005ca64(void);int FUN_8005ca3c(char*a);void FUN_80061a10(int a);void FUN_8005dc58(int a);
char* __nw__5CItemUi(unsigned);
char* FUN_80063a5c(char*p,int a,int b,int c,int d,int e,int f);
void Pack_DefragmentFully__Fv(void);void FUN_8006b240(void);void FUN_80061ea0(void);
void FUN_8005d28c(void){
char*p;
FUN_8005c8dc(8);FUN_8005c97c(8);FUN_8005ca64();
FUN_80061a10(FUN_8005ca3c(DAT_800a1b64));
FUN_8005dc58(6);
p=__nw__5CItemUi(24);
if(p){p=FUN_80063a5c(p,8,FUN_8005ca3c(DAT_800a1b74),0,458,64,128);}
DAT_800d1d0c=p;
DAT_800c0a48[225]=0;DAT_800c0a48[589]=0;
DAT_800d1cec=0;DAT_800d1d14=0;
Pack_DefragmentFully__Fv();FUN_8006b240();FUN_80061ea0();
}
