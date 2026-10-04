/* BloodSplat__6CBruceii (0x80042ab0) */
extern "C" {
#include <sys/types.h>
#include <libgte.h>
}
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
struct CVector {
	int x, y, z;
	CVector &operator+=(const CVector &);
};
struct CSVector { short x, y, z; };
struct Vector { int vx, vy, vz; };
struct Item;
struct SLineInfo {
	Vector StartCoords;
	Vector EndCoords;
	Vector MinCoords;
	Vector MaxCoords;
	int iLo, iHi, jLo, jHi;
	int Distance;
	int Length;
	MATRIX WorldCst;
	Item *pItem;
	Vector Position;
	SVECTOR Normal;
	uint *pFace;
	int Model;
	uchar RecordTriggerZoneHits;
	uchar DropDown;
	ushort Inquiry;
	int tNear;
	uint tNumtrLo;
	int tNumtrHi;
	uint tDenomLo;
	int tDenomHi;
	uint NormalOffset;
};
struct CSpark {
	char pad0[0x24];
	CVector mVel;
	char pad1[0x58 - 0x30];
	int mFloorY;
};
extern "C" {
void *__nw__4CBitUi(unsigned int);
void *__6CSparkR7CVectoriii(void *, CVector &, int, int, int);
}
extern int DAT_800d171c;
extern int DAT_800d1868;
extern int DAT_800d186c;
extern int DAT_800d18b8;
void Video_BloodSplat(struct CBruce *, int, int);
void Bit_SetSparkTrajectory(const CSVector &);
void Bit_SetSparkTrajectoryCone(const CSVector &);
void Bit_SetSparkSize(uint);
void Bit_SetSparkRGB(uchar, uchar, uchar);
void Bit_SetSparkFadeRGB(uchar, uchar, uchar);
int Mem_GetFree(char);
void M3dColij_InitLineInfo(SLineInfo *);
int M3dZone_LineToItem(SLineInfo *, int);
struct CBruce {
	char pad0[0x6c];
	CVector mVel;
	void GetHookPosition(CVector &, uchar);
	void BloodSplat(int BodyPart, int MaxBloodBits);
};
void CBruce::BloodSplat(int BodyPart, int MaxBloodBits)
{
	if (DAT_800d171c) {
		Video_BloodSplat(this, BodyPart, MaxBloodBits);
		if (DAT_800d1868 < 200) {
			CSVector v;
			CVector Pos;
			CSVector Cone;
			int Bits;
			int FloorY;
			SLineInfo BloodLine;
			v.x = -1024;
			v.y = 0;
			v.z = 0;
			Bit_SetSparkTrajectory(v);
			if (BodyPart == 0) {
				Cone.x = 1200;
				Cone.y = 800;
				Cone.z = 0;
			} else if (BodyPart == 1) {
				Cone.x = 1600;
				Cone.y = 1600;
				Cone.z = 0;
			} else {
				Cone.x = 1200;
				Cone.y = 800;
				Cone.z = 0;
			}
			Bit_SetSparkTrajectoryCone(Cone);
			Bit_SetSparkRGB(72, 0, 0);
			Bit_SetSparkFadeRGB(0, 0, 0);
			GetHookPosition(Pos, BodyPart);
			DAT_800d18b8 = 0;
			DAT_800d186c = 0;
			Bits = 200 - DAT_800d1868;
			if (MaxBloodBits < Bits)
				Bits = MaxBloodBits;
			BloodLine.StartCoords.vx = Pos.x;
			BloodLine.StartCoords.vy = Pos.y - 163840;
			BloodLine.StartCoords.vz = Pos.z;
			BloodLine.EndCoords.vx = Pos.x;
			BloodLine.EndCoords.vy = Pos.y + 3276800;
			BloodLine.EndCoords.vz = Pos.z;
			M3dColij_InitLineInfo(&BloodLine);
			M3dZone_LineToItem(&BloodLine, 1);
			if (BloodLine.pItem) {
				FloorY = BloodLine.Position.vy - 16384;
			} else {
				FloorY = Pos.y - 16384;
			}
			Pos.y -= 122880;
			{
				int i;
				for (i = 0; i < Bits; i++) {
					CSpark *pSpark;
					if (Mem_GetFree(1) < 10000)
						return;
					Bit_SetSparkSize((i & 1) + 1);
					pSpark = (CSpark *)__nw__4CBitUi(92);
					if (pSpark)
						pSpark = (CSpark *)__6CSparkR7CVectoriii(pSpark, Pos, (i >> 2) + 14, 10240 + i * 256, (i & 7) + 50);
					pSpark->mVel += mVel;
					pSpark->mFloorY = FloorY;
				}
			}
			DAT_800d186c = 1;
			DAT_800d18b8 = 1;
		}
	}
}
