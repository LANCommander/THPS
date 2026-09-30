/* SetTexture__15CTexturedRibbonUi (0x8002e2f0) */
int Spool_FindTextureEntry__FUi(unsigned);
void SetTexture__15CTexturedRibbonUi(char* t, unsigned a){
  *(int*)(t+0x4c) = Spool_FindTextureEntry__FUi(a);
}
