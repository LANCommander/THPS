typedef struct{int x,y,z;}V;
V*op(V*p,const int*n){p->x<<=*n;p->y<<=*n;p->z<<=*n;return p;}
