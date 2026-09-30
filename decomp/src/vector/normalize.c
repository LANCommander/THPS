/* CVector::Normalize (0x8004d980). Retail never reloads z: it stores (y/len)/len there (an original bug). */
typedef struct{int x,y,z;}V;
extern int Length__C7CVector(V*);
void Normalize(V*v){
  int l=Length__C7CVector(v);
  v->x=v->x/l;v->y=v->y/l;v->z=v->y/l;
}
