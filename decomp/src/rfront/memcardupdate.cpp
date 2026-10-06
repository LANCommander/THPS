/* Front_MemCardUpdate__Fv (0x800127c4) */
/* C++ (RFRONT.CPP), from the demo twin + its MAIN.SYM locals (Activated, GoBack, AnyButton, Start;
   block locals UpDown, FileType, WriteError, save_name, WantedFileType/Vids/m/CardHead/p, pTmp).
   The memory-card front-end state machine; returns the next front-end screen (18 = stay).
   Levers: case bodies of the CardStatus sub-switches in demo source order (case 1 first); the
   string table pointers are fields of the front-end string struct DAT_800a5d5c (lui of the struct
   first); the SaveFile/LoadFile name copy is an if/else of two calls; `if (!WriteError)` first; the
   video-header copy in case 1 reads NumFrames/Highlights through VH; "demoX.rec" is a 10-byte
   word-aligned block copy (strcpy of a literal), done as memcpy from the aligned extern. */
typedef unsigned long ulong;
enum EFileType { FILETYPE_A, FILETYPE_B, FILETYPE_C, FILETYPE_D };
struct SButton {
	unsigned char Pressed;
	unsigned char Triggered;
	int PressedTime;
	int ReleasedTime;
	int TriggeredTime;
};
struct SControl {
	SButton Triangle, Square, Circle, X;
	SButton LeftOne, LeftTwo, RightOne, RightTwo;
	SButton Left, Right, Up, Down;
	char pad[0x16c - 0xc0];
};
struct SCardHead {
	char Magic[2];
	char Type;
	char BlockEntry;
	unsigned char Title[64];
	char reserve[28];
	char Clut[32];
	char Icon[3][128];
};
struct SHighlight { int a, b; };
struct SVideoHead {
	ulong NumFrames;
	SHighlight Highlights[5];
	short NumSkaters;
	short Skater;
	short Skater2;
	short Level;
	short GGame;
	short Checksum;
	char VideoFlags;
	char Padding[7];
};
struct SVideoInfo {
	int VideoMode;
	ulong *pBlockStart;
	ulong *pStreamStart;
	ulong *pStreamEnd;
	ulong *pStream;
	ulong Bits;
	int BitsLeft;
	ulong NumFrames;
	char pad20[0x50 - 0x20];
	SHighlight Highlights[5];
	char pad78[0xc0 - 0x78];
};
struct SVideoSettings { int NumSkaters, Skater, Skater2, Level, GGame; };
struct SFrontStrings { char pad0[0x1b4]; char *f1b4; char *f1b8; };
struct SReplay { int d[2512 / 4]; };
class CMenu {
public:
	void Update();
	int ChoiceIs(const char *);
	int FindEntry(const char *);
	void SetLine(unsigned char);
	void CentreY();
};
class VerticalMenu {
public:
	int getSelected();
	void up();
	void down();
};
extern "C" {
extern int DAT_800d16e4;
extern int DAT_800d1380;
extern CMenu *DAT_800d1428;
extern int DAT_800d1780;
extern int DAT_800d13e4;
extern int DAT_800d1a34;
extern SControl DAT_800c0a48[2];
extern SVideoInfo DAT_800bf318;
extern SVideoSettings DAT_800a42f4;
extern SReplay DAT_800a6844;
extern unsigned char DAT_800a42d0[];
extern char DAT_800a42dc[];
extern char DAT_800a42e8[];
extern char DAT_800a4308[];
extern char DAT_800a4314[][11];
extern char *DAT_800a43bc[];
extern int DAT_800a43f8[];
extern int DAT_800a5880[];
extern char DAT_800a58bc[][40];
extern SFrontStrings DAT_800a5d5c;
extern char DAT_8009d154[] __attribute__((aligned(4)));
extern char DAT_8009d160[];
void *memcpy(void *, const void *, unsigned int);
void FUN_800117b4(void);
int FUN_80012600(void);
void FUN_80012650(void);
int FUN_800144a8(int);
int FUN_80014558(int, int);
int FUN_80014868(int, char *);
int FUN_8004b250(unsigned int, short, int);
void *FUN_8004d068(unsigned int, int, int);
void FUN_8004d5d0(void *);
int FUN_8008c190(char *, ...);
char *FUN_8008e904(char *, char *);
}
VerticalMenu *DAT_800d1104;
int DAT_800d10f0, DAT_800d10f4, DAT_800d10f8, DAT_800d10fc, DAT_800d1100;
int DAT_800d1108, DAT_800d110c, DAT_800d1110, DAT_800d111c, DAT_800d1124;
int DAT_800d1144, DAT_800d1148;
int DAT_800d21c8, DAT_800d21cc, DAT_800d21d8, DAT_800d21dc, DAT_800d21e0;
int Card_CheckStatus(int, int);
int Card_GetDirAndFreeBlocks(int, int);
int Card_FormatCard(int, int);
int Card_ReadFileHeader(char *, SCardHead *);
void Card_SetSelectedFile(char *);
int Card_Load(EFileType, ulong *, ulong *);
void Front_ExtractASCIINameFromSJIS(char *, char *);
void Front_GetButtons(int &, int &, int &, int &);
int GetUpDown();
int SaveReturnState();
int Front_MemCardUpdate()
{
	int Activated;
	int GoBack;
	int AnyButton;
	int Start;
	if (++DAT_800d16e4 & 1) Card_CheckStatus(0, 0);
	Front_GetButtons(Activated, GoBack, AnyButton, Start);
	switch (DAT_800d111c) {
	case 0:
		if (DAT_800d1124) {
			if (--DAT_800d1124 == 0) DAT_800d111c = 1;
		} else {
			DAT_800d1124 = 10;
		}
		break;
	case 1:
		if (DAT_800d10f0) {
			DAT_800d111c = 2;
			break;
		}
		switch (DAT_800d1380) {
		case 1:
			DAT_800d21dc = Card_GetDirAndFreeBlocks(0, 0);
			if (DAT_800d1148 == 1) {
				DAT_800d21d8 = 1;
				if (DAT_800d21dc < 1 && !DAT_800d10f4) {
					DAT_800d111c = 8;
					break;
				}
				if (DAT_800d10f4) {
					{
						int i;
						for (i = 0; i < 10; i++) DAT_800a42d0[i] = DAT_800a4308[i];
					}
					DAT_800d111c = 4;
					DAT_800d21c8 = 4;
					DAT_800d21cc = 4;
				} else {
					DAT_800d111c = 2;
					FUN_800117b4();
				}
			} else {
				DAT_800d21d8 = 3;
				if (DAT_800d1780 == 2) DAT_800d21d8 = 6;
				if (DAT_800d21dc < DAT_800d21d8) {
					DAT_800d111c = 8;
				} else {
					DAT_800d111c = 2;
					FUN_800117b4();
				}
			}
			break;
		case -1:
			DAT_800d111c = 9;
			break;
		case -2:
			DAT_800d111c = 10;
			DAT_800d1428->SetLine(DAT_800d1428->FindEntry(DAT_800a5d5c.f1b8));
			break;
		}
		break;
	case 8:
		switch (DAT_800d1380) {
		case -1:
			DAT_800d111c = 9;
			break;
		case -2:
		case 2:
			DAT_800d111c = 0;
			break;
		}
		if (AnyButton) {
			FUN_8004b250(2, 0x2000, 0);
			return SaveReturnState();
		}
		break;
	case 2:
		{
			int UpDown = GetUpDown();
			if (UpDown == -1) {
				DAT_800d1100 = 16;
				FUN_8004b250(17, 0x2000, 0);
				if (DAT_800a42d0[DAT_800d10fc] == ' ' || DAT_800a42d0[DAT_800d10fc] == 0) {
					DAT_800a42d0[DAT_800d10fc] = 'A';
				} else {
					DAT_800a42d0[DAT_800d10fc]++;
					if (DAT_800a42d0[DAT_800d10fc] >= 91) DAT_800a42d0[DAT_800d10fc] = ' ';
				}
			}
			if (UpDown == 1) {
				DAT_800d1100 = 16;
				FUN_8004b250(17, 0x2000, 0);
				if (DAT_800a42d0[DAT_800d10fc] == ' ' || DAT_800a42d0[DAT_800d10fc] == 0) {
					DAT_800a42d0[DAT_800d10fc] = 'Z';
				} else {
					DAT_800a42d0[DAT_800d10fc]--;
					if (DAT_800a42d0[DAT_800d10fc] < 65) DAT_800a42d0[DAT_800d10fc] = ' ';
				}
			}
			if (DAT_800c0a48[0].Left.Triggered || DAT_800c0a48[1].Left.Triggered) {
				DAT_800d1100 = 16;
				FUN_8004b250(5, 0x2000, 0);
				DAT_800c0a48[0].Left.Triggered = 0;
				DAT_800c0a48[1].Left.Triggered = 0;
				DAT_800d10fc--;
				if (DAT_800d10fc < 0) DAT_800d10fc = 9;
			}
			if (DAT_800c0a48[0].Right.Triggered || DAT_800c0a48[1].Right.Triggered) {
				DAT_800d1100 = 16;
				FUN_8004b250(5, 0x2000, 0);
				DAT_800c0a48[0].Right.Triggered = 0;
				DAT_800c0a48[1].Right.Triggered = 0;
				DAT_800d10fc++;
				if (DAT_800d10fc >= 10) DAT_800d10fc = 0;
			}
			if (DAT_800d1148 == 0) FUN_8008e904(DAT_800a42e8, (char *)DAT_800a42d0);
			else FUN_8008e904(DAT_800a42dc, (char *)DAT_800a42d0);
			if (GoBack) {
				FUN_8004b250(2, 0x2000, 0);
				return SaveReturnState();
			}
			if (DAT_800d1380 == -1 && !DAT_800d10f0) DAT_800d111c = 9;
			if (Activated && !DAT_800d10f0) {
				FUN_8004b250(5, 0x2000, 0);
				{
					int FileType = DAT_800d1148 == 0;
					if (FUN_80012600()) {
						do FUN_80012650();
						while (FUN_800144a8(FileType));
					}
					if (FUN_800144a8(FileType) && !(DAT_800d1148 == 1 && DAT_800d10f4)) {
						DAT_800d111c = 3;
						DAT_800d1428->SetLine(DAT_800d1428->FindEntry(DAT_800a5d5c.f1b8));
						DAT_800d1428->CentreY();
					} else {
						DAT_800d111c = 4;
						DAT_800d21c8 = 4;
						DAT_800d21cc = 4;
					}
				}
			}
			if (Activated && DAT_800d10f0) {
				FUN_8004b250(5, 0x2000, 0);
				DAT_800d111c = 5;
			}
		}
		break;
	case 3:
		DAT_800d1428->Update();
		if (Activated) {
			if (DAT_800d1428->ChoiceIs(DAT_800a5d5c.f1b4)) {
				FUN_8004b250(5, 0x2000, 0);
				DAT_800d111c = 4;
				DAT_800d21c8 = 4;
				DAT_800d21cc = 4;
			} else {
				FUN_8004b250(2, 0x2000, 0);
				DAT_800d111c = 2;
				FUN_800117b4();
			}
		}
		if (GoBack) {
			FUN_8004b250(2, 0x2000, 0);
			DAT_800d111c = 2;
			FUN_800117b4();
		}
		break;
	case 9:
		switch (DAT_800d1380) {
		case -2:
		case 1:
		case 2:
			DAT_800d111c = 0;
			break;
		}
		if (AnyButton) {
			FUN_8004b250(2, 0x2000, 0);
			return SaveReturnState();
		}
		break;
	case 18:
		if (DAT_800d1380 == -1) DAT_800d111c = 17;
		if (AnyButton) {
			FUN_8004b250(GoBack ? 147 : 145, 0x2000, 0);
			return SaveReturnState();
		}
		break;
	case 10:
		DAT_800d1428->Update();
		switch (DAT_800d1380) {
		case 1:
		case 2:
			DAT_800d111c = 0;
			break;
		case -1:
			DAT_800d111c = 9;
			break;
		}
		if (Activated) {
			if (DAT_800d1428->ChoiceIs(DAT_800a5d5c.f1b4)) {
				FUN_8004b250(5, 0x2000, 0);
				DAT_800d111c = 11;
				DAT_800d21c8 = 4;
				DAT_800d21cc = 4;
			} else {
				FUN_8004b250(5, 0x2000, 0);
				return SaveReturnState();
			}
		}
		if (GoBack) {
			FUN_8004b250(2, 0x2000, 0);
			DAT_800d111c = 0;
		}
		break;
	case 11:
		DAT_800d13e4 = 0;
		if (DAT_800d1380 == 2 || DAT_800d1380 == -1) {
			DAT_800d111c = 12;
			DAT_800d21c8 = 75;
			break;
		}
		if (--DAT_800d21c8 < 0 && DAT_800d1380) {
			if (Card_FormatCard(0, 0) == 1) {
				DAT_800d111c = 13;
				DAT_800d21c8 = 75;
			} else if (--DAT_800d21cc < 0) {
				DAT_800d111c = 12;
				DAT_800d21c8 = 75;
			} else {
				DAT_800d21c8 = (4 - DAT_800d21cc) * 60;
			}
		}
		break;
	case 6:
	case 7:
		if (Activated) {
			FUN_8004b250(5, 0x2000, 0);
			return SaveReturnState();
		}
		break;
	case 12:
	case 13:
		if (--DAT_800d21c8 < 0) {
			if (DAT_800d1380 == -1) DAT_800d111c = 9;
			else DAT_800d111c = 0;
		}
		if (AnyButton) {
			FUN_8004b250(GoBack ? 2 : 5, 0x2000, 0);
			DAT_800d111c = 0;
		}
		break;
	case 4:
		DAT_800d13e4 = 0;
		if (DAT_800d1380 == -1) {
			DAT_800d111c = 6;
			DAT_800d21c8 = 75;
		}
		if (--DAT_800d21c8 < 0 && DAT_800d1380) {
			int WriteError;
			switch (DAT_800d1148) {
			case 0:
				DAT_800d21d8 = 3;
				if (DAT_800d1780 == 2) DAT_800d21d8 = 6;
				WriteError = FUN_80014558(1, DAT_800d21d8);
				break;
			case 1:
				DAT_800d21d8 = 1;
				WriteError = FUN_80014558(0, DAT_800d21d8);
				break;
			}
			if (!WriteError) {
				DAT_800d111c = 7;
				if (DAT_800d1148 == 1) {
					DAT_800d10f4 = 1;
					DAT_800d10f8 = 1;
					{
						int i;
						for (i = 0; i < 10; i++) DAT_800a4308[i] = DAT_800a42d0[i];
					}
				}
			} else {
				DAT_800d111c = 6;
				DAT_800d21c8 = 75;
			}
		}
		break;
	case 5:
		DAT_800d13e4 = 0;
		if (DAT_800a42d0[0] < 'A' || DAT_800a42d0[0] > 'Z') DAT_800a42d0[0] = 'A';
		if (DAT_800a42d0[0] >= 'K') {
			DAT_800d111c = 2;
			Activated = 0;
			GoBack = 0;
			break;
		}
		{
			char save_name[16];
			memcpy(save_name, DAT_8009d154, 10);
			save_name[4] = DAT_800a42d0[0];
			FUN_8008c190(DAT_8009d160, save_name);
			FUN_80014868(1, save_name);
			DAT_800d111c = 7;
		}
		break;
	case 14:
		if (AnyButton) FUN_8004b250(5, 0x2000, 0);
		break;
	case 15:
		if (DAT_800d1124) {
			if (--DAT_800d1124 == 0) DAT_800d111c = 16;
		} else {
			DAT_800d1124 = 10;
		}
		break;
	case 16:
		switch (DAT_800d1380) {
		case 1:
			{
				int WantedFileType;
				int Vids;
				int Offset;
				DAT_800d21dc = Card_GetDirAndFreeBlocks(0, 0);
				WantedFileType = 1;
				Offset = 26;
				if (DAT_800d1144 == 2) {
					WantedFileType = 0;
					Offset = 28;
				}
				Vids = 0;
				{
					int i;
					for (i = 0; i < 15; i++) Vids += DAT_800a5880[i] == WantedFileType;
				}
				if (Vids) {
					int m = 0;
					{
						int i;
						for (i = 0; i < 15; i++) {
							if (DAT_800a5880[i] == WantedFileType) {
								SCardHead CardHead;
								char *p;
								Card_ReadFileHeader(DAT_800a58bc[i], &CardHead);
								p = DAT_800a4314[m];
								{
									int j;
									for (j = 0; j < 10; j++) {
										if (!CardHead.Title[Offset + j * 2]) {
											*p++ = 0;
											break;
										}
										if (CardHead.Title[Offset + j * 2] == 0x82)
											*p++ = CardHead.Title[Offset + j * 2 + 1] - 31;
										else
											*p++ = ' ';
									}
								}
								*p = 0;
								DAT_800a43bc[m] = DAT_800a4314[m];
								DAT_800a43f8[m] = i;
								m++;
							}
						}
					}
					DAT_800d1108 = m;
					DAT_800d110c = 0;
					DAT_800d111c = 20;
				} else {
					DAT_800d111c = 19;
				}
			}
			break;
		case -1:
			DAT_800d111c = 17;
			break;
		case -2:
			DAT_800d111c = 18;
			break;
		}
		break;
	case 17:
		switch (DAT_800d1380) {
		case -2:
		case 1:
		case 2:
			DAT_800d111c = 15;
			break;
		}
	case 19:
		if (AnyButton) {
			FUN_8004b250(GoBack ? 147 : 145, 0x2000, 0);
			return SaveReturnState();
		}
		break;
	case 20:
		DAT_800d1110 = 0;
		if (DAT_800c0a48[0].Up.Triggered || DAT_800c0a48[1].Up.Triggered) {
			DAT_800c0a48[0].Up.Triggered = 0;
			DAT_800c0a48[1].Up.Triggered = 0;
			if (DAT_800d1104->getSelected() > 0) {
				DAT_800d1104->up();
			} else if (DAT_800d110c > 0) {
				DAT_800d110c--;
				DAT_800d1110 = 1;
			}
		}
		if (DAT_800c0a48[0].Down.Triggered || DAT_800c0a48[1].Down.Triggered) {
			DAT_800c0a48[0].Down.Triggered = 0;
			DAT_800c0a48[1].Down.Triggered = 0;
			if (DAT_800d110c < DAT_800d1108 - 5) {
				DAT_800d110c++;
				DAT_800d1110 = 1;
			} else if (DAT_800d1104->getSelected() < 4) {
				DAT_800d1104->down();
			}
		}
		if (GoBack || DAT_800d1380 == -1) {
			FUN_8004b250(147, 0x2000, 0);
			return DAT_800d21e0;
		}
		if (Activated) {
			Card_SetSelectedFile(DAT_800a58bc[DAT_800a43f8[DAT_800d110c + DAT_800d1104->getSelected()]]);
			FUN_8004b250(145, 0x2000, 0);
			DAT_800d111c = 21;
		}
		break;
	case 21:
		DAT_800d13e4 = 0;
		switch (DAT_800d1144) {
		case 0:
			{
				int Error;
				DAT_800d1a34 = 1;
				Error = Card_Load(FILETYPE_B, DAT_800bf318.pBlockStart, 0);
				DAT_800d1a34 = 0;
				if (Error) {
					DAT_800d111c = 22;
				} else {
					int i;
					SVideoHead *VH = (SVideoHead *)(DAT_800bf318.pBlockStart + 128);
					DAT_800bf318.NumFrames = VH->NumFrames;
					for (i = 0; i < 5; i++)
						DAT_800bf318.Highlights[i] = VH->Highlights[i];
					DAT_800d111c = 23;
				}
			}
			break;
		case 1:
			if (Card_Load(FILETYPE_C, DAT_800bf318.pBlockStart, 0)) {
				DAT_800d111c = 22;
			} else {
				{
					SVideoHead *VH = (SVideoHead *)(DAT_800bf318.pBlockStart + 128);
					DAT_800a42f4.NumSkaters = VH->NumSkaters;
					DAT_800a42f4.Skater = VH->Skater;
					DAT_800a42f4.Skater2 = VH->Skater2;
					DAT_800a42f4.Level = VH->Level;
					DAT_800a42f4.GGame = VH->GGame;
					{
						int i;
						DAT_800bf318.NumFrames = VH->NumFrames;
						for (i = 0; i < 5; i++)
							DAT_800bf318.Highlights[i] = VH->Highlights[i];
					}
				}
				DAT_800d111c = 23;
			}
			break;
		case 2:
			{
				ulong *pTmp = (ulong *)FUN_8004d068(3200, 1, 1);
				if (Card_Load(FILETYPE_A, pTmp, 0)) {
					DAT_800d111c = 22;
				} else {
					DAT_800a6844 = *(SReplay *)(pTmp + 160);
					DAT_800d10f4 = 1;
					DAT_800d10f8 = 0;
					Front_ExtractASCIINameFromSJIS((char *)pTmp + 32, DAT_800a4308);
					DAT_800d111c = 23;
				}
				FUN_8004d5d0(pTmp);
			}
			break;
		}
		break;
	case 22:
		if (AnyButton) {
			FUN_8004b250(GoBack ? 147 : 145, 0x2000, 0);
			return 36;
		}
		break;
	case 23:
		return 35;
	case 27:
		break;
	}
	return 18;
}
