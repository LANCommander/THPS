/* Update__5CMenu (0x80016dc0) */
/* C++ (FRONT.CPP). Types from the demo's MAIN.SYM. */
typedef unsigned char uchar;

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

struct CMenu {
	int **vf;
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
	void Update();
};

struct SPad {
	uchar b[364];
};

extern SPad Pad[];

int UpDownAutoRepeatTimer;

int SFX_PlayX(unsigned int, short, int);

void CMenu::Update() {
	while (!mEntry[mLine].Visible) {
		mEntry[mLine].TargetScale = mEntry[mLine].LowScale;
		mEntry[mLine].CurrentScale = mEntry[mLine].LowScale;
		mLine++;

		if (mLine >= mNumLines)
			mLine = 0;

		mEntry[mLine].TargetScale = mEntry[mLine].HiScale;
		mEntry[mLine].CurrentScale = mEntry[mLine].LowScale;
	}

	if (Pad[0].b[0xa0] || Pad[0].b[0xb0] || Pad[1].b[0xa0] ||
	    Pad[1].b[0xb0]) {
		if (UpDownAutoRepeatTimer == 0 || (UpDownAutoRepeatTimer >= 16 && (UpDownAutoRepeatTimer & 3) == 0)) {
			if (Pad[0].b[0xa0] || Pad[1].b[0xa0]) {
				mEntry[mLine].TargetScale = mEntry[mLine].LowScale;

				do {
					if (mLine == 0)
						mLine = mNumLines - 1;
					else
						mLine--;
				} while (!mEntry[mLine].Visible || !mEntry[mLine].Enabled);

				mEntry[mLine].TargetScale = mEntry[mLine].HiScale;
				SFX_PlayX(6, 8192, 0);
			}

			if (Pad[0].b[0xb0] || Pad[1].b[0xb0]) {
				mEntry[mLine].TargetScale = mEntry[mLine].LowScale;

				do {
					mLine++;

					if (mLine >= mNumLines)
						mLine = 0;
				} while (!mEntry[mLine].Visible || !mEntry[mLine].Enabled);

				mEntry[mLine].TargetScale = mEntry[mLine].HiScale;
				SFX_PlayX(6, 8192, 0);
			}
		}

		UpDownAutoRepeatTimer++;
	} else {
		UpDownAutoRepeatTimer = 0;
	}

	for (int i = 0; i < mNumLines; i++) {
		if (mEntry[i].CurrentScale < mEntry[i].TargetScale) {
			mEntry[i].CurrentScale += 40;

			if (mEntry[i].CurrentScale > mEntry[i].TargetScale)
				mEntry[i].CurrentScale = mEntry[i].TargetScale;
		}

		if (mEntry[i].CurrentScale > mEntry[i].TargetScale) {
			mEntry[i].CurrentScale -= 40;

			if (mEntry[i].CurrentScale < mEntry[i].TargetScale)
				mEntry[i].CurrentScale = mEntry[i].TargetScale;
		}
	}
}
