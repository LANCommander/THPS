/* PlayAway__Fv (0x80025e00) flags=-fstructure-noalias */
/* C++ (MAIN.CPP). PlayAway (called from LaunchGame). The demo splits this into Game_Init (the
   fuzzy twin of the first 490 words), System_Logic and a 216-byte PlayAway loop. THPS1 writes the
   init out in place: its error exits `goto done` straight to the shutdown, which keeps the first
   EndCode test in the init's last block. System_Logic is an inline. Sets up the level (video restart/replay loading, the
   powerup visibility, settling the cameras), runs the frame loop until EndCode is set, then shuts
   the game down and unloads the fonts. */
typedef unsigned char uchar;
typedef unsigned long ulong;

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
	int rest[11];
};

struct SHighlight {
	short FromFrame;
	short ToFrame;
	int Score;
};

struct SVideoHead {
	ulong NumFrames;
	SHighlight Highlights[5];
	short NumSkaters;
	short Skater;
	short Skater2;
	short Level;
	short GGame;
	short Checksum;
	char VideoFlags;
	char Padding[7];
};

struct SVideoInfo {
	int VideoMode;
	ulong *pBlockStart;
	ulong *pStreamStart;
	ulong *pStreamEnd;
	ulong *pStream;
	ulong Bits;
	int BitsLeft;
	ulong NumFrames;
	int pad20[11];
	int ReplayHighlight;
	SHighlight Highlights[5];
	int pad78[18];
};

struct SVideoRestart {
	int NumSkaters;
	int Skater;
	int Skater2;
	int Level;
	int GGame;
};

struct SLevel {
	int pad0[3];
	int isCompetition;
	int pad10[20];
	int m60;
	int pad64[5];
};

struct CBody {
	char pad0[0x1c];
	CBody *pNext;
	char pad20[0x330 - 0x20];
	int m330;
};

struct CPowerUp {
	char pad0[0x15c];
	short Visible;
};

struct CVector {
	int vx, vy, vz;
	void Set(int x, int y, int z) {
		vx = x;
		vy = y;
		vz = z;
	}
};

struct CSkater {
	char pad0[0x6c];
	CVector mVel;
	char pad78[0x6c4 - 0x78];
	int m6c4;
	int m6c8;
	int m6cc;
	char pad6d0[0x734 - 0x6d0];
	int Dead;
	char pad738[0x7d8 - 0x738];
	CVector m7d8;
	char pad7e4[0xa64 - 0x7e4];
	int ma64;
};

extern "C" {
	extern volatile unsigned DAT_800d1a24; /* Xblanks */
	extern volatile unsigned DAT_800d1a20; /* Vblanks */
	extern int DAT_800d1cb0;               /* DemoTimer */
	extern int DAT_800d1a34;               /* VblankUpdateBar */
	extern int DAT_800d1de8;               /* GVideoReplay */
	extern CBody *DAT_800d19a4;            /* MechList */
	extern int DAT_800d1e28;               /* GLevel */
	extern CBody *DAT_800d2044;            /* CameraList */
	extern unsigned DAT_800d1a1c;          /* GameFade */
	extern int DAT_800d140c;
	extern int DAT_800d215c;
	extern short DAT_800d214c;         /* M3d_OTPushback */
	extern SVideoRestart DAT_800a42f4; /* GVideoRestart */
	extern SVideoInfo DAT_800bf318;    /* GVInfo1 */
	extern SVideoInfo DAT_800bf3d8;    /* GVInfo2 */
	extern uchar DAT_800bf0c4[];       /* DemoName */
	extern SLevel DAT_800a5398[];      /* Levels */
	extern SControl DAT_800c0a48[2];   /* Pad */
	extern char DAT_8009f584[];        /* "ingame1.fnt" */
	extern char DAT_8009f590[];        /* "memory card error" */
	extern char DAT_8009f5a4[];        /* "press x to continue" */

	int DAT_800d16e0;       /* EndCode */
	int DAT_800d16a4;       /* GGame */
	int DAT_800d1780;       /* GNumberOfPlayers */
	char DAT_800d17c4;      /* GVideoFlags */
	CPowerUp *DAT_800d17d0; /* GPowS */
	CPowerUp *DAT_800d17d4; /* GPowK */
	CPowerUp *DAT_800d17d8; /* GPowA */
	CPowerUp *DAT_800d17dc; /* GPowT */
	CPowerUp *DAT_800d17e0; /* GPowE */
	CPowerUp *DAT_800d17e4; /* GPowTape */
	int DAT_800d1784;       /* GState */
	int DAT_800d1788;
	int DAT_800d178c;
	CSkater *DAT_800d17c8; /* GSkater[0] */
	CSkater *DAT_800d17cc; /* GSkater[1] */
	int DAT_800d179c;      /* GHorsePlayer */
	int DAT_800d17e8;      /* GClear1 */
	int DAT_800d17ec;      /* GClear2 */
	int DAT_800d17c0;
	int DAT_800d1728;
	int DAT_800d16fc;
	int DAT_800d1718;
	int DAT_800d16cc;
	int DAT_800d17a8;
	int DAT_800d1790;
	int DAT_800d1794;
	int DAT_800d1798;

	void FUN_8002566c(void); /* PlayAway_Init */
	void Pause__Fi(int);
	void FUN_80025400(void); /* FPS_Init */
	void FUN_800109b0(void); /* Crowd_Init */
	void FUN_800109b8(void); /* Crowd_Start */
	void FUN_800241d4(void); /* ResetMainDemoTimer */
	void FUN_80011628(int);  /* Front_SetLoadAction */
	int Card_Load__F9EFileTypePUlT1(int, ulong *, ulong *);
	void Mess_SetCurrentFont__FPc(char *);
	void FUN_8006b240(void);                              /* HiRes_ClearOTag */
	void FUN_80061ea0(void);                              /* ResetOT */
	void SetClippingBox__Fiiii(int, int, int, int);                /* SetClippingBox */
	void DrawColoredBox__FiiiiUcUcUc(int, int, int, int, int, int, int); /* DrawColoredBox */
	void Mess_SetTextJustify__FUc(int);                               /* Mess_SetTextJustify */
	void Mess_SetScale__Fi(int);
	void Mess_SetRGB__FUcUcUci(int, int, int, int);
	void Mess_DrawText__FiiPCciUiib(int, int, char *, int, int, int, int); /* Mess_DrawText */
	void FUN_8006b26c(void);                                 /* HiRes_DrawOTag */
	void Pad_ClearTriggers__FP8SControl(SControl *);
	int FUN_80070ff4(void); /* Pad_Update */
	int Card_LoadReplayFromCD__FPUlT0Pc(ulong *, ulong *, uchar *);
	int Career_Got__Fi(int);                     /* Career_Got */
	void Video_Start__FP6CBruce10EVideoModeii(CBody *, int, int, int); /* Video_Start */
	void Video_SyncObsIfNeeded__Fv(void);
	void Flash_Reset__Fv(void);   /* Flash_Reset */
	void Video_Cleanup__Fv(void);   /* Video_Cleanup */
	int FUN_8007cd64(CBody *); /* InCompetitionIntro */
	void FUN_800920b4(int);
	void Ob_AI__FPP5CBody(CBody **); /* Ob_AI */
	void FUN_800242cc(void);
	void SFX_Stop__FUi(int);
	void FUN_8001a1c8(void);
	void Front_SwitchOnEndLevelMenu__Fv(void);
	void FUN_80010bb8(void);
	void FUN_80024258(void);
	void Pad_Remap__Fv(void); /* Pad_Restore */
	void Pad_Restore__Fv(void); /* Pad_Remap */
	void Pad_ClearAllOne__Fi(int);
	void Video_HandleStepping__Fv(void);
	void Game_Logic__Fv(void); /* Game_Logic */
	void FUN_80048fec(void); /* Db_WaitRender */
	void FUN_80025440(void);
	void FUN_80024fa4(void); /* Game_Display */
	void Panel_DrawFlatShadedPoly__FiiiiUcUcUci(int, int, int, int, int, int, int, int);
	void Front_PrintDemo__Fv(void);
	void FUN_8002357c(int);
	void Db_Render__Fv(void);
	void FUN_8001a5e0(void);
	void Front_SwitchOnStartLevelMenu__Fv(void);
	int FUN_80043ce8(CBody *);
	void Spool_Sync__Fv(void);
	void Front_SaveGameState__Fv(void);
	void FUN_8008c468(int);
	void FUN_800491e8(void); /* Db_Init */
	void FUN_80010ac0(void); /* Crowd_Stop */
	void FUN_8001f138(int);
	void Mess_UnloadFont__Fv(void);
}

static inline void System_Logic(void) {
	SControl TempPad;

	if (DAT_800d16a4 == 7 && DAT_800d179c == 1) {
		TempPad = DAT_800c0a48[0];
		DAT_800c0a48[0] = DAT_800c0a48[1];
		DAT_800c0a48[1] = TempPad;
	}

	Pad_Remap__Fv();
	FUN_80070ff4();
	Pad_Restore__Fv();

	if (DAT_800d16a4 == 7 && DAT_800d179c == 1) {
		TempPad = DAT_800c0a48[0];
		DAT_800c0a48[0] = DAT_800c0a48[1];
		DAT_800c0a48[1] = TempPad;
	}

	if (DAT_800d17e8)
		Pad_ClearAllOne__Fi(0);

	if (DAT_800d17ec)
		Pad_ClearAllOne__Fi(1);
}

void PlayAway(void) {
	int XStart;

	FUN_8002566c();

	XStart = DAT_800d1a24;
	Pause__Fi(1);
	FUN_80025400();
	FUN_800109b0();
	FUN_800109b8();

	DAT_800d16e0 = 0;
	FUN_800241d4();

	if (DAT_800a42f4.NumSkaters > 0 && DAT_800d1cb0) {
		int LoadError;

		FUN_80011628(0);

		DAT_800d1a34 = 1;

		if (DAT_800a42f4.NumSkaters == 1)
			LoadError = Card_Load__F9EFileTypePUlT1(1, DAT_800bf318.pBlockStart, 0);
		else
			LoadError =
			    Card_Load__F9EFileTypePUlT1(1, DAT_800bf318.pBlockStart, DAT_800bf3d8.pBlockStart);

		DAT_800d1a34 = 0;

		if (LoadError) {
			Mess_SetCurrentFont__FPc(DAT_8009f584);
			FUN_8006b240();
			FUN_80061ea0();
			SetClippingBox__Fiiii(0, 0, 512, 240);
			DrawColoredBox__FiiiiUcUcUc(0, 0, 512, 240, 0, 0, 0);
			Mess_SetTextJustify__FUc(0);
			Mess_SetScale__Fi(255);
			Mess_SetRGB__FUcUcUci(150, 100, 25, 0);
			Mess_DrawText__FiiPCciUiib(256, 110, DAT_8009f590, 1, 0, 256, 0);
			Mess_DrawText__FiiPCciUiib(256, 130, DAT_8009f5a4, 1, 0, 256, 0);
			FUN_8006b26c();
			Pad_ClearTriggers__FP8SControl(&DAT_800c0a48[0]);
			Pad_ClearTriggers__FP8SControl(&DAT_800c0a48[1]);

			while (!DAT_800c0a48[0].X.Triggered && !DAT_800c0a48[1].X.Triggered &&
			       !DAT_800c0a48[0].Start.Triggered && !DAT_800c0a48[1].Start.Triggered)
				FUN_80070ff4();

			DAT_800d16e0 = 9;
			goto done;
		}

		{
			SVideoHead *VH = (SVideoHead *)(DAT_800bf318.pBlockStart + 128);

			DAT_800bf318.NumFrames = VH->NumFrames;

			for (int i = 0; i < 5; i++)
				DAT_800bf318.Highlights[i] = VH->Highlights[i];
		}

		if (DAT_800a42f4.NumSkaters == 2) {
			SVideoHead *VH = (SVideoHead *)(DAT_800bf3d8.pBlockStart + 128);

			DAT_800bf3d8.NumFrames = VH->NumFrames;

			for (int i = 0; i < 5; i++)
				DAT_800bf3d8.Highlights[i] = VH->Highlights[i];
		}

		DAT_800a42f4.NumSkaters = -DAT_800a42f4.NumSkaters;
		DAT_800d1de8 = -1;
	}

	if (!DAT_800d1cb0) {
		int LoadError;

		DAT_800d1a34 = 1;
		LoadError = Card_LoadReplayFromCD__FPUlT0Pc(DAT_800bf318.pBlockStart,
		                                            DAT_800bf3d8.pBlockStart, DAT_800bf0c4);
		DAT_800bf0c4[4]++;

		if (DAT_800bf0c4[4] > 'J')
			DAT_800bf0c4[4] = 'A';

		DAT_800d1a34 = 0;

		if (LoadError) {
			DAT_800d16e0 = 9;
			goto done;
		}

		{
			SVideoHead *VH = (SVideoHead *)(DAT_800bf318.pBlockStart + 128);

			DAT_800a42f4.NumSkaters = VH->NumSkaters;
			DAT_800a42f4.Skater = VH->Skater;
			DAT_800a42f4.Skater2 = VH->Skater2;
			DAT_800a42f4.Level = VH->Level;
			DAT_800a42f4.GGame = VH->GGame;
			DAT_800bf318.NumFrames = VH->NumFrames;

			for (int i = 0; i < 5; i++)
				DAT_800bf318.Highlights[i] = VH->Highlights[i];
		}

		if (DAT_800a42f4.NumSkaters == 2) {
			SVideoHead *VH = (SVideoHead *)(DAT_800bf3d8.pBlockStart + 128);

			DAT_800bf3d8.NumFrames = VH->NumFrames;

			for (int i = 0; i < 5; i++)
				DAT_800bf3d8.Highlights[i] = VH->Highlights[i];
		}

		DAT_800a42f4.NumSkaters = -DAT_800a42f4.NumSkaters;
		DAT_800d1de8 = -1;
	}

	if (!DAT_800d1de8) {
		if (DAT_800d16a4 == 1) {
			DAT_800d17c4 = 0;

			if (Career_Got__Fi(3))
				DAT_800d17c4 |= 1;

			if (Career_Got__Fi(2))
				DAT_800d17c4 |= 2;
		} else {
			DAT_800d17c4 = 3;
		}
	} else {
		DAT_800d17c4 = ((SVideoHead *)(DAT_800bf318.pBlockStart + 128))->VideoFlags;
	}

	if (DAT_800d16a4 == 1 && !DAT_800a5398[DAT_800d1e28].isCompetition) {
		if (DAT_800d17c4 & 2) {
			DAT_800d17d0->Visible = 1;
			DAT_800d17d4->Visible = 1;
			DAT_800d17d8->Visible = 1;
			DAT_800d17dc->Visible = 1;
			DAT_800d17e0->Visible = 1;
		}

		if (DAT_800d17c4 & 1)
			DAT_800d17e4->Visible = 1;
	}

	if (DAT_800d1de8) {
		CBody *pSkater = DAT_800d19a4;
		CBody *pSkater2 = pSkater->pNext;

		if (DAT_800d1de8 > 0) {
			DAT_800bf318.ReplayHighlight = DAT_800d1de8;
			DAT_800bf3d8.ReplayHighlight = DAT_800d1de8;
			Video_Start__FP6CBruce10EVideoModeii(pSkater, 2, DAT_800bf318.Highlights[DAT_800d1de8 - 1].FromFrame,
			             DAT_800bf318.Highlights[DAT_800d1de8 - 1].ToFrame);

			if (pSkater2)
				Video_Start__FP6CBruce10EVideoModeii(pSkater2, 2, DAT_800bf318.Highlights[DAT_800d1de8 - 1].FromFrame,
				             DAT_800bf318.Highlights[DAT_800d1de8 - 1].ToFrame);

			Video_SyncObsIfNeeded__Fv();
		} else {
			DAT_800d1de8 = 0;
			DAT_800bf318.ReplayHighlight = 0;
			DAT_800bf3d8.ReplayHighlight = 0;
			Video_Start__FP6CBruce10EVideoModeii(pSkater, 2, 1, 0x7fffffff);

			if (pSkater2)
				Video_Start__FP6CBruce10EVideoModeii(pSkater2, 2, 1, 0x7fffffff);
		}

		DAT_800d1784 = 0;
		Flash_Reset__Fv();

		DAT_800d19a4->m330 = DAT_800d1a24 + 216030;

		if (DAT_800d19a4->pNext)
			DAT_800d19a4->pNext->m330 = DAT_800d1a24 + 216030;
	} else {
		Video_Cleanup__Fv();

		{
			CBody *pSkater = DAT_800d19a4;
			CBody *pSkater2 = pSkater->pNext;

			if (!DAT_800bf318.VideoMode && !FUN_8007cd64(DAT_800d2044)) {
				Video_Start__FP6CBruce10EVideoModeii(pSkater, 1, 1, 0x7fffffff);

				if (pSkater2)
					Video_Start__FP6CBruce10EVideoModeii(pSkater2, 1, 1, 0x7fffffff);

				((SVideoHead *)(DAT_800bf318.pBlockStart + 128))->VideoFlags = DAT_800d17c4;
			}
		}
	}

	XStart = DAT_800d1a24;

	if (DAT_800d1780 == 1)
		FUN_800920b4(1);

	{
		CSkater *p = DAT_800d17c8;
		int x = p->m7d8.vx, y = p->m7d8.vy, z = p->m7d8.vz;

		p->mVel.vx = x * 20;
		p->mVel.vy = y * 20;
		p->mVel.vz = z * 20;
	}

	for (int i = 0; i < 10; i++)
		Ob_AI__FPP5CBody(&DAT_800d2044);

	DAT_800d1a1c = 0;
	DAT_800d17c8->mVel.vx = 0;
	DAT_800d17c8->mVel.vy = 0;
	DAT_800d17c8->mVel.vz = 0;

	while (!DAT_800d16e0) {
		unsigned StartVblanks = DAT_800d1a20;

		FUN_800242cc();

		if (!DAT_800d17c8->Dead && (!DAT_800d17cc || !DAT_800d17cc->Dead) && DAT_800d1784 == 1) {
			if (--DAT_800d1788 <= 0) {
				if (DAT_800d16a4 != 7 && DAT_800d17c8->ma64) {
					DAT_800d178c = 0;
					DAT_800d1788 = 1;
				} else {
					if (DAT_800d17c8->m6c8) {
						SFX_Stop__FUi(DAT_800d17c8->m6c4);

						DAT_800d17c8->m6c8 = 0;
					}

					if (DAT_800d17c8->m6cc) {
						SFX_Stop__FUi(DAT_800d17c8->m6cc);

						DAT_800d17c8->m6cc = 0;
					}

					if (DAT_800d17cc && DAT_800d17cc->m6c8) {
						SFX_Stop__FUi(DAT_800d17cc->m6c8);

						DAT_800d17cc->m6c8 = 0;
					}

					if (DAT_800d17cc && DAT_800d17cc->m6cc) {
						SFX_Stop__FUi(DAT_800d17cc->m6cc);

						DAT_800d17cc->m6cc = 0;
					}

					DAT_800d1784 = 0;

					if (DAT_800a5398[DAT_800d1e28].isCompetition && DAT_800d16a4 == 1)
						FUN_8001a1c8();
					else
						Front_SwitchOnEndLevelMenu__Fv();
				}
			}
		}

		FUN_80010bb8();
		FUN_80024258();
		System_Logic();
		Video_HandleStepping__Fv();

		if (DAT_800d1784 == 1 && !DAT_800d140c) {
			if (!DAT_800d17c8->Dead) {
				uchar c = DAT_800c0a48[0].Circle.Pressed;

				Pad_ClearAllOne__Fi(0);

				DAT_800c0a48[0].Down.Pressed = 1;
				DAT_800c0a48[0].Circle.Pressed = c;
			}

			if (DAT_800d1780 == 2 && !DAT_800d17cc->Dead) {
				uchar c = DAT_800c0a48[1].Circle.Pressed;

				Pad_ClearAllOne__Fi(1);

				DAT_800c0a48[1].Down.Pressed = 1;
				DAT_800c0a48[1].Circle.Pressed = c;
			}
		}

		if ((DAT_800d1780 == 1 || (DAT_800d16a4 == 7 && DAT_800d17c0)) && !DAT_800d1728)
			Pad_ClearAllOne__Fi(1);

		Game_Logic__Fv();

		if (DAT_800d16e0)
			break;

		Game_Logic__Fv();

		if (DAT_800d16e0)
			break;

		FUN_80048fec();
		FUN_80025440();
		FUN_80024fa4();

		if (!DAT_800d16fc && DAT_800d1718)
			Panel_DrawFlatShadedPoly__FiiiiUcUcUci(448, 208, 54, 18, 0, 0, 0, 0);

		if (!DAT_800d1cb0)
			Front_PrintDemo__Fv();

		FUN_8002357c(DAT_800a5398[DAT_800d1e28].m60 && (DAT_800d1780 == 1 || DAT_800d16a4 == 7)
		                 ? DAT_800d215c
						 : 0);

		DAT_800d215c = 0;

		if (DAT_800d1a20 == StartVblanks)
			Pause__Fi(1);

		Db_Render__Fv();

		if (DAT_800d1a20 == StartVblanks + 1)
			Pause__Fi(1);

		if (DAT_800d16a4 == 7) {
			if (!DAT_800d16cc) {
				DAT_800d17a8 = 1;
				DAT_800d16cc = 1;
				FUN_8001a5e0();
			} else if (!DAT_800d17a8) {
				DAT_800d17a8 = 1;
				Front_SwitchOnStartLevelMenu__Fv();
			}
		}

		if (FUN_80043ce8(DAT_800d19a4))
			DAT_800d16e0 = 2;
	}
done:
	FUN_800920b4(3);
	Spool_Sync__Fv();

	DAT_800d214c = 1;
	Front_SaveGameState__Fv();
	FUN_80048fec();
	FUN_8008c468(0);
	FUN_800491e8();
	FUN_80010ac0();
	FUN_8001f138(DAT_800d1798);
	Mess_UnloadFont__Fv();
	FUN_8001f138(DAT_800d1794);
	Mess_UnloadFont__Fv();
	FUN_8001f138(DAT_800d1790);
	Mess_UnloadFont__Fv();
}
