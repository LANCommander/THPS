/* SetLine__5CMenuUc (0x80016708) */
typedef struct{unsigned short a,b,c,d;char pad[16];}SLine;
typedef struct{char pad[6];unsigned char line;char pad2[21];SLine l[15];}CMenu;
void SetLine__5CMenuUc(CMenu*m,unsigned char line){
  int i;
  m->line=line;
  for(i=0;i<15;i++){
    if(i==m->line){
      m->l[i].b=m->l[i].c;
    }else{
      unsigned short v=m->l[i].d;
      m->l[i].b=v;
      m->l[i].a=v;
    }
  }
}
