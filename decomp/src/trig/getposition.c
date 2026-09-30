/* Trig_GetPosition__FR7CVectori (0x80047600) */
typedef struct { int x, y, z; } V;
unsigned short **DAT_800d19e8;
int* Trig_GetPosition__FR7CVectori(V* out, int n){
  unsigned short* b = DAT_800d19e8[n];
  unsigned char* q;
  int* p;
  switch (*b) {
    case 1:
    case 7:
      q = (unsigned char*)b + 8 + b[3] * 2;
      while (*q != 0xff) q++;
      q += 4;
      break;
    case 3: case 8: case 10: case 11: case 13: case 1000: case 1001:
      q = (unsigned char*)(b[1] * 2 + (unsigned)b) + 7;
      break;
    case 5:
      q = (unsigned char*)(b[2] * 2 + (unsigned)b) + 9;
      break;
    case 500: case 501:
      q = (unsigned char*)b + 5;
      break;
    default:
      goto end;
  }
  p = (int*)((unsigned)q & ~3);
  out->x = p[0] << 12;
  out->y = p[1] << 12;
  out->z = p[2] << 12;
end:
  return p + 3;
}
