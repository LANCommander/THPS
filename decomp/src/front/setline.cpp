/* SetLine__5CMenuUc (0x80016708) */
/* C++ (FRONT.CPP). Demo twin (same lines). Selects menu line Line: it scales up, the rest down. */
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
	void SetLine(uchar Line);
};
void CMenu::SetLine(uchar Line)
{
	mLine = Line;
	for (int i = 0; i < 15; i++) {
		mEntry[i].TargetScale = (i == mLine) ? mEntry[i].HiScale : mEntry[i].LowScale;
		mEntry[i].CurrentScale = mEntry[i].TargetScale;
	}
}
