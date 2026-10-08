/* strNext__Fv (0x80023e88) */
int GameFMV_CurrentFrame, GameFMV_EndFrame, GameFMV_RewindSwitch;

int FUN_800911fc(int *, int **);

int strNext(void) {
	int addr;
	int *hdr;

	if (FUN_800911fc(&addr, &hdr))
		return 0;

	GameFMV_CurrentFrame = hdr[2];

	if (GameFMV_CurrentFrame >= GameFMV_EndFrame)
		GameFMV_RewindSwitch = 1;

	return addr;
}
