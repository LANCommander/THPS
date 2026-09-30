/* GetCommandPoint__Fi (0x80044920) */
typedef struct CP { int pad0; unsigned char coll, exec; short pad6; short pad8; unsigned short id; char padc[8]; struct CP *next; } CP;
short **DAT_800d19e8;
CP *DAT_800d19f8;
CP *GetCommandPoint(int n){
  CP *p;
  if (n != 0xffff && *DAT_800d19e8[n] == 6) {
    for (p = DAT_800d19f8; p; p = p->next)
      if (p->id == n) return p;
  }
  return 0;
}
