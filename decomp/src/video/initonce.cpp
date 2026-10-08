/* Video_InitOnce__Fv (0x800694a0) flags=-fstructure-noalias */
/* C++ (VIDEO.CPP). Demo twin (THPS1 allocates bigger replay buffers and skips a header); locals from
   its MAIN.SYM. Allocates player 1's replay buffer, and player 2's in a two-player game. */
struct SVideoInfo {
	int Mode;
	char *pBuffer; /* 4 */
	char *pPos;    /* 8 */
	char pad0c[0xc0 - 12];
};

extern SVideoInfo DAT_800bf318;
extern SVideoInfo DAT_800bf3d8;
extern int DAT_800d1780;

extern "C" char *Mem_NewX__FUiii(int, int, int);

void Video_InitOnce() {
	DAT_800bf318.pBuffer = DAT_800bf318.pPos = Mem_NewX__FUiii(24576, 1, 1);
	DAT_800bf318.pPos += 576;

	if (DAT_800d1780 == 2) {
		DAT_800bf3d8.pBuffer = DAT_800bf3d8.pPos = Mem_NewX__FUiii(24576, 1, 1);
		DAT_800bf3d8.pPos += 576;
	} else {
		DAT_800bf3d8.pBuffer = DAT_800bf3d8.pPos = 0;
	}
}
