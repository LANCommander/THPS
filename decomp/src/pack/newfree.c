/* Pack_NewFree__Fiiii (0x80049650) */
typedef struct TSPack{unsigned short x,y,w,h;struct TSPack*next;}TSPack;
TSPack*DAT_800d1a60;
TSPack*Pack_New__FPP6TSPack(TSPack**);
TSPack*Pack_NewFree__Fiiii(int x,int y,int w,int h){
  TSPack*p=Pack_New__FPP6TSPack(&DAT_800d1a60);
  p->x=x;
  p->y=y;
  p->w=w;
  p->h=h;
  return p;
}
