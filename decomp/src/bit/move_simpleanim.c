/* Move__11CSimpleAnim (0x80029974) */
typedef struct{char p[0x59]; unsigned char n; signed char f; char q[0x70-0x5b]; int once; int end;}B;
void IncFrame__7CFT4Bit(B*);
void FUN_80027e18(B*);
void SetFrame__7CFT4Biti(B*, int);
void Move__11CSimpleAnim(B* t){
  IncFrame__7CFT4Bit(t);
  if (t->once) {
    if (t->f >= t->end) FUN_80027e18(t);
  } else if (t->f >= t->n) {
    if (t->end == -2) SetFrame__7CFT4Biti(t, t->n - 1);
    else SetFrame__7CFT4Biti(t, 0);
  }
}
