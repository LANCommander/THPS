/* Trig_SetRestart__FPc (0x80044ae4) */
typedef struct { int x, y, z; } V;
int DAT_800d19e4, DAT_800d19ec;
short **DAT_800d19e8;
char *Trig_GetPosition__FR7CVectori(V *v, int n);
int Utils_CompareStrings__FPCcT0Ui(const char *a, const char *b, unsigned n);
void Trig_SetRestart(char *name){
  int i;
  DAT_800d19e4 = 0xffff;
  for (i = 0; i < DAT_800d19ec; i++) {
    if (*DAT_800d19e8[i] == 8) {
      V v;
      if (Utils_CompareStrings__FPCcT0Ui(Trig_GetPosition__FR7CVectori(&v, i) + 6, name, -1)) {
        DAT_800d19e4 = i;
        return;
      }
    }
  }
}
