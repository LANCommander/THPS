/* FUN_8004d5d0 (0x8004d5d0) */
typedef struct B{struct B*next;int flags:4;unsigned len:28;}B;
B*DAT_800d1b48;B*DAT_800d1b4c;int DAT_800d1b50;unsigned DAT_800d1b54;int DAT_800d1b5c[2];unsigned DAT_800d1b60;
void AddToFreeList__FP12SBlockHeaderi(B*b,int i);
void FUN_8004d5d0(char*p){
B*b=(B*)(p-8);
int f=b->flags;
if(f==-2){
if(b==DAT_800d1b48){DAT_800d1b48=0;return;}
if(b==DAT_800d1b4c){DAT_800d1b4c=0;return;}
}
if((unsigned)f<2){
DAT_800d1b5c[f]-=8+b->len;
AddToFreeList__FP12SBlockHeaderi(b,f);
if(f==1){
if(DAT_800d1b60>=DAT_800d1b54)DAT_800d1b50=f;else DAT_800d1b50=0;
}
}
}
