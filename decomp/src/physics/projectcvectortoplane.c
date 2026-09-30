/* ProjectCVectorToPlane__FP7CVectorG7SVECTOR (0x8002fff4) */
typedef struct{int x,y,z;}V;
typedef struct{short vx,vy,vz,pad;}SVECTOR;
extern int FUN_800720ec(V*,V*);
extern int FUN_80072090(int,int);
void ProjectCVectorToPlane(V*v,SVECTOR n){
  V t;
  int d;
  t.x=n.vx; t.y=n.vy; t.z=n.vz;
  d=FUN_800720ec(v,&t);
  v->x-=FUN_80072090(d,n.vx);
  v->y-=FUN_80072090(d,n.vy);
  v->z-=FUN_80072090(d,n.vz);
}
