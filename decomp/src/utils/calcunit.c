/* Utils_CalcUnit__FR7CVectorRC7CVector (0x80047a34) */
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
typedef struct { int x, y, z; } V;
extern long SquareRoot0(long);
void Utils_CalcUnit(V *out, V *in){
  VECTOR t;
  int len;
  t.vx = in->x >> 12; t.vy = in->y >> 12; t.vz = in->z >> 12;
  gte_ldlvl(&t); gte_sqr0(); gte_stlvnl(&t);
  len = SquareRoot0(t.vx + t.vy + t.vz);
  if (len) {
    out->x = in->x / len;
    out->y = in->y / len;
    out->z = in->z / len;
  } else {
    out->x = 0; out->y = 0; out->z = 0;
  }
}
