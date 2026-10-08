/* DecrementTextureUsage__Fi (0x8006f178) */
/* C++ (SPOOL.CPP). Demo twin (the demo version also skips regions of type 2); locals from its
   MAIN.SYM. Walks the region's texture checksum table (after the model table in its PSX file) and
   drops each texture's usage count. */
typedef unsigned short ushort;
typedef unsigned int uint;

struct Texture {
	char pad0[16];
	ushort Usage; /* 16 */
};

struct SPSXRegion {
	char pad0[16];
	uint *pModels; /* 0x10 */
	uint *pPSX;    /* 0x14 */
	char pad18[64 - 0x18];
};

extern SPSXRegion DAT_800bf7a8[];

uint *Spool_SkipPackets(uint *);

void DecrementTextureUsage(int region) {
	uint *pPSX;
	uint *pNumModels;
	uint NumModels;
	uint *ChecksumTable;
	uint NumChecksums;

	pPSX = DAT_800bf7a8[region].pPSX;
	pNumModels = DAT_800bf7a8[region].pModels;
	NumModels = pNumModels[-1];
	ChecksumTable = Spool_SkipPackets(pPSX) + (NumModels + 1);
	NumChecksums = ChecksumTable[-1];

	{
		int i;

		for (i = 0; i < NumChecksums; i++)
			((Texture *)ChecksumTable[i])->Usage--;
	}
}
