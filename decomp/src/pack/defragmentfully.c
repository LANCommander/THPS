/* Pack_DefragmentFully__Fv (0x8004a8cc) */
typedef struct TSPack { unsigned short x, y, w, h; struct TSPack* next; } TSPack;
TSPack* DAT_800d1a60;
int DAT_800d1a74, DAT_800d1a7c;
void FUN_800495f4(TSPack*);
void Pack_Zap__Fiiii(int, int, int, int);
int Pack_Merge__FP6TSPack(TSPack*);
void Pack_DefragmentFully__Fv(void){
  TSPack* p;
  TSPack* n;
  int m;
  if (DAT_800d1a60) {
    DAT_800d1a7c = 0;
    p = DAT_800d1a60;
    do {
      n = p->next;
      FUN_800495f4(p);
      p = n;
    } while (p);
    DAT_800d1a60 = 0;
    switch (DAT_800d1a74) {
      case 320:
        Pack_Zap__Fiiii(320, 256, 64, 256);
        Pack_Zap__Fiiii(DAT_800d1a74 + 64, 256, 128, 256);
        Pack_Zap__Fiiii(DAT_800d1a74 + 192, 256, 512, 256);
        Pack_Zap__Fiiii(DAT_800d1a74, 0, 64, 256);
        Pack_Zap__Fiiii(DAT_800d1a74 + 64, 0, 128, 256);
        Pack_Zap__Fiiii(DAT_800d1a74 + 192, 0, 512, 256);
        break;
      case 640:
        Pack_Zap__Fiiii(640, 256, 128, 256);
        Pack_Zap__Fiiii(DAT_800d1a74 + 128, 256, 256, 256);
        Pack_Zap__Fiiii(DAT_800d1a74, 0, 128, 256);
        Pack_Zap__Fiiii(DAT_800d1a74 + 128, 0, 256, 256);
        break;
      default:
        Pack_Zap__Fiiii(DAT_800d1a74, 256, 1024 - DAT_800d1a74, 256);
        Pack_Zap__Fiiii(DAT_800d1a74, 0, 1024 - DAT_800d1a74, 256);
        break;
    }
    do {
      p = DAT_800d1a60;
      m = 0;
      while (p) {
        m |= Pack_Merge__FP6TSPack(p);
        p = p->next;
      }
    } while (m);
  }
}
