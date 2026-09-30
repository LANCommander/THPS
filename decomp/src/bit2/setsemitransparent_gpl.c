/* SetSemiTransparent__10CGPolyLine (0x800273a4) */
void SetSemiTransparent__10CGPolyLine(char* t){
  int i;
  for (i = 0; i < *(int*)(t+0x48); i++) (*(char**)(t+0x4c) + i*16)[15] |= 2;
  t[0x5f] |= 2;
}
