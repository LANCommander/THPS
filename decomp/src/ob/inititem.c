/* InitItem__5CItemPc (0x800435b8) */
int Spool_FindRegion__FPc(char*);
void InitItem__5CItemPc(char* t, char* name){
  t[0x1b] = Spool_FindRegion__FPc(name);
  *(short*)(t+0x16) = 0;
}
