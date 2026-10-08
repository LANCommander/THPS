/* Load8BitBMP__FPcPPcPiT2PUs (0x80061654) */
extern char DAT_800a208c[];
extern char DAT_800a20a0[];

int FileIO_Open__FPCc(char *);
char *Mem_NewX__FUiii(int, int, int);
void FileIO_Load__FPv(char *);
void FileIO_Sync__Fv(void);
void FUN_8008c190(char *, char *);
void Load8BitBMP2__FPcPPcPiT2PUs(char *, char **, int *, int *, unsigned short *);

int Load8BitBMP__FPcPPcPiT2PUs(char *name, char **a, int *b, int *c, unsigned short *d) {
	int r = FileIO_Open__FPCc(name);
	char *p;

	if (r <= 0) {
		FUN_8008c190(DAT_800a208c, name);
		return 0;
	}

	p = Mem_NewX__FUiii(r, 1, 1);

	if (p) {
		FileIO_Load__FPv(p);
		FileIO_Sync__Fv();
		Load8BitBMP2__FPcPPcPiT2PUs(p, a, b, c, d);
		return 1;
	}

	FUN_8008c190(DAT_800a20a0, name);
	return 0;
}
