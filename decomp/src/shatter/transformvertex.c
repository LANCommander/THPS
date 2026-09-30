/* TransformVertex__FR7CVectorP7SVECTORPUci (0x800216d0) */
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
typedef struct{int x,y,z;}V;
extern V* __als__7CVectorRCi(V*,const int*);
void TransformVertex(V* out, SVECTOR* verts, unsigned char* idx, int i){
  int s;
  gte_ldv0(&verts[idx[i]]);
  gte_rtv0tr();
  gte_stlvnl(out);
  s = 12;
  __als__7CVectorRCi(out, &s);
}
