/* erase__12VerticalMenu (0x80064f9c) */
typedef struct { int spr; char str[0x20]; int a, b, h, c, d, e, x; } E;
typedef struct { char pad[8]; int f8; int fc; int cnt; int prev; int cur; E e[12]; int timer; int _320[2]; int s1; int s2; } VM;
void draw__6Spriteiiiiii(int, int, int, int, int, int, int);
void erase__12VerticalMenu(VM* t){
  int i, w;
  w = ((t->e[t->cur].h >> 1) * t->fc) / t->f8 + 30;
  if (t->timer < 61) {
    if (t->s1) {
      draw__6Spriteiiiiii(t->s1, t->e[t->cur].a - w - 22, t->e[t->cur].b - 34, 0, -1, -1, -1);
    }
    if (t->s2) {
      draw__6Spriteiiiiii(t->s2, t->e[t->cur].a + w - 22, t->e[t->cur].b - 34, 0, -1, -1, -1);
    }
  }
  for (i = 0; i < t->cnt; i++) {
    int o = i << 6;
    int q = (*(int*)((char*)t + o + 0x4c) >> 1) * t->fc / t->f8;
    draw__6Spriteiiiiii(*(int*)((char*)t + o + 0x1c), *(int*)((char*)t + o + 0x58), *(int*)((char*)t + o + 0x44) - q - 1, 0, -1, -1, -1);
  }
}
