/* Spool_ClearEnvironmentRegions__Fv (0x8006fefc) */
int DAT_800d1ed0,DAT_800d1ed4,DAT_800d1ef0;
void FUN_8006fde4(int,int,int);
void Spool_RemoveUnusedTextures__Fv(void);
void Spool_ClearEnvironmentRegions__Fv(void){
  FUN_8006fde4(DAT_800d1ed0,0,0);
  FUN_8006fde4(DAT_800d1ed4,0,0);
  DAT_800d1ed0=-1;
  DAT_800d1ed4=-1;
  Spool_RemoveUnusedTextures__Fv();
  DAT_800d1ef0=0;
}
