/* SetTexture__8CQuadBitPci (0x80028440) */
char* Spool_FindAnim__FPc(char*);
void SetTexture__8CQuadBitPci(char* t, char* name, int i){
  char* p = Spool_FindAnim__FPc(name);
  *(int*)(t+0x94) = *(int*)(p + i*8 + 4);
}
