/* Spool_Continue__Fv (0x8007046c) */
/* C++ (SPOOL.CPP). Demo twin; locals and blocks from its MAIN.SYM (SpoolMode is a function-static
   there, DAT_800d1f08 here). Steps the load queue's head entry through three states: open the file
   and allocate (an environment takes a free environment slot, evicting the oldest, and names its
   region), wait for the read, then process the PSX data and attach the environment. */
typedef unsigned char uchar;
typedef unsigned int uint;

struct SQueue {
	char Name[13];
	uchar Occupied;     /* 13 */
	uchar FileType;     /* 14 */
	uchar Region;       /* 15 */
	uchar KeepTextures; /* 16 */
};

struct SPSXRegion {
	char Name[16]; /* 0 */
	uint *pModels; /* 0x10 */
	uint *pPSX;    /* 0x14 */
	char pad18[0x34 - 0x18];
	uchar KeepTextures; /* 0x34 */
	char pad35[64 - 0x35];
};

extern SQueue DAT_800bf654[];
extern SPSXRegion DAT_800bf7a8[];

int DAT_800d1ef4;
int DAT_800d1f08;
int DAT_800d1ed0[2];
int DAT_800d1ef0;
uint *DAT_800d1f0c[2];

extern int DAT_800d1afc;

void ClearRegion(int, int, int);
void AttachNewEnviro(int);
int Spool_GetEnvIndex(int);
uint *Spool_SkipPackets(uint *);

extern "C" {
	int FileIO_Open__FPCc(char *);
	uint *Mem_NewX__FUiii(int, int, int);
	void FUN_8004cb10(uint *);
	void ProcessNewPSX__Fi(int);
}

void Spool_Continue() {
	SQueue *Q = &DAT_800bf654[DAT_800d1ef4];

	if (!Q->Occupied)
		return;

	switch (DAT_800d1f08) {
		case 0: {
			int FileSize = FileIO_Open__FPCc(Q->Name);

			switch (Q->FileType) {
				case 1: {
					char *pNew;
					char *pDest;
					int c;

					if (DAT_800d1ed0[0] != -1 && DAT_800d1ed0[1] != -1) {
						Q->Region = DAT_800d1ed0[DAT_800d1ef0];
						ClearRegion(Q->Region, 0, 0);

						DAT_800d1ed0[DAT_800d1ef0] = Q->Region;
					} else if (DAT_800d1ed0[0] == -1) {
						DAT_800d1ed0[0] = Q->Region;
					} else {
						DAT_800d1ed0[1] = Q->Region;
					}

					pNew = Q->Name;
					pDest = DAT_800bf7a8[Q->Region].Name;

					for (c = 0; *pNew != '.' && c < 9; c++)
						*pDest++ = *pNew++;

					*pDest = 0;
					DAT_800bf7a8[Q->Region].pPSX = Mem_NewX__FUiii(FileSize, 1, 1);
					FUN_8004cb10(DAT_800bf7a8[Q->Region].pPSX);
					break;
				}
				case 0:
				case 2:
					DAT_800bf7a8[Q->Region].pPSX = Mem_NewX__FUiii(FileSize, 1, 1);
					FUN_8004cb10(DAT_800bf7a8[Q->Region].pPSX);
					break;
			}

			DAT_800d1f08 = 1;
			DAT_800bf7a8[Q->Region].KeepTextures = Q->KeepTextures;
			break;
		}
		case 1:
			if (!DAT_800d1afc)
				DAT_800d1f08 = 2;

			break;
		case 2:
			switch (Q->FileType) {
				case 1:
					ProcessNewPSX__Fi(Q->Region);
					AttachNewEnviro(Q->Region);

					{
						int e = Spool_GetEnvIndex(Q->Region);

						DAT_800d1f0c[e] = Spool_SkipPackets(DAT_800bf7a8[Q->Region].pPSX);
					}

					break;
				case 0:
					ProcessNewPSX__Fi(Q->Region);
					break;
				case 2:
					break;
			}

			Q->Occupied = 0;
			DAT_800d1f08 = 0;
			DAT_800d1ef4 = (DAT_800d1ef4 + 1) % 20;
			break;
	}
}
