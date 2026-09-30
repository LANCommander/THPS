/* Pad_ActuatorOn__FUcUsUcUc (0x80070a80) */
typedef struct { char pad[0x154]; unsigned char act[4]; unsigned short w[10]; } P;
extern P DAT_800c0a48[];
extern char DAT_800c0b9c[];
extern int DAT_800d16a4;
char DAT_800d1f6c[8];
int FUN_80096090(int);
void FUN_800962b0(int, void*, int);
int FUN_80096230(int, void*);
void Pad_ActuatorOn__FUcUsUcUc(unsigned char a, unsigned short b, unsigned char c, unsigned char d){
  int s0 = 0;
  int s3;
  int r;
  if (DAT_800d16a4 != 7) s0 = a;
  s3 = (a != 0) << 4;
  r = FUN_80096090(s3);
  if (r != 0) {
    if (r == 1) DAT_800c0a48[s0].act[3] = 0;
    if (DAT_800c0a48[s0].act[3] == 0) {
      FUN_800962b0(s3, &DAT_800c0a48[a].act[0], 2);
      if (r == 2 || (r == 6 && FUN_80096230(s3, DAT_800d1f6c))) DAT_800c0a48[s0].act[3] = 1;
    }
    {
      int o = a * 0x16c;
      char* p = DAT_800c0b9c;
      char* q = p + 4;
      *(p + o + c) = d;
      {short* s = (short*)(q + o); short* t = c + s; *t = b;}
    }
  }
}
