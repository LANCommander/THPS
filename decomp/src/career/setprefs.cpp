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

extern SOptions GPreferences;
extern SCareer GCareer;
extern int SFXLEVEL, XALEVEL;

extern "C" int FUN_8008b900(char *, const char *, ...); /* sprintf (demo twin) */
void Options_RemapControllers();

void Options_SetPreferences() {
	GCareer.Options.SFXVolume = GPreferences.SFXVolume;
	GCareer.Options.MusicVolume = GPreferences.MusicVolume;
	GCareer.Options.TrickTipsEnabled = GPreferences.TrickTipsEnabled;
	GCareer.Options.ScoreDisplayEnabled = GPreferences.ScoreDisplayEnabled;

	{
		int padNum;

		for (padNum = 0; padNum < 2; padNum++) {
			GCareer.Options.AutoKickEnabled[padNum] = GPreferences.AutoKickEnabled[padNum];
			GCareer.Options.VibrationEnabled[padNum] = GPreferences.VibrationEnabled[padNum];
			GCareer.Options.ControllerFunction[padNum][0] =
			    GPreferences.ControllerFunction[padNum][0];
			GCareer.Options.ControllerFunction[padNum][1] =
			    GPreferences.ControllerFunction[padNum][1];
			GCareer.Options.ControllerFunction[padNum][2] =
			    GPreferences.ControllerFunction[padNum][2];
			GCareer.Options.ControllerFunction[padNum][3] =
			    GPreferences.ControllerFunction[padNum][3];
		}
	}

	{
		int i;

		SFXLEVEL = GCareer.Options.SFXVolume * 1365;
		XALEVEL = GCareer.Options.MusicVolume * 1365;
		FUN_8008b900(GCareer.Options.HorseWord, GPreferences.HorseWord);

		GCareer.Options.HorseLen = GPreferences.HorseLen;

		for (i = GPreferences.HorseLen; i < 11; i++)
			GCareer.Options.HorseWord[i] = 0;

		FUN_8008b900(GCareer.Options.LastHighScoreInitials,
		             GPreferences.LastHighScoreInitials);
	}

	Options_RemapControllers();
}
