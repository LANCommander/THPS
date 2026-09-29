extern int Utils_CompareStrings(const char*, const char*, unsigned);
void ChoiceIs(char *m, const char *s){
  Utils_CompareStrings(s, *(const char**)(m + (unsigned)*(unsigned char*)(m+6)*0x18 + 0x18), 0xffffffff);
}
