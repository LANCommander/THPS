/* FUN_80045538 (0x80045538) */
typedef struct{int x,y,z,pad;}V;
typedef struct{unsigned short w0,w2,w4,w6;unsigned char b8,p9,b10,p11,b12,p13,b14,p15,b16,p17,b18;}P;
typedef struct{int a;char p[3];unsigned char f7;}CP;
short** DAT_800d19e8;
extern int DAT_800d186c;
void FUN_80045268(int,short**);
CP* GetCommandPoint__Fi(int,short**);
void FUN_80046374(int,int,int);
P* Trig_GetPosition__FR7CVectori(V*,int);
int FUN_80027d08(int);
void FUN_8001f614(int,V*,int,int,int,int,int,int,int,int,int,int,int);
void TrickOb_DarkenNode__Fi(int,short**);
int __nw__5CItemUi(int,short**);
void FUN_8004f684(int,int);
void FUN_80045538(int idx){
  V v;
  P*p;
  CP*cp;
  int o,o2;
  switch(*DAT_800d19e8[idx]){
  case 5:
  case 7:
  case 1:
    FUN_80045268(idx,DAT_800d19e8);
    break;
  case 6:
    cp=GetCommandPoint__Fi(idx,DAT_800d19e8);
    cp->f7=cp->f7+1;
    FUN_80046374(cp->a,idx,0);
    break;
  case 501:
    p=Trig_GetPosition__FR7CVectori(&v,idx);
    DAT_800d186c=0;
    o=FUN_80027d08(100);
    if(o)FUN_8001f614(o,&v,idx,p->w0,p->w2,p->w4,p->w6,p->b8,p->b10,p->b12,p->b14,p->b16,p->b18);
    DAT_800d186c=1;
    break;
  case 10:
  case 11:
    o2=__nw__5CItemUi(44,DAT_800d19e8);
    if(o2)FUN_8004f684(o2,idx);
    break;
  case 14:
  case 12:
    TrickOb_DarkenNode__Fi(idx,DAT_800d19e8);
    break;
  }
}
