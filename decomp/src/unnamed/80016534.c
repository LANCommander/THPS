/* FUN_80016534 (0x80016534) */
typedef struct{short a,b;char pad[3];char c7,c8,c9,c10,c11,c12,c13;char pad2[10];}E;
typedef struct{char pad0[4];char b4;char pad1[7];int f12;int f16;int f20;char pad2[8];E e[15];}P;
extern char DAT_8009e538[];
void SetLine__5CMenuUc(char*p,int l);
char* FUN_80016534(P*p,int a,int b,int c,int s2,int s1,int g){
int i;
*(char**)p=DAT_8009e538;
p->f12=a;p->f16=b;p->b4=c;p->f20=g;
for(i=0;i<15;i++){
p->e[i].c7=182;p->e[i].c8=132;p->e[i].c9=36;p->e[i].c10=122;p->e[i].c11=122;p->e[i].c12=122;p->e[i].c13=128;
p->e[i].a=s2;p->e[i].b=s1;
}
SetLine__5CMenuUc((char*)p,0);
return (char*)p;
}
