/* CamPt_SetClosestCamera__FP6CBruce (0x8004e268) */
typedef unsigned long ulong;

struct CVector {
	int vx, vy, vz;
};

class CBody;

class CCamera {
  public:
	char pad0[4];
	CVector mPos;
	char pad10[0x420 - 0x10];
	CBody *mpTripod; /* 0x420 */
	char pad424[4];
	int mTripodMode; /* 0x428 */
	char pad42c[0x438 - 0x42c];
	int mDirty;         /* 0x438 */
	CVector mTripodPos; /* 0x43c */
	char pad448[0x458 - 0x448];
	CBody *mpFocus; /* 0x458 */
	int mFocusMode; /* 0x45c */
	char pad460[0x584 - 0x460];
	int mMode; /* 0x584 */
	char pad588[0x5f0 - 0x588];
	int m5f0; /* 0x5f0 */
	void SetMode(int m) {
		mMode = m;
	}
	void SetFocus(CBody *focus) {
		mFocusMode = 1;
		mpFocus = focus;
		mDirty = 1;
	}
	void SetTripod(CBody *tripod) {
		mTripodMode = 1;
		mpTripod = tripod;
	}
	void SetTripodPos(const CVector &p) {
		mTripodMode = 0;
		mTripodPos = p;
		mpTripod = 0;
		mDirty = 1;
	}
};

class CBruce {
  public:
	char pad0[4];
	CVector mPos;
	char pad10[0x1d8 - 0x10];
	CCamera *mpCamera; /* 0x1d8 */
	char pad1dc[0x7f0 - 0x1dc];
	CVector mUp; /* 0x7f0 */
};

struct SVideoInfo {
	int VideoMode;
	ulong *pBlockStart, *pStreamStart, *pStreamEnd, *pStream;
	ulong Bits;
	int BitsLeft;
	ulong NumFrames;
	ulong FramesLeft;
	int CurCameraIndex;
	CVector CamPos;
	int CamMode, CamXblanks, TabuCam, NoLOS, OldCameraIndex, TrailingCameraType;
};

struct SFog {
	char pad0[12];
	short m12;
};

extern SVideoInfo DAT_800bf318;
extern SVideoInfo DAT_800bf3d8;
extern CBruce *DAT_800d19a4;
extern unsigned int DAT_800d1a24;
extern short DAT_800be344[];
extern unsigned int DAT_800be22c[];

int DAT_800d1b6c;

extern SFog *DAT_800d2178;
extern int DAT_800d1ff4;
extern int DAT_800d1ff8;
extern int DAT_800d1ffc;
extern int DAT_800d2134;
extern int DAT_800d2138;
extern int DAT_800d2168;
extern int DAT_800d216c;

int Utils_LineOfSight(const CVector &, const CVector &);
short *Trig_GetPosition(CVector &, int);
ulong Utils_CrapDist(const CVector &, const CVector &);
int Utils_Dist(const CVector &, const CVector &);
int Redbook_Rnd(int);

void CamPt_SetClosestCamera(CBruce *pSkater) {
	ulong ClosestDist = 0x7fffffff;
	ulong ClosestDist2;
	ulong Dist;
	int Index = -1;
	int Index2;
	CVector CamPos;
	CVector ClosestPos;
	CVector ClosestPos2;
	CVector AdjustedPlayerPos;
	SVideoInfo *VInfo;

	AdjustedPlayerPos = pSkater->mPos;
	AdjustedPlayerPos.vx += pSkater->mUp.vx * 110;
	AdjustedPlayerPos.vy += pSkater->mUp.vy * 110;
	AdjustedPlayerPos.vz += pSkater->mUp.vz * 110;

	if (pSkater == DAT_800d19a4)
		VInfo = &DAT_800bf318;
	else
		VInfo = &DAT_800bf3d8;

	if (Utils_LineOfSight(AdjustedPlayerPos, pSkater->mpCamera->mPos)) {
		VInfo->NoLOS = 0;
	} else if (++VInfo->NoLOS > 10) {
		VInfo->TabuCam = VInfo->CurCameraIndex;
	}

	{
		int i;

		for (i = 0; i < DAT_800d1b6c; i++) {
			if (i == VInfo->TabuCam)
				continue;

			Trig_GetPosition(CamPos, DAT_800be344[i]);

			Dist = Utils_CrapDist(pSkater->mPos, CamPos);

			if (Dist < ClosestDist) {
				ClosestDist2 = ClosestDist;
				ClosestDist = Dist;
				Index2 = Index;
				Index = i;
				ClosestPos2 = ClosestPos;
				ClosestPos = CamPos;
			}
		}
	}

	if (Index != VInfo->CurCameraIndex && Index != -1) {
		if (!Utils_LineOfSight(AdjustedPlayerPos, ClosestPos)) {
			if (Index2 != VInfo->CurCameraIndex && Index2 != -1) {
				if (!Utils_LineOfSight(AdjustedPlayerPos, ClosestPos2))
					Index = -1;
				else {
					Index = Index2;
					ClosestPos = ClosestPos2;
					ClosestDist = ClosestDist2;
				}
			} else
				Index = -1;
		}
	}

	if (ClosestDist > 9000)
		Index = -1;

	if (Index != -1 && Index != VInfo->CurCameraIndex) {
		if (Index != VInfo->OldCameraIndex ||
		    DAT_800d1a24 >= (unsigned int)(VInfo->CamXblanks + 60)) {
			CVector Dummy;
			short *pCam;
			int Type;
			int Param;

			pCam = Trig_GetPosition(Dummy, DAT_800be344[Index]);
			Type = pCam[0];
			Param = pCam[1];
			DAT_800be22c[0] &= ~0xc00;

			if (Type == 1)
				DAT_800be22c[0] |= 0x400;
			else
				DAT_800be22c[0] |= 0x800;

			DAT_800be22c[0] = (DAT_800be22c[0] & ~0xff) + (Redbook_Rnd(5) + 5) * 10;
			DAT_800be22c[Index] = DAT_800be22c[0];

			if (ClosestDist > 4000) {
				int Val = 10000 - ClosestDist;

				if (Val < 0)
					Val = 0;

				DAT_800be22c[0] = (DAT_800be22c[0] & ~0xff) + (Val = Val / 200 + 10);
			}

			{
				int t = DAT_800d1a24;
				int o = VInfo->CurCameraIndex;

				VInfo->CurCameraIndex = Index;
				VInfo->CamXblanks = t;
				VInfo->OldCameraIndex = o;
			}

			VInfo->CamPos = ClosestPos;

			if (DAT_800be22c[Index] & 0x800) {
				pSkater->mpCamera->SetMode(1);
				pSkater->mpCamera->SetFocus((CBody *)pSkater);
				pSkater->mpCamera->SetTripod((CBody *)pSkater);

				VInfo->TrailingCameraType = Param;
			} else if (DAT_800be22c[Index] & 0x400) {
				pSkater->mpCamera->SetMode(2);
				pSkater->mpCamera->SetFocus((CBody *)pSkater);
				pSkater->mpCamera->SetTripodPos(ClosestPos);
			}
		}
	}

	{
		unsigned int *pFlags;
		unsigned int *base = DAT_800be22c;

		Index = VInfo->CurCameraIndex;
		pFlags = base + Index;

		if (*pFlags & 0x800) {
			pSkater->mpCamera->m5f0 = 0;

			switch (VInfo->TrailingCameraType) {
				case 0:
					DAT_800d1ff4 = 245;
					DAT_800d1ff8 = 215;
					DAT_800d2178->m12 = 2410;
					pSkater->mpCamera->m5f0 = 0;
					DAT_800d1ffc = -70;
					break;
				case 1:
					DAT_800d1ff4 = 175;
					DAT_800d1ff8 = 50;
					DAT_800d2178->m12 = 2930;
					pSkater->mpCamera->m5f0 = 0;
					DAT_800d1ffc = -17;
					break;
				case 2:
					DAT_800d1ff4 = 290;
					DAT_800d1ff8 = 150;
					DAT_800d2178->m12 = 3410;
					pSkater->mpCamera->m5f0 = 0;
					DAT_800d1ffc = -108;
					break;
				case 3:
					break;
				case 4:
					DAT_800d1ff4 = 245;
					DAT_800d1ff8 = 215;
					DAT_800d1ffc = -70;
					DAT_800d2178->m12 = 2410;
					pSkater->mpCamera->m5f0 = 2048;
					break;
				case 5:
					DAT_800d1ff4 = 195;
					DAT_800d1ff8 = 50;
					DAT_800d1ffc = -17;
					DAT_800d2178->m12 = 2930;
					pSkater->mpCamera->m5f0 = 2048;
					break;
				case 6:
					DAT_800d1ff4 = 290;
					DAT_800d1ff8 = 150;
					DAT_800d1ffc = -108;
					DAT_800d2178->m12 = 3410;
					pSkater->mpCamera->m5f0 = 2048;
					break;
			}
		} else if (*pFlags & 0x400) {
			if (*pFlags & 0x200) {
				DAT_800d2178->m12 = (256 - (*pFlags & 255)) * 10 + 300;
			} else if (*pFlags & 0x100) {
				int Dist;
				int FogDist;

				FogDist = Utils_Dist(pSkater->mPos, VInfo->CamPos);

				if (FogDist > 2400)
					Dist = 2400;
				else
					Dist = FogDist;

				if (Dist < 450)
					Dist = 450;

				DAT_800d216c = FogDist + DAT_800d2138;
				DAT_800d2168 = DAT_800d216c + (DAT_800d2134 - DAT_800d2138);
				DAT_800d2178->m12 = (int)(*pFlags & 255) * 34130 / Dist;
			}
		}
	}
}
