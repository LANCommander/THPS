/* FUN_80024258 (0x80024258) */
/* CalcPolyBufferEnd: the demo's MAIN.CPP twin used a fixed POLYBUFFERSIZE; THPS1 sizes the
   primitive buffer per level and per player count. */
struct SDoubleBuffer {
	char pad0[0x80a8];
	unsigned long Prims;		/* 0x80a8 */
};
struct SLevel {
	char pad0[0x50];
	int PolyBufferExtra[2];		/* 0x50, indexed by number of players - 1 */
	char pad58[120 - 0x58];
};
extern SDoubleBuffer *DAT_800d1a48;	/* pDoubleBuffer */
extern int DAT_800d1e28;		/* GLevel */
int DAT_800d1780;			/* number of players */
extern SLevel DAT_800a5398[];		/* Levels */
unsigned long DAT_800d177c;		/* PolyBufferEnd */

#define POLYBUFFERSIZE (DAT_800a5398[DAT_800d1e28].PolyBufferExtra[DAT_800d1780 - 1] + 0x17c00)

void FUN_80024258(void)
{
	unsigned long Prims = DAT_800d1a48->Prims;
	int Size = POLYBUFFERSIZE;
	DAT_800d177c = (Prims + Size - 256) & 0x7fffffff;
}
