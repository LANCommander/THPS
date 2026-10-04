/* FUN_800144a8 (0x800144a8) */
/* C++ (CARD.CPP). Fuzzy demo twin Card_FileExists (0.69). Builds a one-block header for the save
   or replay file name, then opens the file for writing (mode 1) to create it. */
struct SCardHead {
	char Magic[2];
	char Type;
	char BlockEntry;
	char Title[64];
	char reserve[28];
	char Clut[32];
	char Icon[3][128];
};
extern char DAT_800a5848[];
extern char DAT_800a5864[];
extern int DAT_800d1148;
int SyncToGoodState(void);
void Card_SetHeader(SCardHead *, int, char *, char *);
void SetSJISChecksum(char *, char *);
extern "C" {
void FUN_800116b4(char *);
int open(char *, int);
int close(int);
}
int FUN_800144a8(int FileType)
{
	SCardHead Head;
	char *FName;
	int fd;
	if (FileType == 0)
		FName = DAT_800a5848;
	else
		FName = DAT_800a5864;
	Card_SetHeader(&Head, 1, (char *)&Head, (char *)&Head);
	if (DAT_800d1148 == 1)
		FUN_800116b4((char *)&Head + 32);
	else
		FUN_800116b4((char *)&Head + 30);
	SetSJISChecksum(Head.Title, FName + 22);
	if (SyncToGoodState() == 1)
		return 0;
	fd = open(FName, 1);
	if (fd == -1)
		return 0;
	close(fd);
	return 1;
}
