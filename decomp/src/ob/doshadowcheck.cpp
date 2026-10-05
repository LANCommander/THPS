/* DoShadowCheck__6CBruce (0x800427d4) flags=-fstructure-noalias */
extern "C" {
#include <sys/types.h>
#include <libgte.h>
}
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
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
struct SShadowRGB { uchar r, g, b; };
extern int DAT_800d1780;
void M3dColij_InitLineInfo(SLineInfo *);
int M3dZone_LineToItem(SLineInfo *, int);
struct CBruce {
	int vf;
	Vector mPos;
	char pad0[0xbc - 0x10];
	Vector mShadowPos;
	char pad1[0xc8 - 0xc8 + 0];
	short mShadowNormal[3];
	char pad2[0x15a - 0xce];
	uchar mShadowOn;
	char pad3[0x160 - 0x15b];
	SShadowRGB *mpShadow;
	char pad4[0x734 - 0x164];
	int mState;
	char pad5[0x7f0 - 0x738];
	Vector mUp;
	void FRUVectorsFromRotMatrix();
	void DoShadowCheck();
};
void CBruce::DoShadowCheck()
{
	SLineInfo line_info;
	FRUVectorsFromRotMatrix();
	if (DAT_800d1780 == 1) {
		line_info.StartCoords.vx = mPos.vx + mUp.vx * 50;
		line_info.StartCoords.vy = mPos.vy + mUp.vy * 50;
		line_info.StartCoords.vz = mPos.vz + mUp.vz * 50;
	} else {
		line_info.StartCoords.vx = mPos.vx;
		line_info.StartCoords.vy = mPos.vy;
		line_info.StartCoords.vz = mPos.vz;
	}
	line_info.EndCoords.vx = line_info.StartCoords.vx;
	line_info.EndCoords.vy = line_info.StartCoords.vy + 0xfa0000;
	line_info.EndCoords.vz = line_info.StartCoords.vz;
	M3dColij_InitLineInfo(&line_info);
	M3dZone_LineToItem(&line_info, 1);
	if (line_info.pItem && line_info.Normal.vy < -1900 && mState != 4 && mState != 8) {
		{
			int _x = line_info.Position.vx;
			int _y = line_info.Position.vy;
			int _z = line_info.Position.vz;
			mShadowPos.vx = _x;
			mShadowPos.vy = _y;
			mShadowPos.vz = _z;
		}
		{
			int _x = line_info.Normal.vx;
			int _z = line_info.Normal.vz;
			int _y = line_info.Normal.vy;
			mShadowNormal[0] = _x;
			mShadowNormal[1] = _y;
			mShadowNormal[2] = _z;
		}
		if (DAT_800d1780 == 1) {
			mShadowOn = 1;
			mpShadow->r = mpShadow->g = mpShadow->b = ((4300 - line_info.Distance) << 7) / 4000;
		}
	} else {
		mShadowOn = 0;
	}
}
