/* GetFaceFlags__FP9SLineInfo (0x8002ee6c) */
typedef struct{unsigned flags0;int _4,_8;unsigned flags;}SFace;
typedef struct{char _0[0x68];int hit;char _6c[0x80-0x6c];SFace*face;}SLineInfo;
int DAT_800d1974,DAT_800d1978,DAT_800d197c,DAT_800d1980,DAT_800d1984;
void GetFaceFlags(SLineInfo*li){
  if(li->hit){
    SFace*f=li->face;
    unsigned fl=f->flags;
    DAT_800d1974=(fl>>16)&0x40;
    DAT_800d1978=!(fl&0x1000000);
    DAT_800d197c=!(fl&0x800000);
    DAT_800d1980=f->flags0&0x80;
    DAT_800d1984=((fl>>16)&0x1e00)>>9;
  }
}
