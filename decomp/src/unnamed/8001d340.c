/* FUN_8001d340 (0x8001d340) */
typedef struct{signed char a;unsigned char b,c,d,e,f,g,h;}E;
extern unsigned char DAT_800b9d9c[];extern E* DAT_800d1adc;
unsigned short DAT_800d15f8;
int FUN_8001d340(unsigned char*s){
int w=0;int n=0;
while(*s){
int v=DAT_800b9d9c[*s];
if(v==254)v=-1;
if(v==253)v=-1;
if(v==252)v=-1;
if(v==251)v=-1;
if(v==250)v=-1;
if(v==255)v=-1;
if(v>=0){n++;w+=DAT_800d1adc[v].c+DAT_800d1adc[v].a;}
else w+=10;
s++;
}
w=(w*DAT_800d15f8)>>8;return w+n*3;
}
