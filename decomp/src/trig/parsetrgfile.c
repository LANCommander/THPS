/* Trig_ParseTRGFile__Fv (0x80047214) */
typedef struct { int x, y, z; } V;
typedef struct { unsigned short us0, us2, us4, us6; unsigned char b8, _9, b10, _b, b12, _d, b14, _f, b16, _11, b18; } Q;
unsigned short **DAT_800d19e8;
int DAT_800d19ec, DAT_800d19f4;
char DAT_800d1a10[8];
extern int DAT_800d186c;
extern unsigned short* DAT_800a8828[];
int GetFlag__FUcPUc(unsigned char, unsigned char*);
int* Trig_GetPosition__FR7CVectori(V*, int);
void FUN_80045268(int);
void FUN_80044820(int, unsigned short, char*);
void* FUN_80027d08(int);
int FUN_8001f614(void*, V*, int, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);
void* __nw__5CItemUi(unsigned);
void FUN_8004ef08(void*, unsigned short, int);
void CamPt_New__Fi(int);
void Trig_ClearTrigMenu__Fv(void);
void Trig_ParseTRGFile__Fv(void){
  int i, j, k;
  unsigned short** e;
  unsigned short ui;
  unsigned short* b;
  short* s;
  V v;
  int* r;
  Q* q;
  void* w;
  void* it;
  for (i = 0; i < DAT_800d19ec; i++) {
    b = DAT_800d19e8[i];
    switch (*(short*)b) {
      case 7:
        GetFlag__FUcPUc(1, (unsigned char*)b + (((short*)b)[3] * 2 + 8));
        break;
      case 1:
        if (GetFlag__FUcPUc(1, (unsigned char*)b + (((short*)b)[3] * 2 + 8))) FUN_80045268(i);
        break;
      case 5:
        r = Trig_GetPosition__FR7CVectori(&v, i);
        if (*(unsigned short*)r == 1) FUN_80045268(i);
        break;
      case 6:
        ui = i;
        b += 1;
        b = (unsigned short*)((char*)b + (*(short*)b * 2 + 2));
        if ((int)b & 2) b += 1;
        FUN_80044820(*(int*)b, ui, (char*)b + 4);
        break;
      case 2: case 9:
        b += 1;
        b = (unsigned short*)((char*)b + (*(short*)b * 2 + 2));
        if ((int)b & 2) b += 1;
        FUN_80044820(*(int*)b, i, DAT_800d1a10);
        break;
      case 500:
        q = (Q*)Trig_GetPosition__FR7CVectori(&v, i);
        DAT_800d186c = 0;
        w = FUN_80027d08(100);
        if (w) FUN_8001f614(w, &v, i, q->us0, q->us2, q->us4, q->us6, q->b8, q->b10, q->b12, q->b14, q->b16, q->b18);
        DAT_800d186c = 1;
        break;
      case 12: case 14:
        it = __nw__5CItemUi(24);
        if (it) FUN_8004ef08(it, i, 0);
        break;
      case 13:
        CamPt_New__Fi(i);
        break;
    }
  }
  Trig_ClearTrigMenu__Fv();
  for (j = 0; j < DAT_800d19ec; j++) {
    short *pNode = (short*)DAT_800d19e8[j];
    if (*pNode == 8) {
      char *pNodeName = (char*)Trig_GetPosition__FR7CVectori(&v, j) + 6;
      DAT_800a8828[DAT_800d19f4++] = (unsigned short*)pNodeName;
    }
  }
}
