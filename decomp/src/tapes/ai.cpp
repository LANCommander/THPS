/* AI__5CTapei (0x800733ec) */
/* C++ (TAPES.CPP). Locals, their order and types come from the demo's MAIN.SYM; field offsets are THPS1's
   (its CBody is 0x2c bytes larger than the THPS2 demo's). */
struct CVector {
	int vx, vy, vz;
};

CVector operator+(const CVector &, const CVector &);
CVector operator-(const CVector &, const CVector &);
CVector operator*(const CVector &, const int &);
CVector operator/(const CVector &, const int &);

struct CSVector {
	short vx, vy, vz;
	void Set(short x, short y, short z) {
		vx = x;
		vy = y;
		vz = z;
	}
};

struct STapeMessage {
	int essential;
	char *Line1, *Line2, *Line3;
};

class CTape {
  public:
	char CBody_0[0x24];
	CSVector mScale;
	char CBody_2a[0x134 - 0x2a];
	void *mpGlow;
	unsigned short mGlowRadiusOrg, mGlowRadiusAmp;
	STapeMessage *mMessageTable;
	int mSessionTapeNum;
	int mTapeNum;
	int mTextX, mTextY;
	int mSize, mSize1, mSize2;
	CVector mVec1, mVec2;
	unsigned char mHasNode, mIs3d, mDropping, mDropForever, mHoverHeight;
	unsigned short mNodeIndex;
	int mGroundY;
	CVector mOrgPos;
	unsigned short mT, mMaxWobbleAmplitude, mWobbleAmplitude, mWobbleSpeed, mLifetime;
	unsigned int mTimer;

	void AI(int tape_no);
	void DoPhysics(void);
	void CreateBit(void);
};

extern CTape *DAT_800a5b14[5];

int DAT_800d1fbc, DAT_800d1fb8;

void Mess_SetTextJustify(unsigned char);
void Mess_SetScale(int);
void Mess_SetRGB(unsigned char, unsigned char, unsigned char, int);
void Mess_DrawText(int, int, const char *, int, unsigned int, int, bool);

void CTape::AI(int tape_no) {
	mTimer++;

	if (mTimer < 60)
		DAT_800d1fbc = 1;
	else
		DAT_800d1fbc = 0;

	if (mSessionTapeNum * 20 + 80 < mTimer)
		DAT_800d1fb8 = 1;
	else
		DAT_800d1fb8 = 0;

	if (mTimer > 60) {
		int temptime = mTimer - 60;
		CVector pos_offset = (mVec2 - mVec1) * temptime / 20;
		int size_offset = (mSize2 - mSize1) * temptime / 20;

		if (temptime < 20) {
			mOrgPos = pos_offset + mVec1;
			mSize = size_offset + mSize1;
			mWobbleAmplitude = mMaxWobbleAmplitude - mMaxWobbleAmplitude * temptime / 20;
		} else {
			mOrgPos = mVec2;
			mWobbleAmplitude = 0;
			mSize = mSize2;
		}
	}

	int message_count = 0;
	STapeMessage *messages[5];
	int message_no;

	messages[0] = 0;
	messages[1] = 0;
	messages[2] = 0;
	messages[3] = 0;
	messages[4] = 0;
	mScale.Set(mSize, mSize, mSize);

	for (int i = 0; i < 5; i++) {
		if (DAT_800a5b14[i]) {
			if (i == 4) {
				messages[4] = &mMessageTable[DAT_800a5b14[4]->mTapeNum];
			} else {
				STapeMessage *m =
				    (STapeMessage *)((DAT_800a5b14[i]->mTapeNum << 4) + (int)mMessageTable);

				if (m->essential == 1)
					messages[i] = m;
			}
		} else {
			messages[i - 1] = &mMessageTable[DAT_800a5b14[i - 1]->mTapeNum];
			break;
		}
	}

	for (int i = 0; i < 5; i++)
		if (messages[i])
			message_count++;

	message_no = 0;

	for (int i = 0; i < mSessionTapeNum; i++)
		if (messages[i])
			message_no++;

	if (message_no * 20 + 80 < mTimer && messages[mSessionTapeNum]) {
		switch (message_count) {
			case 1:
				mTextX = 130;
				mTextY = 120;
				break;
			case 2:
				switch (message_no) {
					case 0:
						mTextX = 130;
						mTextY = 85;
						break;
					case 1:
						mTextX = 130;
						mTextY = 155;
						break;
				}

				break;
			case 3:
				switch (message_no) {
					case 0:
						mTextX = 130;
						mTextY = 64;
						break;
					case 1:
						mTextX = 130;
						mTextY = 120;
						break;
					case 2:
						mTextX = 130;
						mTextY = 176;
						break;
				}

				break;
			case 4:
				switch (message_no) {
					case 0:
						mTextX = 130;
						mTextY = 50;
						break;
					case 1:
						mTextX = 150;
						mTextY = 92;
						break;
					case 2:
						mTextX = 130;
						mTextY = 134;
						break;
					case 3:
						mTextX = 150;
						mTextY = 176;
						break;
				}

				break;
			case 5:
				switch (message_no) {
					case 0:
						mTextX = 130;
						mTextY = 50;
						break;
					case 1:
						mTextX = 150;
						mTextY = 85;
						break;
					case 2:
						mTextX = 130;
						mTextY = 120;
						break;
					case 3:
						mTextX = 150;
						mTextY = 155;
						break;
					case 4:
						mTextX = 130;
						mTextY = 190;
						break;
				}

				break;
		}

		Mess_SetTextJustify(1);
		Mess_SetScale(224);
		Mess_SetRGB(122, 122, 122, 0);

		if (!messages[mSessionTapeNum]->Line2) {
			Mess_DrawText(mTextX, mTextY, messages[mSessionTapeNum]->Line1, 0, 0, 256, 0);
		} else if (!messages[mSessionTapeNum]->Line3) {
			Mess_DrawText(mTextX, mTextY - 8, messages[mSessionTapeNum]->Line1, 0, 0, 256, 0);
			Mess_DrawText(mTextX, mTextY + 8, messages[mSessionTapeNum]->Line2, 0, 0, 256, 0);
		} else {
			Mess_DrawText(mTextX, mTextY - 16, messages[mSessionTapeNum]->Line1, 0, 0, 256, 0);
			Mess_DrawText(mTextX, mTextY, messages[mSessionTapeNum]->Line2, 0, 0, 256, 0);
			Mess_DrawText(mTextX, mTextY + 16, messages[mSessionTapeNum]->Line3, 0, 0, 256, 0);
		}
	}

	DoPhysics();

	if (!mIs3d)
		CreateBit();
}
