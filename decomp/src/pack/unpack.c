/* Pack_Unpack__Fss (0x8004a2d4) */
typedef struct TSPack{unsigned short x,y,w,h;struct TSPack*next;}TSPack;
TSPack*DAT_800d1a64;
void Pack_Remove__FPP6TSPackP6TSPack(TSPack**,TSPack*);
TSPack*Pack_NewFree__Fiiii(int,int,int,int);
int Pack_Merge__FP6TSPack(TSPack*);
void Pack_Unpack__Fss(short x,short y){
  TSPack*p;
  for(p=DAT_800d1a64;p;p=p->next){
    if(p->x==x&&p->y==y){
      int w=p->w,h=p->h;
      Pack_Remove__FPP6TSPackP6TSPack(&DAT_800d1a64,p);
      Pack_Merge__FP6TSPack(Pack_NewFree__Fiiii(x,y,w,h));
      return;
    }
  }
}
