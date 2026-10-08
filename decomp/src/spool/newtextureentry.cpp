/* NewTextureEntry__FUi (0x8006ef30) */
/* C++ (SPOOL.CPP). Demo twin; locals from its MAIN.SYM. Allocates a texture entry for a checksum
   and links it at the head of its hash bucket (low 9 bits of the checksum). */
typedef unsigned int uint;

struct Texture {
	char pad0[16];
	uint Usage : 16; /* 16 */
	uint Flags : 4;
	uint pad : 12;
	uint Checksum; /* 20 */
	char pad18[8];
	Texture *pNext; /* 32 */
	Texture *pPrev; /* 36 */
};

extern Texture *TextureChecksumHashTable[];

extern "C" Texture *Mem_NewX__FUiii(int, int, int);

Texture *NewTextureEntry(uint checksum) {
	Texture *pNew = Mem_NewX__FUiii(40, 0, 1);
	uint Lower = checksum & 511;

	pNew->pNext = TextureChecksumHashTable[Lower];
	pNew->pPrev = 0;
	TextureChecksumHashTable[Lower] = pNew;

	if (pNew->pNext)
		pNew->pNext->pPrev = pNew;

	pNew->Checksum = checksum;
	pNew->Flags = 0;
	pNew->Usage = 0;
	return pNew;
}
