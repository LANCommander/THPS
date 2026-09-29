void f(char* m, void* val){
  *(void**)(m + (unsigned)*(unsigned char*)(m+9)*0x18 + 0x18) = val;
  *(char*)(m + (unsigned)*(unsigned char*)(m+9)*0x18 + 0x25) = 1;
  *(char*)(m + (unsigned)*(unsigned char*)(m+9)*0x18 + 0x26) = 1;
  *(char*)(m + (unsigned)*(unsigned char*)(m+9)*0x18 + 0x24) = 0;
  *(char*)(m+9) += 1;
}
