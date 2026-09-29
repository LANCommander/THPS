struct S { char a[0x20]; int field; char b[0x1c]; };
extern struct S DAT_800bf7a8[];
void f(int p, int p2){ DAT_800bf7a8[*(unsigned char*)(p+0x1b)].field = p2 + 4; }
