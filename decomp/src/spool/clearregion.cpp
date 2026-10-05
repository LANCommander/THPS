/* ClearRegion__Fiii (0x8006fde4) */
/* C++ (SPOOL.CPP). Demo twin; locals and blocks from its MAIN.SYM. Releases a loaded region: drops
   its texture usage counts and, unless it stays in memory, clears the region record, detaches its
   environment and frees the PSX file. Optionally purges unused textures. */
typedef unsigned char uchar;
typedef unsigned int uint;
struct SPSXRegion {
	uchar Used;               /* 0 */
	char pad1[10 - 1];
	uchar Loaded;             /* 10 */
	uchar m0B;                /* 11 */
	char padc[16 - 12];
	uint *pModels;            /* 0x10 */
	uint *pPSX;               /* 0x14 */
	int m18;                  /* 0x18 */
	char pad1c[0x20 - 0x1c];
	int m20;                  /* 0x20 */
	char pad24[0x28 - 0x24];
	int m28;                  /* 0x28 */
	int m2C;                  /* 0x2c */
	char pad30[0x33 - 0x30];
	uchar m33;                /* 0x33 */
	uchar m34;                /* 0x34 */
	char pad35[64 - 0x35];
};
extern SPSXRegion DAT_800bf7a8[];
int DAT_800d1ed0[2];
void DecrementTextureUsage(int);
int Spool_GetEnvIndex(int);
void DetachOldEnviro(uchar);
void Spool_RemoveUnusedTextures(void);
extern "C" {
void FUN_80082738(int);
void FUN_8004d5d0(void *);
}

void ClearRegion(int Region, int cleanuptextures, int KeepInMemory)
{
	if (Region == -1)
		return;
	if (!DAT_800bf7a8[Region].Used)
		return;
	DecrementTextureUsage(Region);
	if (!KeepInMemory) {
		DAT_800bf7a8[Region].m18 = 0;
		DAT_800bf7a8[Region].m2C = 0;
		DAT_800bf7a8[Region].m28 = 0;
		DAT_800bf7a8[Region].m0B = 0;
		DAT_800bf7a8[Region].Loaded = 0;
		DAT_800bf7a8[Region].m20 = 0;
		DAT_800bf7a8[Region].pModels = 0;
		DAT_800bf7a8[Region].Used = 0;
		DAT_800bf7a8[Region].m33 = 0;
		DAT_800bf7a8[Region].m34 = 0;
		{
			int EnvIndex = Spool_GetEnvIndex(Region);
			if (EnvIndex != -1) {
				FUN_80082738(EnvIndex);
				DetachOldEnviro(EnvIndex);
				DAT_800d1ed0[EnvIndex] = -1;
			}
		}
		FUN_8004d5d0(DAT_800bf7a8[Region].pPSX);
		DAT_800bf7a8[Region].pPSX = 0;
	}
	if (cleanuptextures)
		Spool_RemoveUnusedTextures();
}
