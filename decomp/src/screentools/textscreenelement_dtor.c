/* _._17TextScreenElement (0x8002da78) */
extern char DAT_8009f708[];
void FUN_8004d5d0(void*);
void CSpecialDisplay_dtor(void*, int);
void FUN_80027d70(void*);
void TextScreenElement_dtor(char *this, int flags){
  *(char**)(this + 0x44) = DAT_8009f708;
  FUN_8004d5d0(*(void**)(this + 0x50));
  CSpecialDisplay_dtor(this, 0);
  if (flags & 1) FUN_80027d70(this);
}
