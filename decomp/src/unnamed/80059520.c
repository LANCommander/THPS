/* FUN_80059520 (0x80059520) flags=-fstructure-noalias */
typedef struct{int a,b,c,d,e;}S;
extern int DAT_800d1a60;extern int DAT_800d1a64;
S* DAT_800d1c84;S* DAT_800d1c80;int DAT_800d1c88;int DAT_800d1c8c;int DAT_800d1c90;
char DAT_800d1c94[8];char DAT_800d1c98[8];
S* FUN_8004982c(int a,int b,int c,char*d,char*e,int f,int g,int h);S* FUN_8004d068(int a,int b,int c);
void FUN_80059520(int m){
S*s;int t1,t2;
int w=256;
if(m==1)w=128;
s=FUN_8004982c(-1,w,256,DAT_800d1c94,DAT_800d1c98,16,0,0);
DAT_800d1c84=FUN_8004d068(20,1,1);
*DAT_800d1c84=*s;
DAT_800d1c80=FUN_8004d068(20,1,1);
*DAT_800d1c80=*s;
DAT_800d1c88=0;DAT_800d1c84->c=0;DAT_800d1c8c=DAT_800d1a60;DAT_800d1c90=DAT_800d1a64;
}
