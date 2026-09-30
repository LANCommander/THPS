/* Spool_GetModel__FUii (0x8006ee38) */
typedef struct{char name[10];unsigned char f0a,f0b;unsigned*models;unsigned*f10;char pad[0x2c];}SRegion;
extern SRegion DAT_800bf7a8[];
int Spool_GetModel__FUii(unsigned id,int region){
  unsigned n=DAT_800bf7a8[region].f10[-1];
  unsigned*m=DAT_800bf7a8[region].models;
  unsigned i;
  for(i=0;i<n;i++){
    if(*m==id)return i;
    m++;
  }
}
