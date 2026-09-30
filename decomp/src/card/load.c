/* Card_Load__F9EFileTypePUlT1 (0x800149f4) */
extern char DAT_800a5848[];
extern char DAT_800a5864[];
int SyncToGoodState__Fv(void);
int FUN_8008eb4c(char*, int);
void _clear_event__Fv(void);
int FUN_8008ead8(int, unsigned long*, int);
int CalcChecksum__FPUlUl(unsigned long*, unsigned long);
void FUN_8008e934(int);
int Card_Load__F9EFileTypePUlT1(int type, unsigned long* a, unsigned long* b){
  char* name;
  int size, h, sum, chk;
  switch (type) {
    case 0: name = DAT_800a5848; size = 3200; break;
    case 1: name = DAT_800a5864; size = 24576; break;
    case 2: name = DAT_800a5864; size = 640; break;
    case 3: name = 0; size = 0; break;
  }
  if (SyncToGoodState__Fv() == 1) return 1;
  h = FUN_8008eb4c(name, 1);
  if (h == -1) return 1;
  _clear_event__Fv();
  if (FUN_8008ead8(h, a, size) != size) return 1;
  sum = 0;
  chk = 0;
  if (type == 1) {
    sum = ((short*)a)[283];
    chk = CalcChecksum__FPUlUl(a + 160, 23936);
  } else if (type == 0) {
    sum = ((short*)a)[283];
    chk = CalcChecksum__FPUlUl(a + 160, 2560);
  }
  if (sum != chk) return 1;
  if (b) {
    if (FUN_8008ead8(h, b, size) != size) return 1;
    sum = 0;
    chk = 0;
    if (type == 1) {
      sum = ((short*)b)[283];
      chk = CalcChecksum__FPUlUl(b + 160, 23936);
    }
    if (sum != chk) return 1;
  }
  FUN_8008e934(h);
  return 0;
}
