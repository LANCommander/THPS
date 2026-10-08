/* Video_InitOnce__Fv (0x800694a0) flags=-fstructure-noalias */
/* C++ (VIDEO.CPP). Demo twin (THPS1 allocates bigger replay buffers and skips a header); locals from
   its MAIN.SYM. Allocates player 1's replay buffer, and player 2's in a two-player game. */
struct SVideoInfo {
	int Mode;
	char *pBuffer; /* 4 */
	char *pPos;    /* 8 */
	char pad0c[0xc0 - 12];
};

extern SVideoInfo GVInfo1;
extern SVideoInfo GVInfo2;
extern int GNumberOfPlayers;

extern "C" char *Mem_NewX__FUiii(int, int, int);

void Video_InitOnce() {
	GVInfo1.pBuffer = GVInfo1.pPos = Mem_NewX__FUiii(24576, 1, 1);
	GVInfo1.pPos += 576;

	if (GNumberOfPlayers == 2) {
		GVInfo2.pBuffer = GVInfo2.pPos = Mem_NewX__FUiii(24576, 1, 1);
		GVInfo2.pPos += 576;
	} else {
		GVInfo2.pBuffer = GVInfo2.pPos = 0;
	}
}
