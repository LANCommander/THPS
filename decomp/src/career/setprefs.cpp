/* Options_SetPreferences__Fv (0x800101e4) */
/* C++ (CAREER.CPP). Demo twin; locals from its MAIN.SYM. Copies the default preferences into the
   career save's options (volumes, per-pad auto-kick/vibration/button mapping, display toggles,
   the HORSE word and the last high-score initials), sets the volume scalers, then remaps pads. */
struct SOptions {
	int SFXVolume;
	int MusicVolume;
	int OtherOptions[66];
	int AutoKickEnabled[2];        /* 0x110 */
	int VibrationEnabled[2];       /* 0x118 */
	int ControllerFunction[2][4];  /* 0x120 */
	char LastHighScoreInitials[4]; /* 0x140 */
	char pad144[0x184 - 0x144];
	int TrickTipsEnabled;    /* 0x184 */
	int ScoreDisplayEnabled; /* 0x188 */
	int HorseLen;            /* 0x18c */
	char HorseWord[16];      /* 0x190 */
};

struct SCareer {
	char pad0[0x830];
	SOptions Options; /* 0x830 */
};

extern SOptions DAT_800a4118;
extern SCareer DAT_800a6844;
extern int DAT_800d13cc, DAT_800d13d0;

extern "C" int FUN_8008b900(char *, const char *, ...); /* sprintf (demo twin) */
void Options_RemapControllers();

void Options_SetPreferences() {
	DAT_800a6844.Options.SFXVolume = DAT_800a4118.SFXVolume;
	DAT_800a6844.Options.MusicVolume = DAT_800a4118.MusicVolume;
	DAT_800a6844.Options.TrickTipsEnabled = DAT_800a4118.TrickTipsEnabled;
	DAT_800a6844.Options.ScoreDisplayEnabled = DAT_800a4118.ScoreDisplayEnabled;

	{
		int padNum;

		for (padNum = 0; padNum < 2; padNum++) {
			DAT_800a6844.Options.AutoKickEnabled[padNum] = DAT_800a4118.AutoKickEnabled[padNum];
			DAT_800a6844.Options.VibrationEnabled[padNum] = DAT_800a4118.VibrationEnabled[padNum];
			DAT_800a6844.Options.ControllerFunction[padNum][0] =
			    DAT_800a4118.ControllerFunction[padNum][0];
			DAT_800a6844.Options.ControllerFunction[padNum][1] =
			    DAT_800a4118.ControllerFunction[padNum][1];
			DAT_800a6844.Options.ControllerFunction[padNum][2] =
			    DAT_800a4118.ControllerFunction[padNum][2];
			DAT_800a6844.Options.ControllerFunction[padNum][3] =
			    DAT_800a4118.ControllerFunction[padNum][3];
		}
	}

	{
		int i;

		DAT_800d13cc = DAT_800a6844.Options.SFXVolume * 1365;
		DAT_800d13d0 = DAT_800a6844.Options.MusicVolume * 1365;
		FUN_8008b900(DAT_800a6844.Options.HorseWord, DAT_800a4118.HorseWord);

		DAT_800a6844.Options.HorseLen = DAT_800a4118.HorseLen;

		for (i = DAT_800a4118.HorseLen; i < 11; i++)
			DAT_800a6844.Options.HorseWord[i] = 0;

		FUN_8008b900(DAT_800a6844.Options.LastHighScoreInitials,
		             DAT_800a4118.LastHighScoreInitials);
	}

	Options_RemapControllers();
}
