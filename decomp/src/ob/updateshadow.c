/* UpdateShadow__5CBody (0x80043b50) */
typedef struct { short x, y, z; } SV;
typedef struct { char _0[0x40]; short s40; char _42; } Q;
typedef struct { char _0[0x52]; unsigned short flags; char _54[0x68]; char pos[0xc]; unsigned short us_c8; short s_ca; unsigned short us_cc; char _ce[2]; Q* q; unsigned short us_d4; short s_d6, s_d8; } B;
extern int DAT_800d186c;
extern char DAT_800d19c4[];
Q* FUN_80027d08(int);
Q* FUN_80028394(Q*);
void SetTexture__8CQuadBitPci(Q*, char*, int);
void FUN_80028484(Q*, int);
void FUN_80028498(Q*);
void OrientUsing__8CQuadBitRC7CVectorRC7SVECTORiii(Q*, char*, SV*, int, int, int);
void SetTransparency__8CQuadBitUc(Q*, unsigned char);
void FUN_80043af4(B*);
void UpdateShadow__5CBody(B* t){
  Q* q;
  SV sv;
  int v;
  if (t->flags & 8) {
    if (t->q == 0) {
      DAT_800d186c = 0;
      q = FUN_80027d08(156);
      if (q) q = FUN_80028394(q);
      t->q = q;
      DAT_800d186c = 1;
      SetTexture__8CQuadBitPci(q, DAT_800d19c4, 0);
      FUN_80028484(t->q, 4);
      FUN_80028498(t->q);
      t->q->s40 = 32;
      *((char*)t->q + 0x42) = 1;
    }
    if (t->s_ca < -128) {
      sv.x = t->us_c8;
      sv.y = t->s_ca;
      sv.z = t->us_cc;
      OrientUsing__8CQuadBitRC7CVectorRC7SVECTORiii(t->q, t->pos, &sv, t->us_d4, t->us_d4, 0);
    }
    v = ((t->s_d8 - t->s_d6) << 7) / t->s_d8;
    if (v < 0) v = 0;
    { int w = v / 6; SetTransparency__8CQuadBitUc(t->q, w); }
  } else {
    FUN_80043af4(t);
  }
}
