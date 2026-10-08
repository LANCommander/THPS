/* Card_LoadReplayFromCD__FPUlT0Pc (0x80014c74) */
extern char DAT_8009e0b0[];
extern char DAT_8009e0e4[];

char *FileIO_Open__FPCc(char *);
char *Mem_NewX__FUiii(char *, int, int);
void FileIO_Load__FPv(char *);
void FileIO_Sync__Fv(void);
void Mem_Delete__FPv(char *);
void FUN_8008c190(char *);
void Mem_Copy__FPvT0i(void *, void *, int);
int CalcChecksum__FPUlUl(void *, int);

int Card_LoadReplayFromCD__FPUlT0Pc(char *a, char *b, char *name) {
	int c;
	char *p = Mem_NewX__FUiii(FileIO_Open__FPCc(name), 1, 1);

	if (p) {
		FileIO_Load__FPv(p);
		FileIO_Sync__Fv();
	}

	Mem_Copy__FPvT0i(a, p, 0x6000);

	if (b)
		Mem_Copy__FPvT0i(b, p + 0x6000, 0x6000);

	Mem_Delete__FPv(p);

	c = *(short *)(a + 566);

	if (c != CalcChecksum__FPUlUl(a + 640, 23936))
		FUN_8008c190(DAT_8009e0b0);

	if (b) {
		c = *(short *)(b + 566);

		if (c != CalcChecksum__FPUlUl(b + 640, 23936))
			FUN_8008c190(DAT_8009e0e4);
	}

	return 0;
}
