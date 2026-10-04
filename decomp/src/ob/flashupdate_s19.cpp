/* FlashUpdate__5CItem (0x80043728) */
typedef unsigned short ushort;
typedef unsigned int uint;
struct CItem {
	ushort mFlags;
	char pad0[0x1e];
	uint mRGB;
	char pad1[0x10];
	uint mStoredRGB;
	char pad2[0x08];
	ushort mFlashTimer;
	short mFlash_dR;
	short mFlash_dG;
	short mFlash_dB;
	void FlashUpdate();
};
void CItem::FlashUpdate()
{
	if (mFlashTimer) {
		int r, g, b;
		mFlashTimer--;
		r = (mRGB & 255);
		g = ((mRGB >> 8) & 255);
		b = ((mRGB >> 16) & 255);
		r += mFlash_dR;
		g += mFlash_dG;
		b += mFlash_dB;
		mRGB = ((b & 255) << 16) | ((g & 255) << 8) | (r & 255);
		mFlags |= 1024;
		if (mFlashTimer == 0) {
			if (mStoredRGB & 0x02000000)
				mFlags |= 1024;
			else
				mFlags &= ~1024;
			mRGB = mStoredRGB;
			mStoredRGB = 0;
		}
	}
}
