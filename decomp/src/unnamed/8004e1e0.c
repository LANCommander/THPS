/* FUN_8004e1e0 (0x8004e1e0) */
extern int camDist;
extern int camPitch;
extern int camYOffset;
extern char *pCurrentViewport;

int CamPtIndex;

void FUN_8004e1e0(void) {
	char *p = pCurrentViewport;

	camDist = 290;
	camPitch = 150;
	CamPtIndex = 0;
	camYOffset = -108;
	*(short *)(p + 12) = 3413;
}
