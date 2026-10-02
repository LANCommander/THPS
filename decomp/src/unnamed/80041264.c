/* FUN_80041264 (0x80041264) */
typedef struct{char pad[8];short adj;short pad2;void(*fn)(char*,int);}VT;
extern char DAT_800a0218[];char DAT_800d1998[8];
void DeleteFrom__5CBodyPP5CBody(char*p,char*l);void SFX_Stop__FUi(int a);void FUN_8004d5d0(int a);void dt_6CBaddy(char*p,int a);void FUN_80043530(char*p);
void FUN_80041264(char*p,int f){
int i;
*(char**)(p+72)=DAT_800a0218;
DeleteFrom__5CBodyPP5CBody(p,DAT_800d1998);
if(*(int*)(p+556))SFX_Stop__FUi(*(int*)(p+556));
if(*(char**)(p+552)){char*o=*(char**)(p+552);VT*v=*(VT**)(o+68);v->fn(o+v->adj,3);}
if(*(int*)(p+548)){
for(i=0;i<*(unsigned short*)(p+544);i++){
char*o=*(char**)(*(int*)(p+548)+(i<<4)+12);
if(o){VT*v=*(VT**)(o+68);v->fn(o+v->adj,3);}
}
FUN_8004d5d0(*(int*)(p+548));
}
dt_6CBaddy(p,0);
if(f&1)FUN_80043530(p);
}
