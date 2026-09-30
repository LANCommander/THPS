/* _._9CSmokeJet (0x80015b84) */
extern char DAT_8009e2c0[];
void FUN_8002e290(char*, int);
void FUN_80027d70(char*);
void __dt__9CSmokeJet(char* t, int f){
  *(char**)(t+0x44) = DAT_8009e2c0;
  FUN_8002e290(t, 0);
  if (f & 1) FUN_80027d70(t);
}
