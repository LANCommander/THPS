/* __8CTrickObUs (0x8004ef08) flags=-fstructure-noalias */
#pragma interface

class Item;

class CClass {
  public:
	CClass() {}
	virtual ~CClass();
};

class CTrickOb : public CClass {
  public:
	unsigned int mChecksum;
	unsigned short mNode;
	unsigned char mState;
	unsigned char mPlayer;
	unsigned short mScore;
	CTrickOb *mpNext;
	Item *mpItem;
	CTrickOb(unsigned short Node);
	virtual ~CTrickOb();
};

CTrickOb *DAT_800d1b70;

extern unsigned short **DAT_800d19e8;

CTrickOb::CTrickOb(unsigned short Node) {
	mpNext = DAT_800d1b70;
	DAT_800d1b70 = this;
	mpItem = 0;
	mNode = Node;
	mState = 0;

	{
		unsigned short *pNode = DAT_800d19e8[Node];

		pNode += pNode[1] + 2;

		if ((int)pNode & 3)
			pNode++;

		mChecksum = *(unsigned int *)pNode;
	}
}
