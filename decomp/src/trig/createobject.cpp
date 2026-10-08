/* Trig_CreateObject__Fi (0x80045268) */
/* C++ (TRIG.CPP). Fuzzy demo twin (0.71); locals from its MAIN.SYM. Creates the object for a
   trigger node: baddies (203), cars (213-216) and platforms (402) from type-1/7 nodes, powerups
   from type-5 nodes. Objects not active at start are suspended out of their list. */
#pragma interface

typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;

struct CVector {
	int vx, vy, vz;
};

class CBody {
  public:
	char pad0[0x52];
	ushort mCBodyFlags; /* 0x52 */
	char pad54[0xae - 0x54];
	ushort mSeed; /* 0xae */
	char padb0[0xe2 - 0xb0];
	ushort mNodeId; /* 0xe2 */
	void *operator new(uint) throw();
};

class CScriptOnlyBaddy : public CBody {
  public:
	char pade4[568 - 0xe4];
	CScriptOnlyBaddy(short *, int);
};

class CPlatform : public CBody {
  public:
	char pade4[600 - 0xe4];
	CPlatform(short *, int);
};

class CCar : public CBody {
  public:
	char pade4[548 - 0xe4];
	CCar(short *, int, int);
};

short **OffsetList;

extern CBody *BaddyList;
extern CBody *EnvironmentalObjectList;
extern CBody *PowerUpList;
extern CVector ZeroVector;

int GetFlag(uchar, uchar *);
uchar *SkipFlags(uchar *);
ushort *Trig_GetPosition(CVector &, int);
ushort *Trig_GetLinksPointer(int);
CBody *PowerUp_Create(ushort, const CVector &, uint, int, CVector &);

extern "C" {
	void FUN_8001ff34(CBody *, int);
	void Suspend__5CBodyPP5CBody(CBody *, CBody **);
}

CBody *Trig_CreateObject(int NodeIndex) {
	int Type;
	int NotSuspendedAtStart;
	int Seedable = 0xffff;
	int ManualSuspendControl = 0;
	int Inactive = 0;
	CBody *NewObject = 0;
	short *pInfo;
	int NodeType;

	pInfo = OffsetList[NodeIndex];
	NodeType = *pInfo++;

	switch (NodeType) {
		case 7:
			Inactive = 1;
		case 1:
			Type = *pInfo++;
			Seedable = (ushort)*pInfo++;
			pInfo += *pInfo + 1;
			NotSuspendedAtStart = GetFlag(2, (uchar *)pInfo);
			ManualSuspendControl = GetFlag(4, (uchar *)pInfo);
			pInfo = (short *)(((int)SkipFlags((uchar *)pInfo) + 3) & ~3);

			switch (Type) {
				case 203:
					NewObject = new CScriptOnlyBaddy(pInfo, NodeIndex);
					break;
				case 402:
					NewObject = new CPlatform(pInfo, NodeIndex);
					break;
				case 213:
				case 214:
				case 215:
				case 216:
					NewObject = new CCar(pInfo, NodeIndex, Type);
					break;
			}

			break;
		case 5: {
			CVector Pos;
			ushort *pStuff;

			Type = *pInfo;
			pStuff = Trig_GetPosition(Pos, NodeIndex);
			pStuff++;

			{
				int Flag = (*pStuff++ == 0) << 2;

				NewObject = PowerUp_Create(Type, Pos, Flag, *pStuff, ZeroVector);
			}

			if (*Trig_GetLinksPointer(NodeIndex))
				FUN_8001ff34(NewObject, NodeIndex);

			NotSuspendedAtStart = 1;
			break;
		}
	}

	if (NewObject) {
		NewObject->mNodeId = NodeIndex;
		NewObject->mSeed = Seedable;

		if (ManualSuspendControl)
			NewObject->mCBodyFlags &= ~2;

		if (Inactive)
			NewObject->mCBodyFlags |= 4;

		if (!NotSuspendedAtStart) {
			CBody **ppList = 0;

			if (NewObject == BaddyList)
				ppList = &BaddyList;

			if (NewObject == EnvironmentalObjectList)
				ppList = &EnvironmentalObjectList;

			if (NewObject == PowerUpList)
				ppList = &PowerUpList;

			Suspend__5CBodyPP5CBody(NewObject, ppList);
		}

		return NewObject;
	}

	return 0;
}
