/* FUN_80048c8c (0x80048c8c) */
typedef struct { char pad[24]; unsigned char on, r, g, b; char rest[0x80ac - 28]; } T;
extern T DAT_800a891c[2];
extern T DAT_800b09c8;
int DAT_800d1a3c;
void FUN_80048c8c(void)
{ unsigned int c = DAT_800d1a3c;
  if (c == -1) { DAT_800a891c[0].on = 0; DAT_800a891c[1].on = 0; }
  else {
  DAT_800a891c[0].on = 1; DAT_800a891c[0].r = c >> 16; DAT_800a891c[0].g = c >> 8; DAT_800a891c[0].b = DAT_800d1a3c;
  DAT_800a891c[1].on = 1; DAT_800b09c8.r = c >> 16; DAT_800b09c8.g = c >> 8; DAT_800b09c8.b = DAT_800d1a3c; } }
