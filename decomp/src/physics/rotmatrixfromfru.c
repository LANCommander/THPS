/* RotMatrixFromFRUVectors__6CBruce (0x8003a5fc) */
typedef struct{int x,y,z;}V;
typedef struct{short m[3][3];long t[3];}MATRIX;
typedef struct{char _0[4];V pos;char _10[0x78c-0x10];MATRIX m;MATRIX tm;V tpos;V F;V R;V U;}CBruce;
void RotMatrixFromFRUVectors(CBruce*b){
  b->m.m[0][0]=b->R.x; b->m.m[1][0]=b->R.y; b->m.m[2][0]=b->R.z;
  b->m.m[0][1]=b->U.x; b->m.m[1][1]=b->U.y; b->m.m[2][1]=b->U.z;
  b->m.m[0][2]=b->F.x; b->m.m[1][2]=b->F.y; b->m.m[2][2]=b->F.z;
}
