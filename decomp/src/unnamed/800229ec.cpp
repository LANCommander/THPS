/* FUN_800229ec (0x800229ec) */
/* C++ (GAMEFMV.CPP area, after the MDEC decoder). Looks up a texture by checksum and, unless
   DAT_800d1634 is set or DAT_800d16a4 == 7, clears its VRAM rectangle (the FMV frame
   size, DAT_800d1672 x DAT_800d1674) to grey, records its position, and hands the 16-bit tpage
   to FUN_800237b4. The arg is passed straight through in a0. */
extern "C" {
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
}
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

struct STexture {
	char pad0[0x1c];
	ushort x;
	ushort y;
};

int DAT_800d1634;
short DAT_800d1658;
short DAT_800d166e;
short DAT_800d1670;
ushort DAT_800d1672;
ushort DAT_800d1674;
uchar DAT_800d167c;
extern int DAT_800d16a4;

STexture *Spool_FindTextureEntry(uint Checksum);
void FUN_800237b4(short tpage, STexture *pTex);

void FUN_800229ec(uint Checksum)
{
	STexture *pTex;
	RECT r;

	DAT_800d1658 = -1;
	if (DAT_800d1634 == 0 && DAT_800d16a4 != 7)
	{
		pTex = Spool_FindTextureEntry(Checksum);
		if (pTex)
		{
			ushort x = pTex->x;
			ushort y = pTex->y;
			DAT_800d1658 = x;
			DAT_800d166e = y;
			r.x = x;
			r.w = DAT_800d1672;
			r.h = DAT_800d1674;
			r.y = y;
			ClearImage(&r, 8, 8, 8);
			DAT_800d1670 = DAT_800d1658 + (DAT_800d167c ? (DAT_800d1672 * 3) >> 1 : DAT_800d1672);
			FUN_800237b4(getTPage(2, 0, DAT_800d1658, DAT_800d166e), pTex);
		}
	}
}
