/* __amd__8CSVectorRC9CFriction (0x8004e074) */
typedef struct{short x,y,z;}S;
typedef struct{unsigned char x,y,z;}CFriction;
S*op(S*v,const CFriction*f){
  v->x-=v->x>>f->x;
  v->y-=v->y>>f->y;
  v->z-=v->z>>f->z;
  return v;
}
