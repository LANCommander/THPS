/* FUN_80014ba4 (0x80014ba4) */
typedef struct{int a,b;}T;
typedef struct{char pad[44];short s[5];}H;
extern int DAT_800a42f4[];typedef struct{char pad[28];int f;char pad2[48];T t[5];}S;extern S DAT_800bf318;
char* FUN_8004c8a4(void);char* FUN_8004d068(char*a,int b,int c);void FUN_8004cb10(char*a);void FUN_8004cdd0(void);void FUN_8004d5d0(char*a);
short FUN_80014ba4(void){
H*h;char*b;int i;
b=FUN_8004d068(FUN_8004c8a4(),1,1);
if(b){FUN_8004cb10(b);FUN_8004cdd0();}h=(H*)(b+512);
DAT_800a42f4[0]=h->s[0];DAT_800a42f4[1]=h->s[1];DAT_800a42f4[2]=h->s[2];DAT_800a42f4[3]=h->s[3];DAT_800a42f4[4]=h->s[4];
DAT_800bf318.f=*(int*)(b+512);
for(i=0;i<5;i++)DAT_800bf318.t[i]=((T*)(b+516))[i];
FUN_8004d5d0(b);
return h->s[0];
}
