/* AddEntry__5CMenuPCc (0x800167f0) */
typedef struct { const char *name; int pad[2]; unsigned char sel, on, vis, pad2; int pad3[2]; } Entry;
typedef struct { char pad[9]; unsigned char n; char pad2[14]; Entry e[15]; } CMenu;
void AddEntry(CMenu *m, const char *s){
  m->e[m->n].name = s;
  m->e[m->n].on = 1;
  m->e[m->n].vis = 1;
  m->e[m->n].sel = 0;
  m->n++;
}
