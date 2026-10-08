/* FUN_80022aec (0x80022aec) */
struct V {
	int x, y, z;
};

int GameFMV_Active;
int GameFMV_NumSoundSources;

extern struct V DAT_800a6388[];

void FUN_80022aec(struct V *s) {
	int n;

	if (GameFMV_Active == 0) {
		n = GameFMV_NumSoundSources;

		if (n < 8) {
			DAT_800a6388[n] = *s;
			GameFMV_NumSoundSources = n + 1;
		}
	}
}
