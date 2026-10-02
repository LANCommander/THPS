/* FUN_8004d6a0 (0x8004d6a0) */
typedef struct B{struct B*next;int flags:4;unsigned len:28;}B;
B*DAT_800d1b48;B*DAT_800d1b4c;int DAT_800d1b50;unsigned DAT_800d1b54;int DAT_800d1b5c[2];unsigned DAT_800d1b60;
void AddToFreeList__FP12SBlockHeaderi(B*b,int i);
void FUN_8004d6a0(char*p,unsigned n){
B*b=(B*)(p-8);
unsigned l,n8;
int f=b->flags;
B*r;
if(f==-2){
if(b==DAT_800d1b48){b->len=n;return;}
if(b==DAT_800d1b4c)return;
}
l=b->len;
if(n<l-8){
r=(B*)(p+n);
n8=n+8;
r->len=l-n8;
DAT_800d1b5c[f]-=b->len-n;
b->len=n;
AddToFreeList__FP12SBlockHeaderi(r,f);
if(f==1){
if(DAT_800d1b60>=DAT_800d1b54)DAT_800d1b50=f;else DAT_800d1b50=0;
}
}
}
