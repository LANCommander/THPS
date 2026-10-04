/* FUN_80023168 (0x80023168) */
typedef struct{int w0;unsigned short h4,h6,h8,h10;int w12,w16;int b20;int w24,w28;}E;
extern E DAT_800a63e8[];
int DAT_800d1634;int DAT_800d1648;
unsigned char DAT_800d167d;unsigned short DAT_800d1672;unsigned short DAT_800d1674;int DAT_800d1660;int DAT_800d1664;int DAT_800d1668;unsigned char DAT_800d167c;int DAT_800d1680;int DAT_800d165c;
void FUN_80023168(int a){
if(DAT_800d1634)return;
if(a<0){a=~a;}
else{
a=DAT_800d1648++;
while(DAT_800d1648<26){if(DAT_800a63e8[DAT_800d1648].h4==96)break;DAT_800d1648++;}
if(DAT_800d1648==26)DAT_800d1648=2;
}
DAT_800d167d=a;
DAT_800d1672=DAT_800a63e8[a].h4;
DAT_800d1674=DAT_800a63e8[a].h6;
DAT_800d1660=DAT_800a63e8[a].h8;
DAT_800d1664=DAT_800a63e8[a].w12;
DAT_800d1668=DAT_800a63e8[a].w16;
DAT_800d167c=DAT_800a63e8[a].b20;
DAT_800d1680=DAT_800a63e8[a].w28;
DAT_800d165c=DAT_800a63e8[a].w24;
}
