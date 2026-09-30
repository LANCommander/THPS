/* SendDeathPulse__6CBaddy (0x8003fb68) */
extern char** DAT_800d19e8 __attribute__((section(".data")));
void Trig_SendPulse__FPUs(unsigned short*);
void SendDeathPulse__6CBaddy(char* t){
  if (!t[0x1a1] && *(unsigned short*)(t+0xe2) != 0xffff) {
    t[0x1a1] = 1;
    Trig_SendPulse__FPUs((unsigned short*)(DAT_800d19e8[*(unsigned short*)(t+0xe2)] + 6));
  }
}
