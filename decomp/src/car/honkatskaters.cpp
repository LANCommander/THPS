/* HonkAtSkaters__FP4CCarG7CVector (0x8006bd44) */
/* C++ (CAR.CPP). Demo twin HonkAtSkaters (0.26): THPS1 has no skater table, so it checks the
   player skater (DAT_800d19a4) and the one linked after it. A car honks (by type) once when a
   skater within 2000 units is inside the cone ahead of it; the flag at +0x220 rearms when clear.
   FUN_80072038 = 64-bit cross-product sign helper, FUN_8004b250 = SFX_PlayX. Each honk case
   makes its own SFX call; cross-jumping merges them into retail's single jal. */
typedef unsigned short ushort;
struct CVector { int vx, vy, vz; };
class CBruce {
public:
	char pad0[4];
	CVector mPos;             /* 0x04 */
	char pad10[0x1c - 0x10];
	CBruce *mpNext;           /* 0x1c */
};
class CCar {
public:
	char pad0[4];
	CVector mPos;             /* 0x04 */
	char pad10[0x3a - 0x10];
	ushort mType;             /* 0x3a */
	char pad3c[0x220 - 0x3c];
	int mHonked;              /* 0x220 */
};
struct SVideoInfo {
	int VideoMode;
	char pad4[0xc0 - 4];
};
extern SVideoInfo DAT_800bf318;
extern SVideoInfo DAT_800bf3d8;
extern CBruce *DAT_800d19a4;
int Utils_CrapDist(const CVector &, const CVector &);
int Redbook_Rnd(int);
extern "C" {
int FUN_80072038(int, int, int, int);
int FUN_8004b250(int, short, int);
}

void HonkAtSkaters(CCar *pCar, CVector Front)
{
	int Honk = 0;
	if (DAT_800bf318.VideoMode == 2 || DAT_800bf3d8.VideoMode == 2)
		return;
	CBruce *pSkater = DAT_800d19a4;
	CBruce *pOther = pSkater->mpNext;
	if (Utils_CrapDist(pCar->mPos, pSkater->mPos) < 2000) {
		int LeftX = -Front.vz + Front.vx;
		int LeftZ = Front.vx + Front.vz;
		int VecX = pSkater->mPos.vx - pCar->mPos.vx;
		int VecZ = pSkater->mPos.vz - pCar->mPos.vz;
		if (FUN_80072038(LeftX, VecX, LeftZ, VecZ) > 0) {
			int RightX = Front.vz + Front.vx;
			int RightZ = Front.vz - Front.vx;
			Honk = FUN_80072038(RightX, VecX, RightZ, VecZ) > 0;
		}
	}
	if (pOther && !Honk) {
		if (Utils_CrapDist(pCar->mPos, pOther->mPos) < 2000) {
			int LeftX = -Front.vz + Front.vx;
			int LeftZ = Front.vx + Front.vz;
			int VecX = pOther->mPos.vx - pCar->mPos.vx;
			int VecZ = pOther->mPos.vz - pCar->mPos.vz;
			if (FUN_80072038(LeftX, VecX, LeftZ, VecZ) > 0) {
				int RightX = Front.vz + Front.vx;
				int RightZ = Front.vz - Front.vx;
				if (FUN_80072038(RightX, VecX, RightZ, VecZ) > 0)
					Honk = 1;
			}
		}
	}
	if (Honk) {
		if (!pCar->mHonked) {
			switch (pCar->mType) {
			case 213: FUN_8004b250(Redbook_Rnd(3) + 110, 0x2000, 0); break;
			case 214: FUN_8004b250(122, 0x2000, 0); break;
			case 215: FUN_8004b250(130, 0x2000, 0); break;
			case 216: FUN_8004b250(120, 0x2000, 0); break;
			}
			pCar->mHonked = 1;
		}
	} else
		pCar->mHonked = 0;
}
