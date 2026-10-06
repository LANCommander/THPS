/* FUN_80060854 (0x80060854) */
typedef struct{unsigned char a,b,c,d,e[10];}R;
extern R DAT_800a684c[];
extern char DAT_800a1f50[],DAT_800a1f60[],DAT_800a1f78[],DAT_800a1f88[];
extern int DAT_800d1708;
int DAT_800d1d7c,DAT_800d1d80;
int FUN_8005e0e0(char**,int*,int,int,int*,int,int,int,int);
void FUN_8008c190(char*);
int FUN_80060854(int a){
  char*l[2];
  int k[2];
  int v,i,j;
  l[0]=DAT_800a1f50;
  l[1]=DAT_800a1f60;
  k[0]=0;
  k[1]=0;
  v=FUN_8005e0e0(l,k,2,112,&a,0,0,0,0);
  if(v==113){
    DAT_800d1d7c=1;
    DAT_800d1d80=1;
    for(i=0;i<11;i++){
      DAT_800a684c[i].a=0;
      DAT_800a684c[i].d=0;
      DAT_800a684c[i].c=0;
      DAT_800a684c[i].b=0;
      for(j=0;j<10;j++){
        DAT_800a684c[i].e[j]=255;
        DAT_800a684c[i].a+=5;
        DAT_800a684c[i].d+=1;
        DAT_800a684c[i].c+=1;
        DAT_800a684c[i].b+=1;
      }
    }
  }else if(v==114){
    DAT_800d1708=DAT_800d1708^1;
    if(DAT_800d1708==0)FUN_8008c190(DAT_800a1f78);
    else FUN_8008c190(DAT_800a1f88);
  }
  return -1;
}
