/* Spool_ClearPSX__FPc (0x8006fd18) */
typedef struct {
	char name[10];
	unsigned char f0a, f0b;
	unsigned *models;
	unsigned *f10;
	char pad[0x2c];
} SRegion;

extern SRegion DAT_800bf7a8[];

int Spool_FindRegion__FPc(char *);
void ClearRegion__Fiii(int, int, int);

void Spool_ClearPSX__FPc(char *name) {
	int r = Spool_FindRegion__FPc(name);

	if (DAT_800bf7a8[r].f0a)
		ClearRegion__Fiii(Spool_FindRegion__FPc(name), 1, 0);
}
