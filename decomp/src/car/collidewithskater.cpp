/* CollideWithSkater__FP4CCarP6CBruceRC6MATRIXPs (0x8006b6c0) */
/* C++ (CAR.CPP). Fuzzy demo twin (0.96); locals from its MAIN.SYM. Tests the skater's last move
   against a car's bounding box, in car space via the GTE. A grounded skater landing on top bounces
   off with sparks. Otherwise the skater is knocked down, thrown sideways or backwards, and the car
   honks (by type). */
extern "C" {
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <stdlib.h>
}
typedef unsigned short ushort;
#define MTC2(n, v) __asm__ volatile ("mtc2 %0, $" #n : : "r"(v))
#define ABS(x) (((x) ^ ((x) >> 31)) - ((x) >> 31))
#define CTC2(n, v) __asm__ volatile ("ctc2 %0, $" #n : : "r"(v))
struct CVector { int vx, vy, vz; };
struct CSVector { short vx, vy, vz; };
class CCar {
public:
	char pad0[4];
	CVector mPos;             /* 0x04 */
	char pad10[0x3a - 0x10];
	ushort mType;             /* 0x3a */
	char pad3c[0x6c - 0x3c];
	CVector mVel;             /* 0x6c */
};
class CBruce {
public:
	char pad0[4];
	CVector mPos;             /* 0x04 */
	CSVector mAngles;         /* 0x10 */
	char pad16[0x6c - 0x16];
	CVector mVel;             /* 0x6c */
	char pad78[0xf0 - 0x78];
	CVector mOldPos;          /* 0xf0 */
	char padfc[0x1a0 - 0xfc];
	CCar *mLastCar;           /* 0x1a0 */
	char pad1a4[0x358 - 0x1a4];
	int mInAir;               /* 0x358 */
	char pad35c[0x734 - 0x35c];
	int m734;                 /* 0x734 */
	void Vibrate(int, int, int);
	void SetAnglesFromHeading();
	void BloodSplat(int, int);
};
extern int DAT_800a5e1c[];
extern int DAT_800d1868;
extern int DAT_800d186c;
extern char DAT_800a824c[];
unsigned int Utils_CrapDist(const CVector &, const CVector &);
int Redbook_Rnd(int);
void Bit_SetSparkTrajectory(const CSVector &);
extern "C" {
void FUN_80043408(CBruce *);
int FUN_8004b250(int, short, int);
void FUN_8002f340(CBruce *, int, int, int, int);
void FUN_8002952c(CSVector *);
void *FUN_80027d08(int);
void FUN_80027650(void *, CBruce *, char *, int, int, int);
void FUN_8002fe9c(CBruce *, int);
}

void CollideWithSkater(CCar *pCar, CBruce *pSkater, const MATRIX &tm, short *pBox)
{
	if (pCar == pSkater->mLastCar)
		return;
	if (pSkater->mInAir && pSkater->m734)
		return;
	if (Utils_CrapDist(pSkater->mPos, pCar->mPos) >= 500)
		return;
	{
		VECTOR OldPos;
		VECTOR Pos;
		int OldX, OldY, OldZ;
		int NewX, NewY, NewZ;
		int XMin, XMax, YMin, YMax, ZMin, ZMax;
		int tmp;

		OldX = pSkater->mOldPos.vx - pCar->mPos.vx;
		OldY = pSkater->mOldPos.vy - pCar->mPos.vy;
		OldZ = pSkater->mOldPos.vz - pCar->mPos.vz;
		NewX = pSkater->mPos.vx - pCar->mPos.vx;
		NewY = pSkater->mPos.vy - pCar->mPos.vy;
		NewZ = pSkater->mPos.vz - pCar->mPos.vz;
		CTC2(0, ((int *)&tm)[0]);
		CTC2(1, ((int *)&tm)[1]);
		CTC2(2, ((int *)&tm)[2]);
		CTC2(3, ((int *)&tm)[3]);
		CTC2(4, ((int *)&tm)[4]);
		MTC2(9, OldX >> 12);
		MTC2(10, OldY >> 12);
		MTC2(11, OldZ >> 12);
		gte_rtir_sf0();
		gte_stlvnl(&OldPos);
		MTC2(9, NewX >> 12);
		MTC2(10, NewY >> 12);
		MTC2(11, NewZ >> 12);
		gte_rtir_sf0();
		gte_stlvnl(&Pos);
		XMin = OldPos.vx;
		XMax = Pos.vx;
		if (XMax < XMin) {
			tmp = XMin;
			XMin = XMax;
			XMax = tmp;
		}
		XMin -= 0x14000;
		XMax += 0x14000;
		YMin = OldPos.vy;
		YMax = Pos.vy;
		if (YMax < YMin) {
			tmp = YMin;
			YMin = YMax;
			YMax = tmp;
		}
		YMin -= 0x14000;
		YMax += 0x14000;
		ZMin = OldPos.vz;
		ZMax = Pos.vz;
		if (ZMax < ZMin) {
			tmp = ZMin;
			ZMin = ZMax;
			ZMax = tmp;
		}
		ZMin -= 0x14000;
		ZMax += 0x14000;
		if (XMax < pBox[1] << 12 || pBox[0] << 12 < XMin)
			return;
		if (ZMax < pBox[5] << 12 || pBox[4] << 12 < ZMin)
			return;
		if (YMax < pBox[3] << 12 || pBox[2] << 12 < YMin)
			return;
		{
			int CarHeight = 0;
			if (pCar->mType == 215)
				CarHeight = 0x46000;
			else if (pCar->mType == 216)
				CarHeight = 0x64000;
			if (!pSkater->mInAir && pSkater->m734 == 1 && CarHeight < pCar->mPos.vy - pSkater->mPos.vy) {
				pSkater->mVel.vx >>= 1;
				pSkater->mVel.vy >>= 1;
				pSkater->mVel.vz >>= 1;
				pSkater->mVel.vy -= 0x1e000;
				pSkater->Vibrate(8, 1, 150);
				FUN_80043408(pSkater);
				FUN_8004b250(40, 0x2000, 0);
				FUN_8002f340(pSkater, 78, DAT_800a5e1c[0], -1000, 0);
				{
					int n = DAT_800d1868;
					pSkater->mLastCar = pCar;
					if (n >= 200)
						return;
				}
				pSkater->SetAnglesFromHeading();
				Bit_SetSparkTrajectory(pSkater->mAngles);
				{
					CSVector cone;
					int i;
					cone.vx = 450;
					cone.vy = 900;
					cone.vz = 0;
					FUN_8002952c(&cone);
					DAT_800d186c = 0;
					for (i = 0; i < 20; i++) {
						void *p = FUN_80027d08(120);
						if (p)
							FUN_80027650(p, pSkater, DAT_800a824c, -40, 4096, 5);
					}
					DAT_800d186c = 1;
				}
				return;
			}
		}
		switch (Redbook_Rnd(16) >> 3) {
		case 0: {
			int vx = pCar->mVel.vx;
			int vz = pCar->mVel.vz;
			if (ABS(vx) > ABS(vz)) {
				int t;
				vx += vx >> 1;
				t = Redbook_Rnd(vx >> 1) + (vx >> 2);
				if (Redbook_Rnd(16) >> 3)
					t = -t;
				vz += t;
			} else {
				int t;
				vz += vz >> 1;
				t = Redbook_Rnd(vz >> 1) + (vz >> 2);
				if (Redbook_Rnd(16) >> 3)
					t = -t;
				vx += t;
			}
			pSkater->mVel.vx = vx;
			pSkater->mVel.vy = pCar->mVel.vy - 0x16800;
			pSkater->mVel.vz = vz;
			break;
		}
		case 1:
			pSkater->mVel.vx = -pCar->mVel.vx >> 2;
			pSkater->mVel.vy = -0x2d000;
			pSkater->mVel.vz = -pCar->mVel.vz >> 2;
			break;
		}
		pSkater->mLastCar = pCar;
		FUN_8002fe9c(pSkater, 1);
		pSkater->BloodSplat(1, 100);
		pSkater->Vibrate(12, 1, 255);
		FUN_80043408(pSkater);
		FUN_8004b250(114, 0x2000, 0);
		{
			int sfx;
			switch (pCar->mType) {
			case 213:
				sfx = Redbook_Rnd(4) + 115;
				break;
			case 214:
				sfx = Redbook_Rnd(4) + 125;
				break;
			case 215:
				sfx = 131;
				break;
			case 216:
				sfx = 120;
				break;
			default:
				return;
			}
			FUN_8004b250(sfx, 0x2000, 0);
		}
	}
}
