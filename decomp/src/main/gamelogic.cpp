/* Game_Logic__Fv (0x80024868) flags=-fstructure-noalias */
/* C++ (MAIN.CPP). Fuzzy demo twin; locals (Frozen) from MAIN.SYM. Runs the per-frame game logic
   on every other frame: objects, tricks, panels, front end and messages, swapping the two pads
   around the front-end update in two-player mode. */
struct SControl {
	int b[91];
};

struct CBody;

struct CBodyPtrs {
	CBody *p;
};

struct SCareer {
	char pad[0x5f0];
	int Money;
};

struct CSkater {
	char pad1d8[0x1d8];
	SCareer *pCareer;
	char pad[0x734 - 0x1dc];
	int Dead;
};

extern "C" {
	extern SControl DAT_800c0a48[2];
	extern int DAT_800d140c[1];

	int DAT_800d16e8;
	int DAT_800d183c;
	int DAT_800d16e4;
	int DAT_800d16fc;
	int DAT_800d16a4;
	int DAT_800d1784;
	int DAT_800d1788;
	int DAT_800d178c;
	int DAT_800d179c;
	CSkater *DAT_800d17c8;
	CSkater *DAT_800d17cc;

	extern CBody *DAT_800d1998;
	extern CBody *DAT_800d19b0;
	extern CBody *DAT_800d19a4;
	extern CBody *DAT_800d1618;
	extern CBody *DAT_800d1fe4;
	extern CBody *DAT_800d2044;

	void Front_Update__Fv(void);
	void FUN_80027c54(void);
	void FUN_8002aa6c(void);
	void Ob_AI__FPP5CBody(CBody **);
	void Ob_QuickAI__FPP5CBody(CBody **);
	void FUN_80048044(void);
	void FileIO_Continue__Fv(void);
	void FUN_8004f8a0(void);
	void FUN_8006c4e8(void);
	void Spool_Continue__Fv(void);
	void Pad_Remap__Fv(void);
	void Pad_Restore__Fv(void);
	void TrickTips_Update__Fv(void);
	void Flash_Update__Fv(void);
	void Font_Reset__Fv(void);
	void Mess_Update__Fv(void);
	void Ob_ClearInputFlags__FP5CBody(CBody *);
	void Ob_MaybeUnSuspendOrCull__Fv(void);
	void Shatter_MaybeMakeGlassShatterSound__Fv(void);
	void TrickOb_Update__Fv(void);
}

void Game_Logic(void) {
	int Frozen;

	DAT_800d183c++;

	if (DAT_800d16e8++ & 1)
		return;

	DAT_800d16e4++;
	Font_Reset__Fv();

	Frozen = 0;

	if (DAT_800d140c[0] || DAT_800d16fc)
		Frozen = 1;

	if (!Frozen) {
		Flash_Update__Fv();
		FUN_80048044();
		Ob_ClearInputFlags__FP5CBody(DAT_800d1998);
		Ob_ClearInputFlags__FP5CBody(DAT_800d19b0);
		Ob_AI__FPP5CBody(&DAT_800d19a4);

		if (!DAT_800d140c[0]) {
			FUN_8002aa6c();
			FUN_8004f8a0();
			Ob_AI__FPP5CBody(&DAT_800d1618);
			TrickOb_Update__Fv();
			Ob_QuickAI__FPP5CBody(&DAT_800d19b0);
			Ob_QuickAI__FPP5CBody(&DAT_800d1fe4);
			Ob_MaybeUnSuspendOrCull__Fv();
			Ob_AI__FPP5CBody(&DAT_800d1998);
			FUN_80027c54();

			if (DAT_800d16a4 != 7)
				if (DAT_800d1784 == 1 && DAT_800d1788 < 40 && !DAT_800d17c8->Dead &&
				    (!DAT_800d17cc || !DAT_800d17cc->Dead)) {
					DAT_800d17c8->pCareer->Money += DAT_800d178c;

					if (DAT_800d17cc)
						DAT_800d17cc->pCareer->Money += DAT_800d178c;
				}
		}
	} else {
		if (DAT_800d1784 == 1)
			Ob_AI__FPP5CBody(&DAT_800d2044);
	}

	Shatter_MaybeMakeGlassShatterSound__Fv();
	FUN_8006c4e8();

	if (DAT_800d16a4 == 7 && DAT_800d179c == 1) {
		SControl t = DAT_800c0a48[0];

		DAT_800c0a48[0] = DAT_800c0a48[1];
		DAT_800c0a48[1] = t;
	}

	Pad_Remap__Fv();
	Front_Update__Fv();
	Pad_Restore__Fv();

	if (DAT_800d16a4 == 7 && DAT_800d179c == 1) {
		SControl t = DAT_800c0a48[0];

		DAT_800c0a48[0] = DAT_800c0a48[1];
		DAT_800c0a48[1] = t;
	}

	TrickTips_Update__Fv();
	Mess_Update__Fv();
	Spool_Continue__Fv();
	FileIO_Continue__Fv();
}
