/* Spool_ClearEnvironmentRegions__Fv (0x8006fefc) */
int DAT_800d1ed0, DAT_800d1ed4, DAT_800d1ef0;

void ClearRegion__Fiii(int, int, int);
void Spool_RemoveUnusedTextures__Fv(void);

void Spool_ClearEnvironmentRegions__Fv(void) {
	ClearRegion__Fiii(DAT_800d1ed0, 0, 0);
	ClearRegion__Fiii(DAT_800d1ed4, 0, 0);

	DAT_800d1ed0 = -1;
	DAT_800d1ed4 = -1;
	Spool_RemoveUnusedTextures__Fv();

	DAT_800d1ef0 = 0;
}
