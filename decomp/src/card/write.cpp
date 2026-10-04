/* Card_Write__F9EFileTypei (0x80014558) */
typedef unsigned long ulong;
enum EFileType { FILETYPE_A, FILETYPE_B, FILETYPE_C, FILETYPE_D };
struct SCardHead;
struct SVideoHead;
extern char DAT_800a5848[];
extern char DAT_800a5864[];
struct SReplay {
	char pad[2094];
	unsigned short mTime;
	void SetTime(unsigned short t) { mTime = t; }
};
extern SReplay DAT_800a6844;
extern char DAT_8009e16c[];
extern char DAT_8009e18c[];
extern char DAT_8009e20c[];
extern char DAT_8009e22c[];
struct SVideoInfo {
	int VideoMode;
	ulong *pBlockStart;
	char pad[0xc0 - 8];
};
extern SVideoInfo DAT_800bf318;
extern SVideoInfo DAT_800bf3d8;
extern int DAT_800d1148;
int DAT_800d1380;
int DAT_800d1390;
unsigned short DAT_800d1398;
int SyncToGoodState(void);
void _clear_event(void);
unsigned short CalcChecksum(ulong *, ulong);
void Card_SetHeader(SCardHead *, int, char *, char *);
void SetSJISChecksum(char *, char *);
void Video_SetHeader(SVideoHead *, int);
int Card_CheckStatus(int, int);
void Pause(int);
extern "C" {
void FUN_8001571c(void);
void FUN_800116b4(char *);
int erase(char *);
int open(char *, int);
int write(int, void *, int);
int close(int);
}
int Card_Write(EFileType FileType, int NumBlocks)
{
	int fd;
	int i;
	int DataSize;
	int DataSize2;
	int HeaderSize;
	int HeaderSize2;
	ulong *pDataBuf;
	ulong *pDataBuf2;
	ulong *pHeaderBuf;
	ulong *pHeaderBuf2;
	char *pClut;
	char *pIcon;
	char *FName;
	if (SyncToGoodState() == 1)
		return 1;
	switch (FileType) {
	case 0:
		FUN_8001571c();
		DAT_800a6844.SetTime(DAT_800d1398);
		FName = DAT_800a5848;
		DataSize = 2560;
		pHeaderBuf = DAT_800bf318.pBlockStart;
		HeaderSize = 640;
		pDataBuf = (ulong *)&DAT_800a6844;
		pHeaderBuf2 = 0;
		HeaderSize2 = 0;
		pDataBuf2 = 0;
		DataSize2 = 0;
		pClut = DAT_8009e20c;
		pIcon = DAT_8009e22c;
		break;
	case 1:
		FName = DAT_800a5864;
		pHeaderBuf = DAT_800bf318.pBlockStart;
		HeaderSize = 640;
		pDataBuf = pHeaderBuf + 160;
		DataSize = 23936;
		pClut = DAT_8009e16c;
		pIcon = DAT_8009e18c;
		pHeaderBuf2 = DAT_800bf3d8.pBlockStart;
		HeaderSize2 = 640;
		pDataBuf2 = pHeaderBuf2 + 160;
		DataSize2 = 23936;
		break;
	case 2:
		break;
	}
	Video_SetHeader((SVideoHead *)(pHeaderBuf + 128), 0);
	if (pHeaderBuf2)
		Video_SetHeader((SVideoHead *)(pHeaderBuf2 + 128), 1);
	Card_SetHeader((SCardHead *)pHeaderBuf, NumBlocks, pClut, pIcon);
	if (DAT_800d1148 == 1)
		FUN_800116b4((char *)pHeaderBuf + 32);
	else
		FUN_800116b4((char *)pHeaderBuf + 30);
	SetSJISChecksum((char *)pHeaderBuf + 4, FName + 22);
	switch (FileType) {
	case 0:
		*(unsigned short *)((char *)pHeaderBuf + 566) = CalcChecksum(pDataBuf, DataSize);
		break;
	case 1:
		*(unsigned short *)((char *)pHeaderBuf + 566) = CalcChecksum(pDataBuf, DataSize);
		if (pHeaderBuf2)
			*(unsigned short *)((char *)pHeaderBuf2 + 566) = CalcChecksum(pDataBuf2, DataSize2);
		break;
	case 2:
		break;
	}
	for (i = 0; i < 16; i++) {
		if (DAT_800d1380 != 2 || DAT_800d1390 != 2) {
			if (FileType == 1)
				erase(FName);
			fd = open(FName, (NumBlocks << 16) | 512);
			if (fd != -1)
				close(fd);
			fd = open(FName, 2);
			if (fd != -1) {
				_clear_event();
				if (write(fd, pHeaderBuf, HeaderSize) != HeaderSize)
					return 1;
				if (write(fd, pDataBuf, DataSize) != DataSize)
					return 1;
				if (pHeaderBuf2) {
					if (write(fd, pHeaderBuf2, HeaderSize2) != HeaderSize2)
						return 1;
					if (write(fd, pDataBuf2, DataSize2) != DataSize2)
						return 1;
				}
				close(fd);
				return 0;
			}
		}
		Pause(1);
		Pause(1);
		Card_CheckStatus(0, 0);
	}
	return 1;
}
