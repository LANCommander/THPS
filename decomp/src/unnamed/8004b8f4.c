/* FUN_8004b8f4 (0x8004b8f4) */
struct S{int a,b,c,d,e;short f;char pad[42];};
int DAT_800d1a9c;extern unsigned short DAT_800d2b8c[];
void FUN_80094424(int a,unsigned short*b);void FUN_80093e54(int a,struct S*s);void FUN_8008f3a0(int a,int b);
void FUN_8004b8f4(void){struct S s;int i;unsigned short*q;if(!DAT_800d1a9c){i=0;q=DAT_800d2b8c;DAT_800d1a9c=1;s.b=16;s.f=0;for(;i<24;i++){FUN_80094424(i,q);FUN_80093e54(i,&s);q++;}FUN_8008f3a0(11,0);}}
