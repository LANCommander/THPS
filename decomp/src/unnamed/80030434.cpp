/* TrickObRail__6CBruce (0x80030434) */
/* THPS1 fills in the demo's empty TrickObRail: when the rail start node (type 11) links to a trick
   object node (type 14 or 12), look up its enviro item by checksum and remember it with a heap ref.
   Lever: the second link test uses its own pointer local (reusing pLink changes the branch layout). */
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;
struct Item {
	char pad0[0x1b];
	uchar Region;              /* 0x01b */
};
struct SPSXRegion {
	char pad0[0x14];
	void *pData;               /* 0x14 */
	char pad18[64 - 0x18];
};
struct SMemRef {
	void *p;
	int Word0;
};
extern SPSXRegion DAT_800bf7a8[];
extern short **DAT_800d19e8;
extern int DAT_800d16a4;
class CBruce;
ushort *Trig_GetLinksPointer(int);
Item *Spool_FindEnviroItem(uint);
extern "C" {
void FUN_8003036c(CBruce *);
SMemRef FUN_8004d7ac(void *);
void FUN_8004f000(Item *, CBruce *, int);
}
class CBruce {
public:
	char pad0[0x418];
	Item *m418;               /* 0x418 */
	SMemRef m41C;             /* 0x41c */
	char pad424[0x6e8 - 0x424];
	int mRailStart;           /* 0x6e8 */
	void TrickObRail();
};

void CBruce::TrickObRail()
{
	short *pNode;
	if (*DAT_800d19e8[mRailStart] == 11) {
		ushort *pLinks = Trig_GetLinksPointer(mRailStart);
		short *pLink = DAT_800d19e8[pLinks[1]];
		if (*pLink == 14 || *pLink == 12)
			pNode = pLink;
		else {
			short *pLink2 = DAT_800d19e8[pLinks[2]];
			if (*pLink2 == 14 || *pLink2 == 12)
				pNode = pLink2;
		}
		pNode += (ushort)pNode[1] + 2;
		if ((int)pNode & 3)
			pNode++;
		uint Checksum = *(uint *)pNode;
		FUN_8003036c(this);
		m418 = Spool_FindEnviroItem(Checksum);
		m41C = FUN_8004d7ac(DAT_800bf7a8[m418->Region].pData);
		if (DAT_800d16a4 == 1)
			FUN_8004f000(m418, this, -1);
	}
}
