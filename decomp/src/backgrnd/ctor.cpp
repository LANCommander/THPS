/* __11CBackgroundUiRC8CSVector (0x80078188) flags=-fstructure-noalias */
/* C++ (BACKGRND.CPP). Demo twin. A background object: a spinning CSuper with its model looked up by
   checksum, attached to the background list with a running id. */
#pragma interface
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;
struct CSVector { short vx, vy, vz; };
class CItem {
public:
	ushort mFlags;             /* 0x00 */
	char pad2[0x16 - 2];
	short mModel;              /* 0x16 */
	char pad18[0x1b - 0x18];
	uchar mRegion;             /* 0x1b */
	char pad1c[0x48 - 0x1c];
	virtual ~CItem();
	void InitItem(char *);
};
class CBody : public CItem {
public:
	char pad4c[0x52 - 0x4c];
	ushort mCBodyFlags;        /* 0x52 */
	char pad54[0x134 - 0x54];
	void AttachTo(CBody **);
};
class CSuper : public CBody {
public:
	CSuper(uint, const CSVector &);
};
class CBackground : public CSuper {
public:
	ushort mId;                /* 0x134 */
	CBackground(uint checksum, const CSVector &ang_vel);
};
extern char *DAT_800d19f0 __attribute__((section(".data")));
CBody *DAT_800d1fe4;
ushort DAT_800d1fe8;
int Spool_GetModel(uint, int);

CBackground::CBackground(uint checksum, const CSVector &ang_vel)
	: CSuper(checksum, ang_vel)
{
	InitItem(DAT_800d19f0);
	mModel = Spool_GetModel(checksum, mRegion);
	mFlags &= ~2;
	mCBodyFlags &= ~6;
	AttachTo(&DAT_800d1fe4);
	mId = DAT_800d1fe8++;
}
