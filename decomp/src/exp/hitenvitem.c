/* Exp_HitEnvItem__FP4ItemPUii (0x8004e968) */
typedef struct Item{unsigned short flags;char _2[0x14];unsigned short model;char _18[3];unsigned char slot;struct Item* next;}Item;
typedef struct{char _0[0x10];unsigned short** models;char _14[0x2c];}Slot;
extern Item* DAT_800d1eec __attribute__((section(".data")));
extern Slot DAT_800bf7a8[];
void Shatter_Item__FP4Itemii(Item*, int, int);
void FUN_800218a4(Item*, unsigned*, int, int, int, int, int);
void Exp_HitEnvItem(Item* it, unsigned* p, int c){
  Item* q;
  if (it) {
    q = DAT_800d1eec;
    while (q) { if (q == it) break; q = q->next; }
    if (q) {
      int v;
      if (DAT_800bf7a8[it->slot].models[it->model][0] & 2) {
        v = 0; __asm__("" : "+r"(v));
        if ((v || c == 0xffff) && !(c < v)) Shatter_Item__FP4Itemii(it, 1, 1);
      } else if (p) {
        FUN_800218a4(it, p, 1, 1, 1, 1, 1);
      }
    }
  }
}
