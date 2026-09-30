/* Trig_ResetCPExecutedFlags__Fi (0x800449cc) */
typedef struct CP { int pad0; unsigned char coll, exec; char pad6[14]; struct CP *next; } CP;
CP *DAT_800d19f8;
void Trig_ResetCPExecutedFlags(int m){
  CP *p;
  for (p = DAT_800d19f8; p; p = p->next)
    if ((p->exec & m) && !(p->coll & m)) p->exec &= ~m;
}
