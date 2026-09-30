/* __6CBaddy (0x8003fa34) */
extern char DAT_800a0270[];
int DAT_800d1988;
char* FUN_80043d04(char*);
char* __6CBaddy(char* t){
  FUN_80043d04(t);
  *(char**)(t+0x48) = DAT_800a0270;
  *(short*)(t+0xe0) = 0x80;
  *(int*)(t+0xdc) = 0x40;
  *(unsigned short*)(t+0xe2) = 0xffff;
  *(short*)(t+0x1a8) = 0x20;
  *(short*)(t+0x1fc) = 0;
  *(int*)(t+0x1e0) = 0;
  *(int*)(t+0x210) = 0;
  *(int*)(t+0x214) = -1;
  DAT_800d1988++;
  return t;
}
