/* FUN_80022b4c (0x80022b4c) */
struct E{int f0;int p[5];int f24;int q[1];};
extern struct E DAT_800a63e8[];extern unsigned char DAT_800a6728[];
int FUN_8009085c(char*a,int b);int FUN_800913c0(char*a);
void FUN_80022b4c(void){
char buf[24];
int i;
for(i=0;i<26;i++){
if(DAT_800a63e8[DAT_800a6728[i]].f24){
if(FUN_8009085c(buf,DAT_800a63e8[DAT_800a6728[i]].f0))DAT_800a63e8[DAT_800a6728[i]].f24=FUN_800913c0(buf);
else DAT_800a63e8[DAT_800a6728[i]].f24=0;
}
}
}
