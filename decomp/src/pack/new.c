/* Pack_New__FPP6TSPack (0x8004961c) */
typedef struct TSPack{unsigned short x,y,w,h;struct TSPack*next;}TSPack;
TSPack*FUN_800495c4(void);
TSPack*Pack_New__FPP6TSPack(TSPack**list){
  TSPack*p=FUN_800495c4();
  p->next=*list;
  *list=p;
  return p;
}
