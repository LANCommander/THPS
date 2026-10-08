/* FUN_80048fec (0x80048fec) flags=-fstrict-aliasing */
typedef struct {
	char pad0[0x74];
	int Busy;   /* 0x74 */
	int Flag78; /* 0x78 */
	char pad7c[0x84 - 0x7c];
	unsigned long OT[(0x80a8 - 0x84) / 4];
	unsigned long Prims; /* 0x80a8 */
} SBuffer;

SBuffer *DAT_800d1a48;
SBuffer *DAT_800d1a58;
unsigned long DAT_800d1a54;

void Pause__Fi(int);
void FUN_8008c468(int);
void FUN_80048e40(void);
int FUN_80048c74(void);
void FUN_8008c7d4(unsigned long *, int);

void FUN_80048fec(void) {
	DAT_800d1a58 = DAT_800d1a48;

	while (DAT_800d1a58->Busy)
		Pause__Fi(1);

	if (DAT_800d1a48->Flag78) {
		FUN_8008c468(0);
		FUN_80048e40();
	}

	FUN_8008c7d4(DAT_800d1a48->OT, FUN_80048c74());

	DAT_800d1a54 = DAT_800d1a48->Prims & 0x7fffffff;
}
