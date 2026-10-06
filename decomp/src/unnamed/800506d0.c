/* FUN_800506d0 (0x800506d0) flags=-fstructure-noalias */
struct E{char pad[8];char*n8;char pad2[52];char*name;char q[272];};
struct V{int x,y,z;};
struct B{int vt;struct V pos;char pad[16];int col;};
static inline void Set(struct V*v,int _x,int _y,int _z){v->x=_x;v->y=_y;v->z=_z;}
extern struct E DAT_800a44fc[];extern char DAT_800be3f8[];
int DAT_800d1ba8;int DAT_800d22a4;
char* FUN_800434d4(int n);char* FUN_80041e5c(char*p);void InitItem__6CBrucePc(char*t,char*n);void CycleAnim__6CSuperiSc(char*t,int a,signed char c);
void FUN_8008b238(char*m); /* identity-matrix init, one arg */
char* FUN_800506d0(int idx){
char*p;
p=FUN_800434d4(3612);
if(p)p=FUN_80041e5c(p);
*(int*)(p+744)=idx;
InitItem__6CBrucePc(p,DAT_800a44fc[idx].n8);
*(int*)(p+336)=0x10000;
CycleAnim__6CSuperiSc(p,0,1);
{struct B*b=(struct B*)p;
b->col=0x404040;
Set(&b->pos,DAT_800d1ba8,DAT_800d22a4,0x30000);}
FUN_8008b238(p+1932);
if(DAT_800a44fc[idx].name[0]==82||DAT_800a44fc[idx].name[0]==114)*(int*)(p+308)|=2;
*(char**)(p+60)=DAT_800be3f8;
return p;
}
