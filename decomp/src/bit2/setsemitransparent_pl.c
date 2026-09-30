/* SetSemiTransparent__9CPolyLine (0x80027210) */
void SetSemiTransparent__9CPolyLine(char* t){
  int i;
  for (i = 0; i < *(int*)(t+0x4c); i++) (*(char**)(t+0x50) + i*16)[15] |= 2;
}
