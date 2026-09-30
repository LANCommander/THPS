/* CentreY__5CMenu (0x80016680) */
typedef struct { const char *name; int pad[2]; unsigned char h, on, vis, pad2; int pad3[2]; } Entry;
typedef struct { char pad[9]; unsigned char n; char pad2[6]; int y; int gap; Entry e[15]; } CMenu;
void CentreY(CMenu *m){
  int cnt = 0, i, sum = 0;
  for (i = 0; i < m->n; i++) {
    if (m->e[i].on) { cnt++; sum += m->e[i].h; }
  }
  m->y = (240 - ((cnt - 1) * m->gap + sum)) / 2;
}
