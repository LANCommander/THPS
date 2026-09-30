/* Front_GetButtons__FRiN30 (0x80019e94) */
typedef struct { unsigned char b[0x16c]; } Pad;
extern Pad DAT_800c0a48[];
extern int DAT_800d1728, DAT_800d16fc;
int DAT_800d151c, DAT_800d1520;
void Front_GetButtons__FRiN30(int* a, int* b, int* c, int* d){
  int v, w, e;
  if (DAT_800d1728 == 0 || DAT_800d16fc == 0) {
    v = 0;
    if (DAT_800c0a48[0].b[0xe1] || DAT_800c0a48[1].b[0xe1]) v = 1;
    *d = v;
    e = DAT_800c0a48[0].b[0xe1];
    DAT_800d151c = e;
    if (!e) DAT_800d1520 = DAT_800c0a48[1].b[0xe1];
    else DAT_800d1520 = 0;
    DAT_800c0a48[0].b[0xe1] = 0;
    DAT_800c0a48[1].b[0xe1] = 0;
  } else {
    *d = 0;
  }
  v = 0;
  if (DAT_800c0a48[0].b[0x31] || DAT_800c0a48[1].b[0x31] || *d) v = 1;
  *a = v;
  DAT_800c0a48[0].b[0x31] = 0;
  DAT_800c0a48[1].b[0x31] = 0;
  w = 0;
  if (DAT_800c0a48[0].b[1] || DAT_800c0a48[1].b[1]) w = 1;
  *b = w;
  DAT_800c0a48[0].b[1] = 0;
  DAT_800c0a48[1].b[1] = 0;
  *c = *b | *a;
  if (DAT_800c0a48[0].b[0x11]) { DAT_800c0a48[0].b[0x11] = 0; *c = 1; }
  if (DAT_800c0a48[0].b[0x21]) { DAT_800c0a48[0].b[0x21] = 0; *c = 1; }
  if (DAT_800c0a48[0].b[0xf1]) { DAT_800c0a48[0].b[0xf1] = 0; *c = 1; }
  if (DAT_800c0a48[0].b[0x41]) { DAT_800c0a48[0].b[0x41] = 0; *c = 1; }
  if (DAT_800c0a48[0].b[0x51]) { DAT_800c0a48[0].b[0x51] = 0; *c = 1; }
  if (DAT_800c0a48[0].b[0x61]) { DAT_800c0a48[0].b[0x61] = 0; *c = 1; }
  if (DAT_800c0a48[0].b[0x71]) { DAT_800c0a48[0].b[0x71] = 0; *c = 1; }
  if (DAT_800c0a48[1].b[0x11]) { DAT_800c0a48[1].b[0x11] = 0; *c = 1; }
  if (DAT_800c0a48[1].b[0x21]) { DAT_800c0a48[1].b[0x21] = 0; *c = 1; }
  if (DAT_800c0a48[1].b[0xf1]) { DAT_800c0a48[1].b[0xf1] = 0; *c = 1; }
  if (DAT_800c0a48[1].b[0x41]) { DAT_800c0a48[1].b[0x41] = 0; *c = 1; }
  if (DAT_800c0a48[1].b[0x51]) { DAT_800c0a48[1].b[0x51] = 0; *c = 1; }
  if (DAT_800c0a48[1].b[0x61]) { DAT_800c0a48[1].b[0x61] = 0; *c = 1; }
  if (DAT_800c0a48[1].b[0x71]) { DAT_800c0a48[1].b[0x71] = 0; *c = 1; }
  if (*a) *b = 0;
}
