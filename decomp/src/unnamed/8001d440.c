/* FUN_8001d440 (0x8001d440) */
extern unsigned char DAT_800b9d9c[];extern unsigned char* DAT_800d1adc;
unsigned short DAT_800d15f8;
int FUN_8001d440(unsigned char*s){
int m=0;
while(*s){
int v=DAT_800b9d9c[*s];
if(v==254)v=-1;
if(v==253)v=-1;
if(v==252)v=-1;
if(v==251)v=-1;
if(v==250)v=-1;
if(v==255)v=-1;
if(v>=0){int w=DAT_800d1adc[v*8+3];if(m<w)m=w;}
s++;
}
return (m*DAT_800d15f8)>>8;
}
