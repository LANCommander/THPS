/* Front_Update__Fv (0x8001a6f8) flags=-fstructure-noalias */
/* C++ (FRONT.CPP). Fuzzy demo twin (0.66); locals and blocks from its MAIN.SYM (SoundEffect,
   SwitchOffPauseMode, Activated/GoBack/AnyButton/Start, the StartSelectPressed statics, the
   case 0 / case 20 pSkater pair, the restarts-menu head[4], the horse-word UpDown/lastAlpha/
   firstAlpha). The in-game front end: soft reset on Start+Select, then one case per paused
   status (pause menu, restarts, yes/no menus, end-of-level/heat menus, horse word, high-score
   initials, sound levels), then leaving pause mode. THPS1 drops the MPC states, so its
   EPausedStatus numbering is the demo's minus 8 from STATUS_ENDGAME on.
   Levers: -fstructure-noalias (GSkater[1] loaded above the GSkater[0] field store); Vblanks/
   Xblanks volatile; the "retry" text and the sound-level value are single ?: expressions; the
   replay choices store GVideoReplay, EndCode, then SwitchOffPauseMode (one cross-jumped tail);
   `else Front_OnTime++` tails; the sfx-volume temp `v` lengthens the GCareer-high gcse pseudo
   so the GameText-high one loses s0 (retail's s1/s2 for it and SoundEffect).
   Residue (2316/2318): in both sfx blocks retail schedules `addiu s0,t0,%lo(GCareer)` before
   `sra v0,v0,31`; the temp puts it after. */
typedef unsigned char uchar;
typedef unsigned int uint;

enum EPausedStatus {
	STATUS_NORMAL, STATUS_PAUSEDMENU, STATUS_SKIPTORESTART, STATUS_REALLYQUIT,
	STATUS_PADUNPLUGGED, STATUS_SAVEGAME, STATUS_QUITSAVE, STATUS_MEDALSAVE,
	STATUS_ENDLEVELFADESCREEN, STATUS_DOSAVEFADESCREEN, STATUS_NOSAVEFADESCREEN,
	STATUS_GOTTAPE, STATUS_TAPESAVE, STATUS_STATS, STATUS_ENDINGSCREEN,
	STATUS_VIDEOSCREEN, STATUS_VIDEOSCREEN2, STATUS_REALLYMAINMENU, STATUS_MEMCARDMENUS,
	STATUS_ENDHEAT, STATUS_ENDHEATREPLAY, STATUS_ENDHEATJUDGES, STATUS_ENDHEATLADDER,
	STATUS_ENDHEATWINLOSE, STATUS_ENDHEATMENU, STATUS_ENDHEATVIDEOMENU, STATUS_BEGINHEAT,
	STATUS_ENDGAME, STATUS_ENDGAMEALLGOLD, STATUS_ENDGAMEPLAYERMOVIE, STATUS_ENDGAMEBAILMOVIE,
	STATUS_ENDGAMESAVE, STATUS_ENDGAMECREDITS, STATUS_STARTHORSE, STATUS_CHANGEHORSEWORD,
	STATUS_LOADSUCCESS, STATUS_LOADFAILED, STATUS_HIGHSCORE, STATUS_SETSOUNDLEVELS
};
enum EMemCardState { SVSTATUS_CHECKINGCARDPAUSE };
enum ESaveAction { SAVE_VIDEO, SAVE_GAME };
enum EVideoMode { VIDEO_OFF, VIDEO_RECORD, VIDEO_PLAYBACK };

struct SButton {
	uchar Pressed;
	uchar Triggered;
	int PressedTime;
	int ReleasedTime;
	int TriggeredTime;
};
struct SControl {
	SButton Triangle, Square, Circle, X;
	SButton LeftOne, LeftTwo, RightOne, RightTwo;
	SButton Left, Right, Up, Down;
	SButton AnalogueLeft, AnalogueRight, Start, Select;
	SButton Crouch, Jump, SmartBomb, SelectWeapon;
	uchar AnaloguePotMapping[4];
	uchar Raw[4];
	char Analogue[4];
	int Type;
	int pad150[7];
};
struct SVideoInfo {
	EVideoMode VideoMode;
	int pad4[6];
	uint NumFrames;
	int pad20[11];
	int ReplayHighlight;
	int pad50[27];
	int PlaybackFrozen;
};
struct SLevelInfo {
	int pad0[3];
	int mNoHighScores;
	int pad10[26];
};
struct SHighScore {
	char Name[4];
	uchar Skater;
	uint Score;
};
struct SCareer {
	int pad0[41];
	SHighScore HighScores[20][8];   /* 0x0a4 */
	int pad824[3];
	int SfxVol;                     /* 0x830 */
	int MusicVol;                   /* 0x834 */
	int pad838[78];
	char PlayerName[4];             /* 0x970 */
	int pad974[18];
	int HorseLen;                   /* 0x9bc */
	char HorseWord[12];             /* 0x9c0 */
};
struct SPreferences {
	int SfxVol;
	int MusicVol;
	int pad8[97];
	int HorseLen;                   /* 0x18c */
	char HorseWord[12];             /* 0x190 */
};
struct CBruce {
	char pad0[0x1c];
	CBruce *mpNext;                 /* 0x01c */
	char pad20[0x310 - 0x20];
	int m310;
	int m314;
	char pad318[0x330 - 0x318];
	int m330;
};
struct SEntry {
	char *pString;
	short CurrentScale;
	short TargetScale;
	short HiScale;
	short LowScale;
	uchar Clearance;
	uchar Visible;
	uchar Enabled;
	uchar HiR, HiG, HiB;
	uchar LowR, LowG, LowB;
	uchar FadeUpCounter;
};
class CItem {
public:
	virtual ~CItem();
	void *operator new(unsigned int) throw();
};
class CMenu : public CItem {
public:
	uchar mJustification;
	uchar mRep;
	uchar mLine;
	uchar mHasCursor;
	uchar mCursorLine;
	uchar mNumLines;
	int mX;
	int mY;
	int mLineSep;
	SEntry mEntry[15];
	CMenu(int, int, uchar, int, int, int);
	void Update();
	void AddEntry(const char *);
	void EntryOn(const char *);
	void EntryOff(const char *);
	int IsEntryOn(const char *);
	int ChoiceIs(const char *);
	int FindEntry(const char *);
	void SetLine(uchar);
	void CentreY();
};
class CTape {
public:
	char pad0[0x48];
	virtual ~CTape();
	static int DisplayContinueButton();
};
class FallingTextEffect {
public:
	int handleComplete();
};

extern SControl DAT_800c0a48[2];                /* Pad */
extern SVideoInfo DAT_800bf318;                 /* GVInfo1 */
extern SVideoInfo DAT_800bf3d8;                 /* GVInfo2 */
extern SLevelInfo DAT_800a5398[];               /* Levels */
extern SCareer DAT_800a6844;                    /* GCareer */
extern SPreferences DAT_800a4118;               /* GPreferences */
extern char *DAT_800a5d5c[];                    /* GameText */
extern char DAT_800a5d2c[];                     /* soundBuf */
extern char DAT_800a5d44[];                     /* musicBuf */
extern char *DAT_800a8788[];                    /* CheatRestarts */
extern char *DAT_800a87d8[];                    /* HorseRestarts */
extern CTape *DAT_800a5b14[];                   /* GTape */
extern FallingTextEffect DAT_800a5b28[];        /* GHorseFallingText */
extern char DAT_800d14e0[];
extern CBruce *DAT_800d19a4;                    /* MechList */
extern CBruce *DAT_800d17c8;                    /* GSkater[0] */
extern CBruce *DAT_800d17cc;                    /* GSkater[1] */
extern volatile uint DAT_800d1a20;                      /* Vblanks */
extern volatile int DAT_800d1a24;                       /* Xblanks */
extern int DAT_800d16e0;                        /* EndCode */
extern int DAT_800d16fc;                        /* GameFrozen */
extern int DAT_800d1780;                        /* GNumberOfPlayers */
extern int DAT_800d1cb0;                        /* DemoTimer */
extern int DAT_800d1770;
extern int DAT_800d1e28;                        /* GLevel */
extern int DAT_800d16a4;                        /* GGame */
extern int DAT_800d1710;                        /* Cheat_RestartSkip */
extern int DAT_800d1fec;                        /* CheatCheck */
extern int DAT_800d1784;                        /* GState */
extern int DAT_800d1788;                        /* GSpin */
extern int DAT_800d17c0;                        /* GHorseClearInput2 */
extern int DAT_800d19d8;                        /* NumCheatRestarts */
extern int DAT_800d10f8;                        /* GLoadedCareerIsSaved */
extern int DAT_800d1c9c;
extern int DAT_800d1de8;                        /* GVideoReplay */
extern int DAT_800d1100;
extern int DAT_800d17b8;                        /* GHorseCursorPos */
extern int DAT_800d17bc;                        /* GHorseWaitTime */
extern int DAT_800d17a0;                        /* GHorseMode */
extern int DAT_800d17ac;                        /* GHorseRestart */
extern int DAT_800d17a4;                        /* GHorseScore */
extern int DAT_800d17b0;                        /* GHorseLetters[0] */
extern int DAT_800d17b4;                        /* GHorseLetters[1] */
extern int DAT_800d179c;                        /* GHorsePlayer */
extern int DAT_800d16cc;                        /* GHorseWordChosen */
extern int DAT_800d17a8;                        /* GHorseDoneStart */
extern int DAT_800d17e8;                        /* GClear1 */
extern int DAT_800d17ec;                        /* GClear2 */

EPausedStatus DAT_800d13e8;                     /* Status */
int DAT_800d13e4;                               /* GSoftResetEnabled */
int DAT_800d14d8;                               /* StartSelectPressed */
uint DAT_800d14dc;                              /* VblanksWhenStartSelectFirstPressed */
int DAT_800d140c;                               /* GamePaused */
int DAT_800d1410;                               /* WobbleAmplitude */
int DAT_800d1414;                               /* WobbleT */
CMenu *DAT_800d1428;                            /* pYesNoMenu */
CMenu *DAT_800d142c;                            /* pESMenu */
CMenu *DAT_800d1430;                            /* pVSMenu */
CMenu *DAT_800d1434;                            /* pVS2Menu */
CMenu *DAT_800d1438;                            /* pVS3Menu */
CMenu *DAT_800d143c;                            /* pEHMenu */
CMenu *DAT_800d1440;                            /* pSoundMenu */
CMenu *DAT_800d1474;                            /* pPausedMenu */
CMenu *DAT_800d1478;                            /* pRestartsMenu */
int DAT_800d151c;                               /* GStart1 */
int DAT_800d1520;                               /* GStart2 */
int DAT_800d1514;                               /* Front_OnTime */
int DAT_800d13d8;                               /* GRollCredits */
int DAT_800d13dc;                               /* GHighScoreLineIndex */
int DAT_800d13e0;                               /* GHighScoreInitialCursorPos */
int DAT_800d13c4;                               /* GHorseContinue */
int DAT_800d14f4;                               /* GHorseSounded */
int DAT_800d14fc;                               /* NextHorseMode */
int DAT_800d1500;                               /* NextHorsePlayer */
int DAT_800d1504;                               /* NextHorseScore */
int DAT_800d1508;                               /* NextHorseRestart */
int DAT_800d150c;                               /* NextHorseLetters[0] */
int DAT_800d1510;                               /* NextHorseLetters[1] */
int DAT_800d13cc;                               /* SFXLEVEL */
int DAT_800d13d0;
int DAT_800d21fc;                               /* soundVol */
int DAT_800d2200;                               /* musicVol */

void Front_GetButtons(int &, int &, int &, int &);
int Card_CheckStatus(int, int);
void Horse_Reset();
EPausedStatus Front_MemCardUpdate();
void Video_Stop(CBruce *);
void Video_Start(CBruce *, EVideoMode, int, int);
void Front_SwitchOnVideoScreen();
void Mess_DeleteAll();
void Pad_ClearTriggers(SControl *);
void Pad_ActuatorOff(uchar, uchar);
void SFX_Pause();
void SFX_Unpause();
int SFX_PlayX(unsigned int, short, int);
int Shell_DoCheatProcessing();
void Game_Over();
void Competition_Init();
int Utils_CompareStrings(const char *, const char *, unsigned int);
void Trig_SetRestart(char *);
void Front_SetSaveAction(ESaveAction);
void Front_InitMemCardMenus(int, EMemCardState, EPausedStatus);
bool InCompetition();
bool Competition_IsOver();
void Flash_Fade(int, int);
void Flash_Update();
int Flash_FadeFinished();
void Flash_Reset();
void Video_Cleanup();
void Video_SortAndMerge();
int GetUpDown();
void InitStatsSwisch();
void Competition_EndGameLogic(EPausedStatus &, int &);
void Competition_WinLoseLogic(EPausedStatus &, int &);
void Competition_LadderLogic();
int Competition_LadderFullyDisplayed();
int Competition_NewHeat();
void Competition_JudgeLogic();
int Competition_JudgeFullyDisplayed();
void RestartCompFrig();
extern "C" {
int FUN_8008b900(char *, const char *, ...);
void FUN_8008f19c(int, int, int);
void FUN_8008f0ec(int);
void FUN_8008f4d4(int, int, int);
void FUN_80023528(void);
void FUN_80076484(void);
void FUN_80076494(void);
}

void Front_Update()
{
	int SoundEffect = -1;
	int SwitchOffPauseMode = 0;
	int Activated;
	int GoBack;
	int AnyButton;
	int Start;

	if ((!DAT_800c0a48[0].LeftOne.Pressed || DAT_800d13e8 != STATUS_PAUSEDMENU) && DAT_800d13e8 != STATUS_MEMCARDMENUS)
		Front_GetButtons(Activated, GoBack, AnyButton, Start);

	if (DAT_800d13e8)
		Card_CheckStatus(0, 0);

	if ((DAT_800d13e4 && DAT_800c0a48[0].Select.Pressed && DAT_800c0a48[0].Start.Pressed) ||
		(DAT_800c0a48[1].Select.Pressed && DAT_800c0a48[1].Start.Pressed))
	{
		if (!DAT_800d14d8)
		{
			DAT_800d14d8 = 1;
			DAT_800d14dc = DAT_800d1a20;
		}
		if (DAT_800d1a20 - DAT_800d14dc > 120)
		{
			DAT_800d14d8 = 0;
			DAT_800d16e0 = 8;
			SwitchOffPauseMode = 1;
			Horse_Reset();
		}
	}
	else
	{
		DAT_800d14d8 = 0;
	}
	DAT_800d13e4 = 1;

	switch (DAT_800d13e8)
	{
	case STATUS_MEMCARDMENUS:
		DAT_800d13e8 = Front_MemCardUpdate();
		break;

	case STATUS_NORMAL:
		{
			CBruce *pSkater = DAT_800d19a4;
			CBruce *pSkater2 = pSkater->mpNext;
			SVideoInfo *VInfo = &DAT_800bf318;
			if (VInfo->VideoMode == VIDEO_PLAYBACK && Activated)
			{
				VInfo->PlaybackFrozen = 0;
				DAT_800d16fc = 0;
				Video_Stop(pSkater);
				if (pSkater2)
					Video_Stop(pSkater2);
				Front_SwitchOnVideoScreen();
				break;
			}
		}
		if ((Start || !DAT_800c0a48[0].Type || (DAT_800d1780 == 2 && !DAT_800c0a48[1].Type)) && DAT_800d1cb0)
		{
			DAT_800d140c = 1;
			DAT_800d17c8->m310 = DAT_800d1770;
			if (DAT_800d17cc)
				DAT_800d17cc->m310 = DAT_800d1770;
			DAT_800d17c8->m314 = DAT_800d1770;
			if (DAT_800d17cc)
				DAT_800d17cc->m314 = DAT_800d1770;
			Mess_DeleteAll();
			Pad_ClearTriggers(&DAT_800c0a48[0]);
			Pad_ClearTriggers(&DAT_800c0a48[1]);
			DAT_800d1410 = 0;
			SFX_Pause();
			SFX_PlayX(2, 4096, 0);
			Pad_ActuatorOff(0, 0);
			Pad_ActuatorOff(0, 1);
			DAT_800d1474 = new CMenu(256, 0, 0, 335, 256, 22);
			DAT_800d1474->AddEntry(DAT_800a5d5c[96]);
			DAT_800d1474->AddEntry((DAT_800a5398[DAT_800d1e28].mNoHighScores && DAT_800d16a4 == 1) ? DAT_800a5d5c[30] : DAT_800a5d5c[29]);
			DAT_800d1474->AddEntry(DAT_800a5d5c[105]);
			if (!DAT_800d1710)
				DAT_800d1474->EntryOff(DAT_800a5d5c[105]);
			DAT_800d1474->AddEntry(DAT_800a5d5c[83]);
			if (DAT_800d16a4 == 7)
				DAT_800d1474->AddEntry(DAT_800a5d5c[1]);
			else
				DAT_800d1474->AddEntry(DAT_800a5d5c[2]);
			DAT_800d1474->CentreY();
			DAT_800d1474->mY += 13;
			if (DAT_800c0a48[0].Type && (DAT_800d1780 == 1 || DAT_800c0a48[1].Type))
			{
				DAT_800d13e8 = STATUS_PAUSEDMENU;
				if (DAT_800d151c && DAT_800d1520)
				{
					DAT_800d17e8 = 0;
					DAT_800d17ec = 0;
				}
				else if (DAT_800d16a4 != 7)
				{
					DAT_800d17e8 = DAT_800d1520;
					DAT_800d17ec = DAT_800d151c;
				}
			}
			else
			{
				DAT_800d13e8 = STATUS_PADUNPLUGGED;
			}
		}
		break;

	case STATUS_PAUSEDMENU:
		if (!DAT_800d140c)
			SwitchOffPauseMode = 1;
		if (!DAT_800c0a48[0].Type || (DAT_800d1780 == 2 && !DAT_800c0a48[1].Type))
			DAT_800d13e8 = STATUS_PADUNPLUGGED;
		if (DAT_800c0a48[0].LeftOne.Pressed)
		{
			if (Shell_DoCheatProcessing())
			{
				DAT_800d1410 = 32;
				DAT_800d1414 = 0;
			}
			Pad_ClearTriggers(&DAT_800c0a48[0]);
			Pad_ClearTriggers(&DAT_800c0a48[1]);
			break;
		}
		DAT_800d1fec = 0;
		if (DAT_800d1710)
			DAT_800d1474->EntryOn(DAT_800a5d5c[105]);
		else
			DAT_800d1474->EntryOff(DAT_800a5d5c[105]);
		DAT_800d1474->Update();
		if (Activated)
		{
			if (DAT_800d1474->ChoiceIs(DAT_800a5d5c[2]))
			{
				SoundEffect = 5;
				Game_Over();
				SwitchOffPauseMode = 1;
				DAT_800d1784 = 1;
				DAT_800d1788 = 1;
			}
			if (DAT_800d1474->ChoiceIs(DAT_800a5d5c[96]))
			{
				SoundEffect = 5;
				SwitchOffPauseMode = 1;
			}
			if (DAT_800d1474->ChoiceIs((DAT_800a5398[DAT_800d1e28].mNoHighScores && DAT_800d16a4 == 1) ? DAT_800a5d5c[30] : DAT_800a5d5c[29]))
			{
				SwitchOffPauseMode = 1;
				Horse_Reset();
				DAT_800d16e0 = 7;
				Competition_Init();
			}
			if (DAT_800d1474->ChoiceIs(DAT_800a5d5c[105]))
			{
				SoundEffect = 5;
				DAT_800d13e8 = STATUS_SKIPTORESTART;
			}
			if (DAT_800d1474->ChoiceIs(DAT_800a5d5c[98]))
			{
				SoundEffect = 5;
				DAT_800d1428->SetLine(DAT_800d1428->FindEntry(DAT_800a5d5c[110]));
				DAT_800d13e8 = STATUS_REALLYQUIT;
			}
			if (DAT_800d1474->ChoiceIs(DAT_800a5d5c[83]))
			{
				SoundEffect = 5;
				DAT_800d13e8 = STATUS_SETSOUNDLEVELS;
				FUN_8008f19c(0, 0, -1);
				FUN_8008f0ec(480);
			}
			if (DAT_800d1474->ChoiceIs(DAT_800a5d5c[1]))
			{
				SoundEffect = 5;
				DAT_800d1514 = 0;
				DAT_800d17c0 = 0;
				DAT_800d13e8 = STATUS_ENDINGSCREEN;
			}
		}
		if (GoBack)
		{
			SoundEffect = 5;
			SwitchOffPauseMode = 1;
		}
		SFX_PlayX(SoundEffect, 4096, 0);
		break;

	case STATUS_SKIPTORESTART:
		if (!DAT_800d1478)
		{
			int i;
			DAT_800d1478 = new CMenu(256, 0, 0, 335, 256, 22);
			DAT_800d1478->mLineSep = 18;
			for (i = 0; i < DAT_800d19d8; i++)
			{
				char head[4];
				head[0] = DAT_800a8788[i][0];
				head[1] = DAT_800a8788[i][1];
				head[2] = DAT_800a8788[i][2];
				head[3] = 0;
				if (!Utils_CompareStrings(head, DAT_800d14e0, -1))
					DAT_800d1478->AddEntry(DAT_800a8788[i]);
			}
			DAT_800d1478->CentreY();
		}
		DAT_800d1478->Update();
		if (Activated)
		{
			Trig_SetRestart(DAT_800d1478->mEntry[DAT_800d1478->mLine].pString);
			delete DAT_800d1478;
			SwitchOffPauseMode = 1;
			DAT_800d1478 = 0;
			DAT_800d16e0 = 7;
			SFX_PlayX(5, 8192, 0);
		}
		if (GoBack)
		{
			delete DAT_800d1478;
			DAT_800d1478 = 0;
			DAT_800d13e8 = STATUS_PAUSEDMENU;
			SFX_PlayX(2, 8192, 0);
		}
		break;

	case STATUS_REALLYQUIT:
		DAT_800d1428->Update();
		if (Activated)
		{
			if (DAT_800d1428->ChoiceIs(DAT_800a5d5c[109]))
			{
				DAT_800d16e0 = 8;
				SwitchOffPauseMode = 1;
				Horse_Reset();
				SFX_PlayX(5, 8192, 0);
			}
			else
			{
				DAT_800d13e8 = STATUS_PAUSEDMENU;
				SFX_PlayX(2, 8192, 0);
			}
		}
		if (GoBack)
		{
			SFX_PlayX(2, 8192, 0);
			DAT_800d13e8 = STATUS_PAUSEDMENU;
		}
		break;

	case STATUS_PADUNPLUGGED:
		if (DAT_800c0a48[0].Type && (DAT_800d1780 == 1 || DAT_800c0a48[1].Type))
			DAT_800d13e8 = STATUS_PAUSEDMENU;
		break;

	case STATUS_QUITSAVE:
		DAT_800d1428->Update();
		if (Activated)
		{
			if (DAT_800d1428->ChoiceIs(DAT_800a5d5c[109]))
			{
				SFX_PlayX(5, 8192, 0);
				Front_SetSaveAction(SAVE_GAME);
				Front_InitMemCardMenus(512, SVSTATUS_CHECKINGCARDPAUSE, STATUS_ENDINGSCREEN);
				DAT_800d13e8 = STATUS_MEMCARDMENUS;
			}
			else
			{
				DAT_800d13e8 = STATUS_ENDLEVELFADESCREEN;
				SFX_PlayX(2, 8192, 0);
			}
		}
		if (GoBack)
		{
			SFX_PlayX(2, 8192, 0);
			DAT_800d13e8 = STATUS_ENDINGSCREEN;
		}
		break;

	case STATUS_REALLYMAINMENU:
		DAT_800d1428->Update();
		if (Activated)
		{
			if (DAT_800d1428->ChoiceIs(DAT_800a5d5c[109]))
			{
				DAT_800d13e8 = STATUS_ENDLEVELFADESCREEN;
				SFX_PlayX(5, 8192, 0);
			}
			else
			{
				SFX_PlayX(2, 8192, 0);
				if (InCompetition() & !Competition_IsOver())
				{
					DAT_800d13e8 = STATUS_ENDHEATMENU;
					DAT_800d143c->SetLine(DAT_800d143c->FindEntry(DAT_800a5d5c[49]));
				}
				else
				{
					DAT_800d13e8 = STATUS_ENDINGSCREEN;
				}
			}
		}
		if (GoBack)
		{
			SFX_PlayX(2, 8192, 0);
			if (InCompetition() & !Competition_IsOver())
			{
				DAT_800d13e8 = STATUS_ENDHEATMENU;
				DAT_800d143c->SetLine(DAT_800d143c->FindEntry(DAT_800a5d5c[49]));
			}
			else
			{
				DAT_800d13e8 = STATUS_ENDINGSCREEN;
			}
		}
		break;

	case STATUS_ENDINGSCREEN:
		if (DAT_800d13d8)
		{
			DAT_800d13e8 = STATUS_ENDLEVELFADESCREEN;
		}
		else if (DAT_800d1514 > 10)
		{
			DAT_800d142c->Update();
			if (Activated)
			{
				SFX_PlayX(5, 8192, 0);
				Flash_Fade(16, 1);
				if (DAT_800d142c->ChoiceIs(DAT_800a5d5c[98]))
				{
					if (!DAT_800a5398[DAT_800d1e28].mNoHighScores && DAT_800d142c->IsEntryOn(DAT_800a5d5c[28]) && !DAT_800d10f8)
					{
						DAT_800d13e8 = STATUS_QUITSAVE;
						DAT_800d1428->SetLine(DAT_800d1428->FindEntry(DAT_800a5d5c[109]));
					}
					else
					{
						DAT_800d13e8 = STATUS_REALLYMAINMENU;
					}
				}
				else if (DAT_800d142c->ChoiceIs((DAT_800a5398[DAT_800d1e28].mNoHighScores && DAT_800d16a4 == 1) ? DAT_800a5d5c[30] : DAT_800a5d5c[29]))
				{
					DAT_800d16e0 = 7;
					SwitchOffPauseMode = 1;
					Competition_Init();
					Horse_Reset();
				}
				else if (DAT_800d142c->ChoiceIs(DAT_800a5d5c[33]))
				{
					DAT_800d13e8 = STATUS_VIDEOSCREEN;
				}
				else if (DAT_800d142c->ChoiceIs(DAT_800a5d5c[28]) || DAT_800d142c->ChoiceIs(DAT_800a5d5c[89]))
				{
					DAT_800d1428->SetLine(DAT_800d1428->FindEntry(DAT_800a5d5c[109]));
					DAT_800d13e8 = STATUS_SAVEGAME;
				}
				else if (DAT_800d142c->ChoiceIs(DAT_800a5d5c[31]))
				{
					DAT_800d1c9c = 1;
					DAT_800d13e8 = STATUS_ENDLEVELFADESCREEN;
				}
				else if (DAT_800d142c->ChoiceIs(DAT_800a5d5c[32]))
				{
					DAT_800d1c9c = 2;
					DAT_800d13e8 = STATUS_ENDLEVELFADESCREEN;
				}
				else if (DAT_800d142c->ChoiceIs(DAT_800a5d5c[0]))
				{
					DAT_800d1c9c = 6;
					DAT_800d13e8 = STATUS_ENDLEVELFADESCREEN;
				}
			}
		}
		else
		{
			DAT_800d1514++;
		}
		break;

	case STATUS_VIDEOSCREEN:
		if (DAT_800d1514 > 10)
		{
			Front_SetSaveAction(SAVE_VIDEO);
			DAT_800d1430->Update();
			if (Activated)
			{
				DAT_800d1de8 = 0;
				SFX_PlayX(5, 8192, 0);
				Flash_Fade(32, 1);
				if (DAT_800d1430->ChoiceIs(DAT_800a5d5c[27]))
				{
					Video_Cleanup();
					DAT_800d13e8 = STATUS_ENDINGSCREEN;
				}
				else if (DAT_800d1430->ChoiceIs(DAT_800a5d5c[23]))
				{
					DAT_800d1de8 = -1;
					DAT_800d16e0 = 7;
					SwitchOffPauseMode = 1;
					Video_SortAndMerge();
				}
				else if (DAT_800d1430->ChoiceIs(DAT_800a5d5c[24]))
				{
					DAT_800d1de8 = 1;
					DAT_800d16e0 = 7;
					SwitchOffPauseMode = 1;
					Video_SortAndMerge();
				}
				else if (DAT_800d1430->ChoiceIs(DAT_800a5d5c[25]))
				{
					Front_InitMemCardMenus(512, SVSTATUS_CHECKINGCARDPAUSE, STATUS_VIDEOSCREEN);
					DAT_800d13e8 = STATUS_MEMCARDMENUS;
				}
			}
			if (GoBack)
			{
				SFX_PlayX(2, 8192, 0);
				DAT_800d13e8 = STATUS_ENDINGSCREEN;
			}
		}
		else
		{
			DAT_800d1514++;
		}
		break;

	case STATUS_VIDEOSCREEN2:
		if (!DAT_800d1cb0)
		{
			Video_Cleanup();
			DAT_800d13e8 = STATUS_ENDLEVELFADESCREEN;
		}
		if (DAT_800d1514 > 10)
		{
			Front_SetSaveAction(SAVE_VIDEO);
			DAT_800d1434->Update();
			if (Activated)
			{
				DAT_800d1de8 = 0;
				SFX_PlayX(5, 8192, 0);
				Flash_Fade(32, 1);
				if (DAT_800d1434->ChoiceIs(DAT_800a5d5c[27]))
				{
					Video_Cleanup();
					DAT_800d13e8 = STATUS_ENDLEVELFADESCREEN;
				}
				else if (DAT_800d1434->ChoiceIs(DAT_800a5d5c[23]))
				{
					DAT_800d1de8 = -1;
					DAT_800d16e0 = 7;
					SwitchOffPauseMode = 1;
					Video_SortAndMerge();
				}
				else if (DAT_800d1434->ChoiceIs(DAT_800a5d5c[24]))
				{
					DAT_800d1de8 = 1;
					DAT_800d16e0 = 7;
					SwitchOffPauseMode = 1;
					Video_SortAndMerge();
				}
			}
			if (GoBack)
			{
				SFX_PlayX(2, 8192, 0);
				Video_Cleanup();
				DAT_800d13e8 = STATUS_ENDLEVELFADESCREEN;
			}
		}
		else
		{
			DAT_800d1514++;
		}
		break;

	case STATUS_ENDHEATVIDEOMENU:
		if (DAT_800d1514 > 10)
		{
			Front_SetSaveAction(SAVE_VIDEO);
			DAT_800d1438->Update();
			if (Activated)
			{
				DAT_800d1de8 = 0;
				SFX_PlayX(5, 8192, 0);
				Flash_Fade(32, 1);
				if (DAT_800d1438->ChoiceIs(DAT_800a5d5c[73]))
				{
					Video_Cleanup();
					DAT_800d13e8 = STATUS_ENDHEATMENU;
					DAT_800d143c->SetLine(DAT_800d143c->FindEntry(DAT_800a5d5c[49]));
				}
				else if (DAT_800d1438->ChoiceIs(DAT_800a5d5c[23]))
				{
					DAT_800d1de8 = -1;
					DAT_800d16e0 = 7;
					SwitchOffPauseMode = 1;
					Video_SortAndMerge();
				}
				else if (DAT_800d1438->ChoiceIs(DAT_800a5d5c[24]))
				{
					DAT_800d1de8 = 1;
					DAT_800d16e0 = 7;
					SwitchOffPauseMode = 1;
					Video_SortAndMerge();
				}
				else if (DAT_800d1438->ChoiceIs(DAT_800a5d5c[25]))
				{
					Front_InitMemCardMenus(512, SVSTATUS_CHECKINGCARDPAUSE, STATUS_ENDHEATVIDEOMENU);
					DAT_800d13e8 = STATUS_MEMCARDMENUS;
				}
			}
			if (GoBack)
			{
				SFX_PlayX(2, 8192, 0);
				DAT_800d13e8 = STATUS_ENDHEATMENU;
				DAT_800d143c->SetLine(DAT_800d143c->FindEntry(DAT_800a5d5c[49]));
			}
		}
		else
		{
			DAT_800d1514++;
		}
		break;

	case STATUS_GOTTAPE:
		if (DAT_800d1514 > 10)
		{
			if (Activated && CTape::DisplayContinueButton())
			{
				SFX_PlayX(5, 8192, 0);
				{
					int i;
					for (i = 0; i < 5; i++)
					{
						delete DAT_800a5b14[i];
						DAT_800a5b14[i] = 0;
					}
				}
				DAT_800d13e8 = STATUS_TAPESAVE;
				DAT_800d1428->SetLine(DAT_800d1428->FindEntry(DAT_800a5d5c[109]));
			}
		}
		else
		{
			DAT_800d1514++;
		}
		break;

	case STATUS_CHANGEHORSEWORD:
		{
			int UpDown;
			char lastAlpha;
			char firstAlpha;
			DAT_800d17c0 = 0;
			UpDown = GetUpDown();
			lastAlpha = 'Z';
			firstAlpha = 'A';
			if (DAT_800d17b8 >= DAT_800a6844.HorseLen - 1 && DAT_800a6844.HorseLen >= 4)
			{
				lastAlpha = ' ';
				firstAlpha = ' ';
			}
			if (UpDown == -1)
			{
				DAT_800d1100 = 16;
				SFX_PlayX(17, 8192, 0);
				if (DAT_800a6844.HorseWord[DAT_800d17b8] == ' ' || DAT_800a6844.HorseWord[DAT_800d17b8] == 0)
				{
					DAT_800a6844.HorseWord[DAT_800d17b8] = 'A';
				}
				else
				{
					DAT_800a6844.HorseWord[DAT_800d17b8]++;
					if ((uchar)DAT_800a6844.HorseWord[DAT_800d17b8] > 'Z')
						DAT_800a6844.HorseWord[DAT_800d17b8] = firstAlpha;
				}
			}
			if (UpDown == 1)
			{
				DAT_800d1100 = 16;
				SFX_PlayX(17, 8192, 0);
				if (DAT_800a6844.HorseWord[DAT_800d17b8] == ' ' || DAT_800a6844.HorseWord[DAT_800d17b8] == 0)
				{
					DAT_800a6844.HorseWord[DAT_800d17b8] = 'Z';
				}
				else
				{
					DAT_800a6844.HorseWord[DAT_800d17b8]--;
					if ((uchar)DAT_800a6844.HorseWord[DAT_800d17b8] < 'A')
						DAT_800a6844.HorseWord[DAT_800d17b8] = lastAlpha;
				}
			}
			DAT_800a6844.HorseLen = 10;
			{
				int i;
				for (i = 0; i < 10; i++)
				{
					if (DAT_800a6844.HorseWord[i] == ' ' || DAT_800a6844.HorseWord[i] == 0)
					{
						DAT_800a6844.HorseLen = i;
						break;
					}
				}
			}
			if (DAT_800c0a48[0].Left.Triggered || DAT_800c0a48[1].Left.Triggered)
			{
				DAT_800d1100 = 16;
				SFX_PlayX(5, 8192, 0);
				DAT_800c0a48[0].Left.Triggered = 0;
				DAT_800c0a48[1].Left.Triggered = 0;
				DAT_800d17b8--;
				if (DAT_800d17b8 < 0)
					DAT_800d17b8 = DAT_800a6844.HorseLen;
				if (DAT_800d17b8 >= 10)
					DAT_800d17b8 = 9;
			}
			if (DAT_800c0a48[0].Right.Triggered || DAT_800c0a48[1].Right.Triggered)
			{
				DAT_800d1100 = 16;
				SFX_PlayX(5, 8192, 0);
				DAT_800c0a48[0].Right.Triggered = 0;
				DAT_800c0a48[1].Right.Triggered = 0;
				DAT_800d17b8++;
				if (DAT_800d17b8 > DAT_800a6844.HorseLen)
					DAT_800d17b8 = 0;
				if (DAT_800d17b8 >= 10)
					DAT_800d17b8 = 0;
			}
			if (Activated)
			{
				{
					int i;
					for (i = 0; i < 10; i++)
					{
						if (DAT_800a6844.HorseWord[i] == ' ')
						{
							DAT_800a6844.HorseWord[i] = 0;
							break;
						}
					}
				}
				FUN_8008b900(DAT_800a4118.HorseWord, DAT_800a6844.HorseWord);
				DAT_800d16cc = 1;
				DAT_800d17a8 = 0;
				DAT_800a4118.HorseLen = DAT_800a6844.HorseLen;
				SFX_PlayX(5, 8192, 0);
			}
		}
		break;

	case STATUS_STARTHORSE:
		DAT_800d17c0 = 1;
		DAT_800d17c8->m310 = DAT_800d1770;
		if (Activated)
			SwitchOffPauseMode = 1;
		break;

	case STATUS_TAPESAVE:
		DAT_800d1428->Update();
		if (Activated)
		{
			SFX_PlayX(5, 8192, 0);
			Flash_Fade(32, 1);
			if (DAT_800d1428->ChoiceIs(DAT_800a5d5c[109]))
			{
				Front_SetSaveAction(SAVE_GAME);
				Front_InitMemCardMenus(512, SVSTATUS_CHECKINGCARDPAUSE, STATUS_STATS);
				DAT_800d13e8 = STATUS_MEMCARDMENUS;
			}
			else
			{
				DAT_800d13e8 = STATUS_STATS;
			}
		}
		if (GoBack)
		{
			SFX_PlayX(2, 8192, 0);
			DAT_800d13e8 = STATUS_GOTTAPE;
		}
		break;

	case STATUS_HIGHSCORE:
		if (DAT_800d1514 > 10)
		{
			if (DAT_800d13dc != -1)
			{
				int UpDown = GetUpDown();
				if (UpDown == -1)
				{
					DAT_800d1100 = 16;
					SFX_PlayX(17, 8192, 0);
					if (DAT_800a6844.HighScores[DAT_800d1e28][DAT_800d13dc].Name[DAT_800d13e0] == ' ' ||
						DAT_800a6844.HighScores[DAT_800d1e28][DAT_800d13dc].Name[DAT_800d13e0] == 0)
					{
						DAT_800a6844.HighScores[DAT_800d1e28][DAT_800d13dc].Name[DAT_800d13e0] = 'A';
					}
					else
					{
						DAT_800a6844.HighScores[DAT_800d1e28][DAT_800d13dc].Name[DAT_800d13e0]++;
						if ((uchar)DAT_800a6844.HighScores[DAT_800d1e28][DAT_800d13dc].Name[DAT_800d13e0] > 'Z')
							DAT_800a6844.HighScores[DAT_800d1e28][DAT_800d13dc].Name[DAT_800d13e0] = ' ';
					}
				}
				if (UpDown == 1)
				{
					DAT_800d1100 = 16;
					SFX_PlayX(17, 8192, 0);
					if (DAT_800a6844.HighScores[DAT_800d1e28][DAT_800d13dc].Name[DAT_800d13e0] == ' ' ||
						DAT_800a6844.HighScores[DAT_800d1e28][DAT_800d13dc].Name[DAT_800d13e0] == 0)
					{
						DAT_800a6844.HighScores[DAT_800d1e28][DAT_800d13dc].Name[DAT_800d13e0] = 'Z';
					}
					else
					{
						DAT_800a6844.HighScores[DAT_800d1e28][DAT_800d13dc].Name[DAT_800d13e0]--;
						if ((uchar)DAT_800a6844.HighScores[DAT_800d1e28][DAT_800d13dc].Name[DAT_800d13e0] < 'A')
							DAT_800a6844.HighScores[DAT_800d1e28][DAT_800d13dc].Name[DAT_800d13e0] = ' ';
					}
				}
				if (DAT_800c0a48[0].Left.Triggered || DAT_800c0a48[1].Left.Triggered)
				{
					DAT_800d1100 = 16;
					SFX_PlayX(5, 8192, 0);
					DAT_800c0a48[0].Left.Triggered = 0;
					DAT_800c0a48[1].Left.Triggered = 0;
					DAT_800d13e0--;
					if (DAT_800d13e0 < 0)
						DAT_800d13e0 = 2;
				}
				if (DAT_800c0a48[0].Right.Triggered || DAT_800c0a48[1].Right.Triggered)
				{
					DAT_800d1100 = 16;
					SFX_PlayX(5, 8192, 0);
					DAT_800c0a48[0].Right.Triggered = 0;
					DAT_800c0a48[1].Right.Triggered = 0;
					DAT_800d13e0++;
					if (DAT_800d13e0 >= 3)
						DAT_800d13e0 = 0;
				}
			}
			if (Activated)
			{
				SFX_PlayX(18, 8192, 0);
				FUN_8008b900(DAT_800a6844.PlayerName, DAT_800a6844.HighScores[DAT_800d1e28][DAT_800d13dc].Name);
				DAT_800d13dc = -1;
				DAT_800d13e8 = STATUS_ENDINGSCREEN;
			}
		}
		break;

	case STATUS_STATS:
		if (DAT_800d1514 > 10)
		{
			if (DAT_800d16a4 == 7)
			{
				DAT_800d17c0 = 0;
				if (--DAT_800d17bc <= 0 && DAT_800d14fc != 2)
					Activated = 1;
				if (DAT_800d14fc == 2 && DAT_800d13c4 && !DAT_800a5b28[0].handleComplete())
				{
					DAT_800d1514 = 0;
					DAT_800d13e8 = STATUS_ENDINGSCREEN;
				}
			}
			if (Activated)
			{
				SFX_PlayX(5, 8192, 0);
				DAT_800d14f4 = 0;
				if (DAT_800d16a4 == 7)
				{
					if (DAT_800d14fc == 2)
					{
						DAT_800d13c4 = 1;
						DAT_800d17ac = 0;
						Trig_SetRestart(DAT_800a87d8[0]);
					}
					else
					{
						DAT_800d17ac = DAT_800d1508;
						DAT_800d17a4 = DAT_800d1504;
						DAT_800d17a0 = DAT_800d14fc;
						DAT_800d179c = DAT_800d1500;
						DAT_800d17b0 = DAT_800d150c;
						DAT_800d17b4 = DAT_800d1510;
						SwitchOffPauseMode = 1;
						Trig_SetRestart(DAT_800a87d8[DAT_800d17ac]);
						DAT_800d16e0 = 7;
					}
				}
				else if (DAT_800d13dc != -1)
				{
					DAT_800d13e8 = STATUS_HIGHSCORE;
					InitStatsSwisch();
				}
				else
				{
					DAT_800d13e8 = STATUS_ENDINGSCREEN;
				}
			}
		}
		else
		{
			DAT_800d1514++;
		}
		break;

	case STATUS_ENDHEATMENU:
		if (DAT_800d1514 > 10)
		{
			DAT_800d143c->Update();
			if (Activated)
			{
				SFX_PlayX(5, 8192, 0);
				Flash_Fade(32, 1);
				if (DAT_800d143c->ChoiceIs(DAT_800a5d5c[98]))
				{
					DAT_800d13e8 = STATUS_REALLYMAINMENU;
				}
				else if (DAT_800d143c->ChoiceIs(DAT_800a5d5c[49]))
				{
					SwitchOffPauseMode = 1;
					DAT_800d16e0 = 7;
				}
				else if (DAT_800d143c->ChoiceIs(DAT_800a5d5c[50]))
				{
					DAT_800d13e8 = STATUS_ENDHEATWINLOSE;
				}
				else if (DAT_800d143c->ChoiceIs(DAT_800a5d5c[33]))
				{
					DAT_800d13e8 = STATUS_ENDHEATVIDEOMENU;
				}
			}
		}
		else
		{
			DAT_800d1514++;
		}
		break;

	case STATUS_ENDGAME:
		Competition_EndGameLogic(DAT_800d13e8, Activated);
		break;

	case STATUS_ENDHEATWINLOSE:
		Competition_WinLoseLogic(DAT_800d13e8, Activated);
		break;

	case STATUS_MEDALSAVE:
		DAT_800d1428->Update();
		if (Activated)
		{
			SFX_PlayX(5, 8192, 0);
			Flash_Fade(32, 1);
			if (DAT_800d1428->ChoiceIs(DAT_800a5d5c[109]))
			{
				Front_SetSaveAction(SAVE_GAME);
				Front_InitMemCardMenus(512, SVSTATUS_CHECKINGCARDPAUSE, STATUS_ENDINGSCREEN);
				DAT_800d13e8 = STATUS_MEMCARDMENUS;
			}
			else
			{
				DAT_800d13e8 = STATUS_ENDINGSCREEN;
			}
		}
		break;

	case STATUS_ENDHEATLADDER:
		Competition_LadderLogic();
		if (Activated)
		{
			if (Competition_LadderFullyDisplayed())
			{
				Video_Stop(DAT_800d19a4);
				DAT_800d140c = 1;
				if (Competition_NewHeat())
				{
					DAT_800d13e8 = STATUS_ENDHEATMENU;
					DAT_800d143c->SetLine(DAT_800d143c->FindEntry(DAT_800a5d5c[49]));
				}
				else
				{
					DAT_800d13e8 = STATUS_ENDHEATWINLOSE;
				}
			}
			else
			{
				FUN_80076494();
				SFX_PlayX(52, 8192, 0);
			}
		}
		break;

	case STATUS_ENDHEATREPLAY:
		Competition_JudgeLogic();
		if (DAT_800d1514 > 10)
		{
			if (Activated)
			{
				if (Competition_JudgeFullyDisplayed())
				{
					SFX_PlayX(5, 8192, 0);
					DAT_800d13e8 = STATUS_ENDHEATLADDER;
					DAT_800d1de8 = -1;
					RestartCompFrig();
					delete DAT_800d1474;
					DAT_800d1474 = 0;
					if (DAT_800d16e0 != 8 && DAT_800d16e0 != 4 && DAT_800d16e0 != 3)
						SFX_Unpause();
					Video_SortAndMerge();
					if (DAT_800bf318.NumFrames > 90)
					{
						CBruce *pSkater = DAT_800d19a4;
						CBruce *pSkater2 = pSkater->mpNext;
						DAT_800d140c = 0;
						DAT_800d1de8 = 0;
						DAT_800bf318.ReplayHighlight = 0;
						DAT_800bf3d8.ReplayHighlight = 0;
						Video_Start(pSkater, VIDEO_PLAYBACK, 1, 0x7fffffff);
						if (pSkater2)
							Video_Start(pSkater2, VIDEO_PLAYBACK, 1, 0x7fffffff);
						DAT_800d1784 = 0;
						Flash_Reset();
						DAT_800d19a4->m330 = DAT_800d1a24 + 216030;
						if (DAT_800d19a4->mpNext)
							DAT_800d19a4->mpNext->m330 = DAT_800d1a24 + 216030;
					}
				}
				else
				{
					FUN_80076484();
					SFX_PlayX(52, 8192, 0);
				}
			}
		}
		else
		{
			DAT_800d1514++;
		}
		break;

	case STATUS_ENDHEAT:
		DAT_800d13e8 = STATUS_ENDHEATREPLAY;
		DAT_800d1514++;
		break;

	case STATUS_SAVEGAME:
		DAT_800d1428->Update();
		if (Activated)
		{
			SFX_PlayX(5, 8192, 0);
			Flash_Fade(32, 1);
			if (DAT_800d1428->ChoiceIs(DAT_800a5d5c[109]))
			{
				Front_SetSaveAction(SAVE_GAME);
				Front_InitMemCardMenus(512, SVSTATUS_CHECKINGCARDPAUSE, STATUS_ENDINGSCREEN);
				DAT_800d13e8 = STATUS_MEMCARDMENUS;
			}
			else
			{
				DAT_800d13e8 = STATUS_ENDINGSCREEN;
			}
		}
		if (GoBack)
		{
			SFX_PlayX(2, 8192, 0);
			DAT_800d13e8 = STATUS_ENDINGSCREEN;
		}
		break;

	case STATUS_ENDLEVELFADESCREEN:
		Flash_Update();
		if (Flash_FadeFinished())
		{
			DAT_800d16e0 = 8;
			SwitchOffPauseMode = 1;
			Horse_Reset();
		}
		break;

	case STATUS_DOSAVEFADESCREEN:
	case STATUS_NOSAVEFADESCREEN:
		Flash_Update();
		if (Flash_FadeFinished())
		{
			if (DAT_800d13e8 == STATUS_DOSAVEFADESCREEN)
				DAT_800d16e0 = 4;
			else
				DAT_800d16e0 = 3;
			SwitchOffPauseMode = 1;
		}
		break;

	case STATUS_SETSOUNDLEVELS:
		DAT_800d1440->Update();
		DAT_800d13d0 = (DAT_800d1440->ChoiceIs(DAT_800a5d44) || DAT_800d1440->ChoiceIs(DAT_800a5d5c[86])) ? DAT_800a4118.MusicVol * 0x555 : 0;
		if (DAT_800c0a48[0].Left.Triggered || DAT_800c0a48[1].Left.Triggered)
		{
			DAT_800c0a48[0].Left.Triggered = 0;
			DAT_800c0a48[1].Left.Triggered = 0;
			if (DAT_800d1440->ChoiceIs(DAT_800a5d2c))
			{
				int v;
				if (DAT_800d21fc > 0)
					DAT_800d21fc--;
				v = DAT_800d21fc * 6 / 5;
				DAT_800a6844.SfxVol = v;
				DAT_800a4118.SfxVol = v;
				FUN_8008b900(DAT_800a5d2c, DAT_800a5d5c[84], DAT_800d21fc);
				DAT_800d13cc = DAT_800a6844.SfxVol * 0x555;
				SFX_PlayX(5, 8192, 0);
			}
			else if (DAT_800d1440->ChoiceIs(DAT_800a5d44))
			{
				if (DAT_800d2200 > 0)
					DAT_800d2200--;
				DAT_800a4118.MusicVol = DAT_800a6844.MusicVol = DAT_800d2200 * 6 / 5;
				FUN_8008b900(DAT_800a5d44, DAT_800a5d5c[85], DAT_800d2200);
			}
		}
		if (DAT_800c0a48[0].Right.Triggered || DAT_800c0a48[1].Right.Triggered)
		{
			DAT_800c0a48[0].Right.Triggered = 0;
			DAT_800c0a48[1].Right.Triggered = 0;
			if (DAT_800d1440->ChoiceIs(DAT_800a5d2c))
			{
				int v;
				if (DAT_800d21fc < 10)
					DAT_800d21fc++;
				v = DAT_800d21fc * 6 / 5;
				DAT_800a6844.SfxVol = v;
				DAT_800a4118.SfxVol = v;
				FUN_8008b900(DAT_800a5d2c, DAT_800a5d5c[84], DAT_800d21fc);
				DAT_800d13cc = DAT_800a6844.SfxVol * 0x555;
				SFX_PlayX(5, 8192, 0);
			}
			else if (DAT_800d1440->ChoiceIs(DAT_800a5d44))
			{
				if (DAT_800d2200 < 10)
					DAT_800d2200++;
				DAT_800a4118.MusicVol = DAT_800a6844.MusicVol = DAT_800d2200 * 6 / 5;
				FUN_8008b900(DAT_800a5d44, DAT_800a5d5c[85], DAT_800d2200);
			}
		}
		if (Activated)
		{
			if (DAT_800d1440->ChoiceIs(DAT_800a5d5c[86]))
				FUN_80023528();
			else if (DAT_800d1440->ChoiceIs(DAT_800a5d5c[87]))
				GoBack = 1;
		}
		if (GoBack)
		{
			SFX_PlayX(2, 8192, 0);
			DAT_800d13e8 = STATUS_PAUSEDMENU;
			DAT_800d13d0 = DAT_800a6844.MusicVol * 0x555;
			FUN_8008f19c(1, 0, -1);
			FUN_8008f4d4(9, 0, 0);
		}
		break;
	}

	if (SwitchOffPauseMode)
	{
		DAT_800d140c = 0;
		DAT_800d17e8 = 0;
		DAT_800d17ec = 0;
		DAT_800d13e8 = STATUS_NORMAL;
		delete DAT_800d1474;
		DAT_800d1474 = 0;
		if (DAT_800d16e0 != 8 && DAT_800d16e0 != 4 && DAT_800d16e0 != 3)
			SFX_Unpause();
	}
}
