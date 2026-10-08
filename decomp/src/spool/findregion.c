/* Spool_FindRegion__FPc (0x8006fcb0) */
typedef struct {
	char name[10];
	unsigned char f0a, f0b;
	unsigned *models;
	unsigned *f10;
	char pad[0x2c];
} SRegion;

extern SRegion DAT_800bf7a8[];

int Utils_CompareStrings__FPCcT0Ui(const char *, const char *, unsigned);

int Spool_FindRegion__FPc(char *name) {
	int i;

	for (i = 0; i < 40; i++)
		if (Utils_CompareStrings__FPCcT0Ui(name, DAT_800bf7a8[i].name, -1))
			return i;

	return -1;
}
