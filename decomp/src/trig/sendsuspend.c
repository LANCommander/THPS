/* SendSuspend__FPP5CBodyi (0x80045e30) */
void FUN_80043a14(char *b, char **pp);
void SendSuspend(char **pp, int node){
  char *b;
  for (b = *pp; b; b = *(char**)(b + 0x1c))
    if (*(unsigned short*)(b + 0xe2) == node) FUN_80043a14(b, pp);
}
