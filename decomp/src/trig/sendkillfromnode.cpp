/* SendKillFromNode__Fii (0x80045a90) */
/* C++ (TRIG.CPP). Fuzzy demo twin (0.73); locals from its MAIN.SYM. Sends a kill to every node
   linked from Node: platforms bounce the skater and pulse their own links, environment items are
   hit (How 1) or flagged, bits are killed. Anything else goes to the body lists by node id. */
#pragma interface

typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;

struct CVector {
	int vx, vy, vz;
};

struct Item {
	ushort Flags;
};

class CBruce {
  public:
	char pad0[0x6c];
	CVector m6C; /* 0x6c */
};

class CBody {
  public:
	ushort mFlags; /* 0x00 */
	char pad2[0x1c - 2];
	CBody *mNextItem; /* 0x1c */
	char pad20[0xe2 - 0x20];
	ushort mNodeId; /* 0xe2 */
	char pade4[0x1a1 - 0xe4];
	uchar m1A1; /* 0x1a1 */
	char pad1a2[0x1ac - 0x1a2];
	uint m1AC; /* 0x1ac */
};

class CPlatform : public CBody {
  public:
	void Bounce(CBruce *, const CVector &);
};

class CBit {
  public:
	char pad0[4];
	CBit *pNext; /* 0x04 */
	char pad8[2];
	ushort Node; /* 0x0a */
	char padc[0x43 - 0xc];
	uchar Type; /* 0x43 */
};

short **DAT_800d19e8;

extern CBody *DAT_800d19b0;
extern CBody *DAT_800d1998;
extern CBruce *DAT_800d199c;
extern CBit *DAT_800d18cc;

ushort *Trig_GetLinksPointer(int);
void Trig_SendPulse(ushort *);
Item *Spool_FindEnviroItem(uint);
void Exp_HitEnvItem(Item *, uint *, int);

extern "C" {
	void FUN_80045774(int, CBody *, int);
	void FUN_80027e18(CBit *);
}

void SendKillFromNode(int Node, int How) {
	ushort *pNodes;
	ushort NumLinks;
	int Bounced;
	int i;

	pNodes = Trig_GetLinksPointer(Node);
	NumLinks = *pNodes++;

	for (i = 0; i < NumLinks; i++) {
		ushort KillNode = *pNodes++;
		short *pKillNode = DAT_800d19e8[KillNode];
		CBody *pList;

		Bounced = 0;

		switch (*pKillNode) {
			case 1:
				for (pList = DAT_800d19b0; pList; pList = pList->mNextItem) {
					if (pList->mNodeId == KillNode && (pList->mFlags & 0x100) &&
					    (pList->m1AC & 0x10)) {
						pList->mFlags |= 0x20;

						if (!(pList->m1AC & 0x20)) {
							Trig_SendPulse(Trig_GetLinksPointer(pList->mNodeId));

							pList->m1A1 = 1;
							((CPlatform *)pList)->Bounce(DAT_800d199c, DAT_800d199c->m6C);
							Bounced = 1;
						}
					}
				}

				if (!Bounced) {
					FUN_80045774(KillNode, DAT_800d1998, How);
					FUN_80045774(KillNode, DAT_800d19b0, How);
				}

				break;
			case 2:
			case 9: {
				Item *pItem;

				pKillNode++;
				pKillNode += *pKillNode + 1;

				if ((int)pKillNode & 2)
					pKillNode++;

				pItem = Spool_FindEnviroItem(*(uint *)pKillNode);

				if (!pItem)
					break;

				if (How == 1)
					Exp_HitEnvItem(pItem, 0, 0xffff);
				else
					pItem->Flags |= 0x41;

				break;
			}
			case 10:
			case 11:
			case 12:
				break;
			/* 13 and 14 are separate compare-tree nodes in retail, so their bodies weren't plain
		   breaks; whatever they did folded away */
			case 13:
				Bounced = 0;
				break;
			case 14:
				Bounced = 0;
				break;
			case 500:
			case 501: {
				CBit *pBit;

				for (pBit = DAT_800d18cc; pBit; pBit = pBit->pNext) {
					if (pBit->Type == 2 && pBit->Node == KillNode) {
						FUN_80027e18(pBit);
						break;
					}
				}

				break;
			}
		}
	}
}
