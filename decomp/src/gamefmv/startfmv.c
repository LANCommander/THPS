/* GameFMV_StartFMV__Fi (0x80023270) */
typedef struct { char pad[0x18]; int p; int pad2; } FE;
extern FE DAT_800a63e8[];
extern int DAT_800a6748[];
int DAT_800d1634, DAT_800d162c, DAT_800d163c, DAT_800d1640, DAT_800d1644, DAT_800d164c, DAT_800d1630;
int DAT_800d168c[2];
int DAT_800d1664, DAT_800d1668, DAT_800d222c;
unsigned char DAT_800d167c, DAT_800d166c;
unsigned short DAT_800d1658, DAT_800d166e, DAT_800d1672, DAT_800d1674, DAT_800d1684, DAT_800d1686, DAT_800d1688, DAT_800d168a;
unsigned char DAT_800d167d;
int FUN_8004d068(int, int, int);
void FUN_80022498(void);
void FUN_80023cb8(void);
int strNextVlc__Fi(int);
void GameFMV_StartFMV__Fi(int a){
  int i, j;
  unsigned t, u;
  if (DAT_800d1634 == 0 && DAT_800a63e8[DAT_800d167d].p != 0) {
    DAT_800d1684 = DAT_800d1658;
    DAT_800d1686 = DAT_800d166e;
    DAT_800d1688 = DAT_800d167c ? 24 : 16;
    DAT_800d164c = 0;
    DAT_800d162c = 0;
    DAT_800d163c = 0;
    DAT_800d1640 = 0;
    DAT_800d1644 = 0;
    DAT_800d168a = DAT_800d1674;
    if (a) {
      for (i = 0; i < 2; i++) DAT_800d168c[i] = FUN_8004d068(DAT_800d1664, 1, 1);
    }
    DAT_800d222c = FUN_8004d068(DAT_800d1668 << 11, 1, 1);
    t = DAT_800d1672;
    t >>= 4;
    DAT_800d166c = t;
    if (a) {
      u = t & 255;
      if (u) {
        j = 0;
        do { DAT_800a6748[j] = FUN_8004d068(DAT_800d1674 << 5, 1, 1); j++; } while (j < DAT_800d166c);
      }
      FUN_80022498();
    }
    DAT_800d1634 = 1;
    DAT_800d1630 = 0;
    FUN_80023cb8();
    strNextVlc__Fi(1);
  }
}
