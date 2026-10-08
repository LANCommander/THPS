/* FUN_80014868 (0x80014868) */
/* C++ (CARD.CPP). Debug twin of Card_Write: writes the replay header/data buffers (and the 2-player
   pair) to the PC host through the Psy-Q PCinit/PCcreat/PClseek/PCwrite/PCclose break calls,
   with the same switch(FileType) setup and checksums as Card_Write (only case 1 survives). */
typedef unsigned long ulong;
enum EFileType { FILETYPE_A, FILETYPE_B, FILETYPE_C, FILETYPE_D };
struct SVideoHead;

struct SVideoInfo {
	int VideoMode;
	ulong *pBlockStart;
	char pad[0xc0 - 8];
};

extern SVideoInfo DAT_800bf318;
extern SVideoInfo DAT_800bf3d8;
extern char DAT_8009e00c[];
extern char DAT_8009e030[];
extern char DAT_8009e054[];
extern char DAT_8009e084[];

unsigned short CalcChecksum(ulong *, ulong);
void Video_SetHeader(SVideoHead *, int);

extern "C" {
	int PCinit(void);
	int PCcreat(char *, int);
	int PClseek(int, int, int);
	int printf(const char *, ...);
	int PCwrite(int, char *, int);
	int PCclose(int);
}

extern "C" int FUN_80014868(EFileType FileType, char *FName) {
	unsigned short fd;
	int DataSize;
	int DataSize2;
	int HeaderSize;
	ulong *pDataBuf;
	ulong *pDataBuf2;
	ulong *pHeaderBuf;
	ulong *pHeaderBuf2;

	switch (FileType) {
		case 1:
			pHeaderBuf = DAT_800bf318.pBlockStart;
			HeaderSize = 640;
			pDataBuf = pHeaderBuf + 160;
			DataSize = 23936;
			pHeaderBuf2 = DAT_800bf3d8.pBlockStart;
			pDataBuf2 = pHeaderBuf2 + 160;
			DataSize2 = 23936;
			break;
	}

	Video_SetHeader((SVideoHead *)(pHeaderBuf + 128), 0);
	if (pHeaderBuf2)
		Video_SetHeader((SVideoHead *)(pHeaderBuf2 + 128), 1);

	switch (FileType) {
		case 1:
			*(unsigned short *)((char *)pHeaderBuf + 566) = CalcChecksum(pDataBuf, DataSize);

			if (pHeaderBuf2)
				*(unsigned short *)((char *)pHeaderBuf2 + 566) = CalcChecksum(pDataBuf2, DataSize2);

			break;
	}

	PCinit();

	fd = PCcreat(FName, 0);

	PClseek(fd, 0, 0);
	printf(DAT_8009e00c, HeaderSize);
	PCwrite(fd, (char *)pHeaderBuf, HeaderSize);
	printf(DAT_8009e030, DataSize);
	PCwrite(fd, (char *)pDataBuf, DataSize);

	if (pHeaderBuf2) {
		printf(DAT_8009e054, 640);
		PCwrite(fd, (char *)pHeaderBuf2, 640);
		printf(DAT_8009e084, DataSize2);
		PCwrite(fd, (char *)pDataBuf2, DataSize2);
	}

	PCclose(fd);

	return 0;
}
