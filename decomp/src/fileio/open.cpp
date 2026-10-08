/* FileIO_Open__FPCc (0x8004c8a4) */
/* C++ (FILEIO.CPP). Fuzzy demo twin (0.67); locals from its MAIN.SYM. Opens a file: from the
   loaded PRE archive if there is one, else by a case-insensitive search of the CD directory
   table. Each entry is {name, pad to 4, sector, size}; an end-of-block marker byte of 255 flashes
   the screen. Sets up the sector count and returns the size rounded to whole sectors.
   153/155 (S29). Two levers moved it from 149:
   - An unsized `extern uchar DAT_800c0a98[]` gives retail's split `lui v0` / `lbu a0`.
   - Reusing `len` for the byte count (`len = sectors << 11`). That makes the sll's dest
     set twice, which defeats sched1's set-once boost (birthing_insn_p).
   Residue: retail's sll result is in a1, separate from len (v0, as the demo SYM says),
   and lives across the lbu. Ours shares v0 with len and stores 224c early. A separate
   variable set once gets the boost and loses the order (141-149); one also set in the
   early PRE return gets a1 but costs a copy there (152). The tail statement order was
   searched exhaustively. */
#pragma interface
extern "C" {
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
}
typedef unsigned char uchar;
class PREManager {
public:
	char *getFile(char *, int *);
};
int DAT_800d1af8;
int DAT_800d1b04;
PREManager *DAT_800d1b10;
int DAT_800d1b14;
char *DAT_800d1b18;
int DAT_800d1b1c;
const char *DAT_800d1b30;
int DAT_800d224c;
int DAT_800d2264;
int DAT_800d2268;
extern RECT DAT_800d1b20[];
extern char DAT_800d1b28[];
extern uchar DAT_800c0a98[];
extern uchar DAT_800ba09c[];
extern char DAT_800a12bc[];
extern "C" {
void FUN_80047774(const char *, int, char *);
int FUN_8008c5ec(RECT *, int, int, int);
void FUN_8008c190(void *);
}

int FileIO_Open(const char *filename)
{
	char *header;
	char *scan;
	int len;

	DAT_800d1af8 = 0;
	FUN_80047774(filename, 299, DAT_800a12bc);
	DAT_800d1b14 = 0;
	if (DAT_800d1b10) {
		DAT_800d1b18 = DAT_800d1b10->getFile((char *)filename, &DAT_800d1b1c);
		if (DAT_800d1b18) {
			DAT_800d1b14 = 1;
			DAT_800d1b04 = 1;
			return DAT_800d1b1c;
		}
	}
	FUN_80047774(filename, 323, DAT_800a12bc);
	header = (char *)DAT_800ba09c;
	DAT_800d1b30 = filename;
	scan = (char *)filename;
	while (*scan) {
		char letter = *scan++;
		char checkletter = *header++;
		if (letter >= 'A' && letter <= 'Z')
			letter += 32;
		if (checkletter >= 'A' && checkletter <= 'Z')
			checkletter += 32;
		if (checkletter != letter) {
			scan = (char *)filename;
			while (*header++)
				;
			header = (char *)(((int)header + 3) & ~3) + 8;
			if (*header == 255) {
				RECT rect = DAT_800d1b20[0];
				FUN_8008c5ec(&rect, 0, 0, 255);
				rect.y += 256;
				FUN_8008c5ec(&rect, 0, 0, 255);
			}
		} else if (!*scan) {
			if (*header) {
				scan = (char *)filename;
				header++;
				while (*header++)
					;
				header = (char *)(((int)header + 3) & ~3) + 8;
				if (*header == 255) {
					RECT rect = DAT_800d1b20[0];
					FUN_8008c5ec(&rect, 0, 0, 255);
					rect.y += 256;
					FUN_8008c5ec(&rect, 0, 0, 255);
				}
			}
		}
	}
	header = (char *)(((int)header + 4) & ~3);
	DAT_800d2268 = ((int *)header)[0];
	len = ((int *)header)[1];
	{
		int sectors = (len + 2047) / 2048;
		DAT_800d2264 = sectors;
		len = sectors << 11;
		DAT_800d224c = len;
	}
	DAT_800d1b04 = 1;
	if (DAT_800c0a98[0])
		FUN_8008c190(DAT_800d1b28);
	FUN_80047774(filename, 495, DAT_800a12bc);
	return DAT_800d224c;
}
