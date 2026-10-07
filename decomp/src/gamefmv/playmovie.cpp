/* GameFMV_PlayMovie__Fi (0x80022c1c) */
/* C++ (GAMEFMV.CPP). Fuzzy demo twin (0.98; retail drops the demo's ExitDemo path), locals from its
   MAIN.SYM. Plays the current FMV: allocates the bitstream ring and slice buffers, switches the
   display to the movie's size (24-bit for hi-colour movies), sets the CD volume, then decodes
   frame by frame until the stream ends, a button is pressed or the lid opens. Then it restores
   the display and frees everything. */
extern "C" {
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
}
typedef unsigned char uchar;
typedef unsigned short ushort;
struct CdlATV { uchar val0, val1, val2, val3; };
struct SButton {
	uchar Pressed;
	uchar Triggered;
	char pad[14];
};
struct SControl {
	SButton b[16];
	char pad[0x16c - 0x100];
};
struct SMovie {
	char pad0[24];
	char *pName;              /* 24 */
	char pad1c[32 - 28];
};
int DAT_800d162c;
int DAT_800d1630;
int DAT_800d1634;
int DAT_800d163c;
int DAT_800d1640;
int DAT_800d1644;
short DAT_800d1658;
int DAT_800d1664;
int DAT_800d1668;
uchar DAT_800d166c;
short DAT_800d166e;
short DAT_800d1670;
ushort DAT_800d1672;
ushort DAT_800d1674;
uchar DAT_800d167c;
uchar DAT_800d167d;
short DAT_800d1684;
short DAT_800d1686;
short DAT_800d1688;
short DAT_800d168a;
u_long *DAT_800d168c[2];
u_long *DAT_800d222c;
extern SMovie DAT_800a63e8[];
extern short DAT_800a8984[];
extern int DAT_800d13c8;
extern u_long *DAT_800a6748[];
extern SControl DAT_800c0a48[];
int strNextVlc(int);
void Front_ClearScreen(void);
void handleLidOpen(void);
void Pad_ClearTriggers(SControl *);
extern "C" {
void FUN_80023168(int); /* GameFMV_SetStartTrack */
void *FUN_8004d068(int, int, int);
void FUN_8004d5d0(void *);
void FUN_80022498(void);
DISPENV *FUN_800914fc(DISPENV *, int, int, int, int);
void FUN_8008eebc(int);
int FUN_8008ca0c(DISPENV *);
void FUN_8008f620(CdlATV *);
void FUN_80023cb8(void);
void FUN_80070ff4(void);
void FUN_800902c0(u_long *, int);
void FUN_8009033c(u_long *, int);
int FUN_8008f264(int, int, uchar *);
void FUN_8009035c(int);
void FUN_8009074c(void);
void FUN_8008f4d4(int, int, int);
}

void GameFMV_PlayMovie(int track)
{
	DISPENV disp;
	short old_screen_w;
	CdlATV atv;

	if (DAT_800d1634)
		return;
	DAT_800d162c = 1;
	FUN_80023168(track);
	DAT_800d1658 = (320 - DAT_800d1672) / 2;
	DAT_800d1670 = DAT_800d1658 + (DAT_800d167c ? (DAT_800d1672 * 3) / 2 : DAT_800d1672);
	DAT_800d166e = (240 - DAT_800d1674) / 2;
	DAT_800d1630 = 0;
	if (!DAT_800a63e8[DAT_800d167d].pName)
		return;
	DAT_800d1684 = DAT_800d1658;
	DAT_800d1686 = DAT_800d166e;
	DAT_800d168a = DAT_800d1674;
	DAT_800d1688 = DAT_800d167c ? 24 : 16;
	DAT_800d163c = 0;
	DAT_800d1640 = 0;
	DAT_800d1644 = 0;
	old_screen_w = DAT_800a8984[0];
	{
		int i;
		for (i = 0; i < 2; i++)
			if (!(DAT_800d168c[i] = (u_long *)FUN_8004d068(DAT_800d1664, 1, 0)))
				goto InsufficientMemory;
	}
	DAT_800d222c = (u_long *)FUN_8004d068(DAT_800d1668 << 11, 1, 0);
	if (!DAT_800d222c)
		goto InsufficientMemory;
	DAT_800d166c = 2;
	{
		int i;
		for (i = 0; i < DAT_800d166c; i++) {
			int h = DAT_800d1674;
			if (!(DAT_800a6748[i] = (u_long *)FUN_8004d068(DAT_800d167c ? h * 48 : h * 32, 1, 0)))
				goto InsufficientMemory;
		}
	}
	{
		FUN_80022498();
		DAT_800d1634 = 1;
		Front_ClearScreen();
		FUN_800914fc(&disp, 0, 256, 320, 240);
		FUN_8008eebc(0);
		FUN_8008ca0c(&disp);
		atv.val2 = 0;
		atv.val3 = 0;
		if (track == 3) {
			atv.val0 = 192;
			atv.val1 = 192;
		} else {
			int fmv_level;
			if (DAT_800d13c8 < 64)
				fmv_level = DAT_800d13c8 * 3;
			else
				fmv_level = (DAT_800d13c8 - 64) * 63 / 64 + 192;
			atv.val0 = fmv_level;
			atv.val1 = fmv_level;
		}
		FUN_8008f620(&atv);
	}
	FUN_80023cb8();
	FUN_80070ff4();
	DAT_800c0a48[0].b[14].Triggered = 0;
	DAT_800c0a48[0].b[3].Triggered = 0;
	while (!strNextVlc(1))
		;
	for (;;) {
		FUN_800902c0(DAT_800d168c[DAT_800d1640], DAT_800d167c ? 3 : 2);
		FUN_8009033c(DAT_800a6748[DAT_800d163c], DAT_800d1688 * DAT_800d168a / 2);
		{
			uchar result[8];
			int count;
			FUN_8008f264(1, 0, result);
			if (result[0] & 16) {
				handleLidOpen();
				break;
			}
			count = 0x800000;
			while (!strNextVlc(1)) {
				if (!count)
					goto end;
				count--;
			}
			if (!count)
				break;
			count = 0x800000;
			while (DAT_800d1684 != DAT_800d1658) {
				if (!count)
					goto end;
				count--;
			}
			if (!count)
				break;
		}
		FUN_800914fc(&disp, 0, (DAT_800d1686 < 256) << 8, DAT_800d167c ? 480 : 320, 240);
		if (DAT_800d167c) {
			disp.isrgb24 = 1;
			disp.disp.w = disp.disp.w * 2 / 3;
		}
		FUN_8008eebc(0);
		FUN_8008ca0c(&disp);
		if (DAT_800d1630)
			break;
		FUN_80070ff4();
		if (DAT_800c0a48[0].b[14].Triggered)
			break;
		if (DAT_800c0a48[0].b[3].Triggered)
			break;
	}
end:
	Pad_ClearTriggers(DAT_800c0a48);
	DAT_800d1634 = 0;
	Front_ClearScreen();
	disp.isrgb24 = 0;
	disp.disp.w = 512;
	disp.screen.w = old_screen_w;
	FUN_8008eebc(0);
	FUN_8008ca0c(&disp);
	atv.val0 = 0;
	atv.val1 = 0;
	atv.val2 = 0;
	atv.val3 = 0;
	FUN_8008f620(&atv);
	FUN_8009035c(0);
	FUN_8009074c();
	FUN_8008f4d4(9, 0, 0);
InsufficientMemory:
	if (DAT_800d222c) {
		FUN_8004d5d0(DAT_800d222c);
		DAT_800d222c = 0;
	}
	{
		int i;
		for (i = 0; i < 2; i++) {
			if (DAT_800d168c[i]) {
				FUN_8004d5d0(DAT_800d168c[i]);
				DAT_800d168c[i] = 0;
			}
		}
	}
	{
		int i;
		for (i = 0; i < DAT_800d166c; i++) {
			if (DAT_800a6748[i]) {
				FUN_8004d5d0(DAT_800a6748[i]);
				DAT_800a6748[i] = 0;
			}
		}
	}
}
