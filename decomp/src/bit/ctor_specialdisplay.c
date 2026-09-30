/* __15CSpecialDisplay (0x80027ec4) */
extern char DAT_8009f890[];
void* DAT_800d18f0;
char* FUN_80027e44(char*);
void AttachTo__4CBitPv(char*, void*);
char* __15CSpecialDisplay(char* t){
  FUN_80027e44(t);
  *(char**)(t+0x44) = DAT_8009f890;
  AttachTo__4CBitPv(t, &DAT_800d18f0);
  return t;
}
