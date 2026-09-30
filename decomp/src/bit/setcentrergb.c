/* SetCentreRGB__5CGlowUcUcUc (0x8002901c) */
void SetCentreRGB__5CGlowUcUcUc(char* t, unsigned char r, unsigned char g, unsigned char b){
  *(unsigned*)(t+0x58) = (0x32<<24) | (b<<16) | (g<<8) | r;
}
