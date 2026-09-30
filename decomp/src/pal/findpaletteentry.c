/* Pal_FindPaletteEntry__FUi (0x8004abf4) */
typedef struct SPalette{char pad[8];unsigned id;int fc;struct SPalette*next;}SPalette;
SPalette*DAT_800d1a80;
SPalette*Pal_FindPaletteEntry__FUi(unsigned id){
  SPalette*p=DAT_800d1a80;
  while(p&&p->id!=id)p=p->next;
  return p;
}
