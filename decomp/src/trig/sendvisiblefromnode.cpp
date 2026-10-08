/* SendVisibleFromNode__Fii (0x80045838) */
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

struct Item {
	ushort mFlags;
};

struct CBit {
	char pad0[4];
	CBit *mNext;
	char pad1[2];
	ushort mNodeId;
	char pad2[0x43 - 0xc];
	uchar mType;
	char pad3[0x56 - 0x44];
	uchar mProtected;
};

struct CItemL {
	ushort mFlags;
	char pad[0x1a];
	CItemL *mNextItem;
};

extern int DAT_800d199c;
extern int DAT_800d1780;
extern int DAT_800d19a4;
extern CItemL *DAT_800d1618;
extern CBit *DAT_800d18cc;

short **DAT_800d19e8;

ushort *Trig_GetLinksPointer(int);
Item *Spool_FindEnviroItem(uint);

void SendVisibleFromNode(int node, int visible) {
	int SetFlags;
	int ClearFlags;
	ushort *pNodes;
	ushort NumLinks;

	if (!DAT_800d199c || DAT_800d1780 == 1)
		SetFlags = 65;
	else if (DAT_800d199c == DAT_800d19a4)
		SetFlags = 64;
	else
		SetFlags = 1;

	if (visible) {
		ClearFlags = ~SetFlags;
		SetFlags = 0;
	} else {
		ClearFlags = -1;
	}

	pNodes = Trig_GetLinksPointer(node);
	NumLinks = *pNodes++;

	{
		int i;

		for (i = 0; i < NumLinks; i++) {
			ushort VisNode = *pNodes++;
			short *pVisNode = DAT_800d19e8[VisNode];

			switch (*pVisNode) {
				case 5: {
					CItemL *pUp;

					for (pUp = DAT_800d1618; pUp; pUp = pUp->mNextItem) {
						if (*(ushort *)((char *)pUp + 0xe2) == VisNode) {
							pUp->mFlags = (pUp->mFlags & ClearFlags) | SetFlags;
							break;
						}
					}

					break;
				}
				case 501: {
					CBit *pBit;

					for (pBit = DAT_800d18cc; pBit; pBit = pBit->mNext) {
						if (pBit->mType == 2 && pBit->mNodeId == VisNode) {
							if (visible)
								pBit->mProtected = 1;
							else if (DAT_800d1780 == 1)
								pBit->mProtected = 0;

							break;
						}
					}

					break;
				}
				case 9:
				case 14:
				case 2:
				case 12: {
					Item *pItem;

					pVisNode++;
					pVisNode += *pVisNode + 1;

					if ((int)pVisNode & 2)
						pVisNode++;

					pItem = Spool_FindEnviroItem(*(uint *)pVisNode);

					if (pItem)
						pItem->mFlags = (pItem->mFlags & ClearFlags) | SetFlags;

					break;
				}
			}
		}
	}
}
