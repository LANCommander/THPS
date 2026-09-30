/* removeBlack__11SlicedImage (0x800637d0) */
typedef struct { int pad0; int w, h; int pad1[2]; unsigned short *pix; int pad2[3]; int depth; } SlicedImage;
void SlicedImage_removeBlack(SlicedImage *s){
  if (s->depth == 16) {
    int n = s->w * s->h;
    unsigned short *p = s->pix;
    int i;
    for (i = 0; i < n; i++, p++)
      if (!*p) *p = 0x8000;
  }
}
