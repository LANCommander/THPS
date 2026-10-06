/* RunAnim__6CSuperiiii (0x80043e0c) */
/* C++ (OB.CPP). Demo twin (same shape); locals from its MAIN.SYM. Starts an animation: clamps the
   anim index to the model's table, then the from/to frames (-1 = last), and sets the play direction.
   The direction byte is signed so its -1 shares the register of the "from == -1" test. */
typedef struct{char p[0x18]; unsigned int* anims; char q[0x40-0x1c];}R;
extern R DAT_800bf7a8[] __attribute__((section(".data")));
class CSuper {
public:
  char p0[0x1b];
  unsigned char type;
  char p1[0x144-0x1c];
  short a144;
  unsigned short anim;
  unsigned char f148; signed char f149; unsigned char f14a, f14b;
  unsigned short f14c;
  unsigned char nframes;
  unsigned char f14f;
  void RunAnim(int anim, int from, int to, int to2);
};
void CSuper::RunAnim(int a, int from, int to, int to2){
  anim = a;
  if (anim >= *DAT_800bf7a8[type].anims)
    anim = 46;
  nframes = ((unsigned char*)DAT_800bf7a8[type].anims)[anim*8 + 8];
  if (from == -1)
    from = nframes - 1;
  if (to == -1)
    to = nframes - 1;
  if (from < 0)
    from = 0;
  if (to < 0)
    to = 0;
  if (from >= nframes)
    from = nframes - 1;
  if (to >= nframes)
    to = nframes - 1;
  f148 = 0;
  if (from >= to) {
    if (to < from) f149 = -1;
    else f149 = 0;
  } else f149 = 1;
  a144 = from;
  f14a = to;
  f14b = to2;
  f14c = 0;
  f14f = (short)from == (signed char)to;
}
