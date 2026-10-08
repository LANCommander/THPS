/* Trig_InitialParseTRGFile__FPc (0x80044ed8) */
/* C++ (TRIG.CPP). Fuzzy demo twin (0.43; THPS1 loads the file here); locals from its MAIN.SYM.
   Loads <name>.TRG, relocates its node table, trims the buffer after the terminating node, then
   collects the restart (type 8) nodes and the 'H' named ones, runs the level's start-up command
   lists (type 15 in a two-player game, else type 4) and parses the rest of the file. Two pointers
   are bumped in place (`pTable += 3`, `pNodeName += 6`): written as `base + n`, CSE keeps the base
   live and folds the offset into the following load, which retail doesn't. */
typedef unsigned char uchar;
typedef unsigned short ushort;

struct CVector {
	int vx, vy, vz;
};

extern char DAT_800d1a04[];
extern char *DAT_800a8788[];
extern char *DAT_800a87d8[];
extern int DAT_800d1780;

char *DAT_800d19e0;
short **DAT_800d19e8;
int DAT_800d19ec;
int DAT_800d19d8;
int DAT_800d19dc;
int DAT_800d19e4;

char *Trig_GetPosition(CVector &, int);
void Trig_ParseTRGFile();

extern "C" {
	int FileIO_Open__FPCc(char *);
	char *Mem_NewX__FUiii(int, int, int);
	void FUN_8004cb10(char *);
	void FUN_8004cdd0(void);
	void FUN_8004d6a0(char *, int);
	void ExecuteCommandList__FPUsii(ushort *, int, int);
}

void Trig_InitialParseTRGFile(char *pName) {
	char Name[32];
	int Found;

	{
		char *pExt = DAT_800d1a04;
		char *pDest = Name;

		while (*pName)
			*pDest++ = *pName++;

		while (*pExt)
			*pDest++ = *pExt++;

		*pDest = 0;
	}

	DAT_800d19e0 = Mem_NewX__FUiii(FileIO_Open__FPCc(Name), 0, 1);
	FUN_8004cb10(DAT_800d19e0);
	FUN_8004cdd0();

	{
		short **pTable = (short **)DAT_800d19e0;
		int i;

		DAT_800d19ec = ((ushort *)pTable)[4];
		pTable += 3;
		DAT_800d19e8 = pTable;

		for (i = 0; i < DAT_800d19ec; i++) {
			*pTable = (short *)((int)*pTable + (int)DAT_800d19e0);
			pTable++;
		}
	}

	{
		short *pLast = DAT_800d19e8[DAT_800d19ec - 1];

		if (*pLast == 255)
			FUN_8004d6a0(DAT_800d19e0, ((char *)pLast - DAT_800d19e0 + 5) & ~3);
	}

	DAT_800d19d8 = 0;

	{
		int i;

		for (i = 0; i < DAT_800d19ec; i++) {
			short *pNode = DAT_800d19e8[i];

			if (*pNode == 8) {
				CVector Dummy;
				char *pNodeName = Trig_GetPosition(Dummy, i) + 6;

				DAT_800a8788[DAT_800d19d8++] = pNodeName;
			}
		}
	}

	DAT_800d19dc = 0;

	{
		int i;

		for (i = 0; i < DAT_800d19ec; i++) {
			short *pNode = DAT_800d19e8[i];

			if (*pNode == 8) {
				CVector Dummy;
				char *pNodeName = Trig_GetPosition(Dummy, i);

				pNodeName += 6;

				if (*pNodeName == 'H')

					DAT_800a87d8[DAT_800d19dc++] = pNodeName;
			}
		}
	}

	DAT_800d19e4 = 0xffff;
	Found = 0;

	if (DAT_800d1780 == 2) {
		int i;

		for (i = 0; i < DAT_800d19ec; i++) {
			short *pNode = DAT_800d19e8[i];

			if (*pNode == 15) {
				Found = 1;
				ExecuteCommandList__FPUsii((ushort *)(pNode + 1), i, 1);
			}
		}
	}

	if (!Found) {
		int i;

		for (i = 0; i < DAT_800d19ec; i++) {
			short *pNode = DAT_800d19e8[i];

			if (*pNode == 4)
				ExecuteCommandList__FPUsii((ushort *)(pNode + 1), i, 1);
		}
	}

	Trig_ParseTRGFile();
}
