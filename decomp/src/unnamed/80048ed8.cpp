/* Db_Vblank__Fv (0x80048ed8) flags=-fstructure-noalias */
/* C++ (DB.CPP). Demo twin Db_Vblank; THPS1 moved the demo's second loop into FUN_80048d24.
   Flips any buffer that finished drawing. The unused frame delta (a dead read of the volatile
   vblank counter, demo line 209) is what keeps &LastVblanks out of the loop's giv set. */
struct DISPENV { short d[10]; };
struct SDoubleBuffer {
	char Draw[0x5c];
	DISPENV Disp;         /* 0x5c */
	int Visible;          /* 0x70 */
	int RenderNow;        /* 0x74 */
	int Rendering;        /* 0x78 */
	int FlipNow;          /* 0x7c */
	int LastVblanks;      /* 0x80 */
	unsigned long OrderingTable[(0x80ac - 0x84) / 4];
};
extern SDoubleBuffer DAT_800a891c[2];
extern volatile int DAT_800d1a20;
extern "C" int FUN_8008ca0c(DISPENV *);
extern "C" void FUN_80048d24(void);

void Db_Vblank()
{
	int i;
	for (i = 0; i < 2; i++) {
		if (DAT_800a891c[i].FlipNow) {
			int frames = DAT_800d1a20 - DAT_800a891c[i].LastVblanks;
			FUN_8008ca0c(&DAT_800a891c[1 - i].Disp);
			DAT_800a891c[i].FlipNow = 0;
			DAT_800a891c[i].Visible = 1;
			DAT_800a891c[1 - i].Visible = 0;
			DAT_800a891c[i].LastVblanks = DAT_800d1a20;
		}
	}
	FUN_80048d24();

}
