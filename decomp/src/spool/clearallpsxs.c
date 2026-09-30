/* Spool_ClearAllPSXs__Fv (0x8006fd74) */
typedef struct{char name[10];unsigned char f0a,f0b;unsigned*models;unsigned*f10;char pad[0x2c];}SRegion;
extern SRegion DAT_800bf7a8[];
void Spool_Sync__Fv(void);
void Spool_ClearEnvironmentRegions__Fv(void);
void Spool_RemoveUnusedTextures__Fv(void);
void FUN_8006fde4(int,int,int);
void Spool_ClearAllPSXs__Fv(void){
  int i;
  Spool_Sync__Fv();
  Spool_ClearEnvironmentRegions__Fv();
  for(i=0;i<40;i++)
    if(!DAT_800bf7a8[i].f0b)FUN_8006fde4(i,1,0);
  Spool_RemoveUnusedTextures__Fv();
}
