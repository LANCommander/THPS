/* TrickOb_Update__Fv (0x8004f374) */
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

struct Item {
	ushort mFlags;
	char pad[0x1e];
	uint mRGB;
};

struct CTrickOb {
	int vf;
	uint mChecksum;
	ushort mNode;
	uchar mState;
	uchar mPlayer;
	ushort mScore;
	CTrickOb *mpNext;
	Item *mpItem;
};

CTrickOb *DAT_800d1b70;

extern const int DAT_800d16a4;
extern uint DAT_800d1a24;

void TrickOb_Update(void) {
	CTrickOb *pTrickOb;

	for (pTrickOb = DAT_800d1b70; pTrickOb; pTrickOb = pTrickOb->mpNext) {
		if (pTrickOb->mState) {
			Item *pItem = pTrickOb->mpItem;

			if (pItem) {
				if (DAT_800d16a4 == 8) {
					int Red;
					uint t = DAT_800d1a24 << 2;

					if (pTrickOb->mScore <= 2000)
						Red = t % ((((pTrickOb->mScore << 6) / 2000) + 1) * 2);
					else
						Red = t % 130;

					if (pTrickOb->mScore <= 2000) {
						if ((((pTrickOb->mScore << 6) / 2000) + 1) < Red)
							goto flip;
					} else {
						if (Red >= 66) {
						flip:
							if (pTrickOb->mScore <= 2000)
								Red = ((((pTrickOb->mScore << 6) / 2000) + 1) * 2) - Red;
							else
								Red = 130 - Red;
						}
					}

					if (pTrickOb->mPlayer == 1)
						pItem->mRGB = (pItem->mRGB & 0xff00ffff) | ((Red + 64) << 16);
					else
						pItem->mRGB = (pItem->mRGB & 0xffffff00) | (Red + 64);
				} else {
					int Red = (DAT_800d1a24 >> 1) & 63;

					if (Red > 32)
						Red = 64 - Red;

					pItem->mRGB = (pItem->mRGB & 0xffffff00) | (Red + 32);
				}
			}
		}
	}
}
