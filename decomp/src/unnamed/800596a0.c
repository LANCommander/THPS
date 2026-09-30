/* FUN_800596a0 (0x800596a0) */
struct Q{int a,b,c,d,e;};
extern struct Q* DAT_800d1a60;struct Q* DAT_800d1c80;
void FUN_80059618(int a);void FUN_8004d5d0(struct Q*p);struct Q* FUN_8004d068(int a,int b,int c);
void FUN_800596a0(void){struct Q*n;FUN_80059618(0);if(DAT_800d1a60){do{n=(struct Q*)DAT_800d1a60->c;FUN_8004d5d0(DAT_800d1a60);DAT_800d1a60=n;}while(n);}DAT_800d1a60=FUN_8004d068(20,1,1);*DAT_800d1a60=*DAT_800d1c80;DAT_800d1a60->c=0;FUN_80059618(0);}
