/* Mess_LoadFont__FPciii (0x8001eed4) */
extern int FileIO_Open__FPCc(char *);
extern void *Mem_NewX__FUiii(int, int, int);
extern void FUN_8004cb10(void *);
extern void FUN_8004cdd0(void);
extern void Mess_LoadFont__FPcT0iii(char *, void *, int, int, int);

void Mess_LoadFont(char *name, int a, int b, int c) {
	void *buf = Mem_NewX__FUiii(FileIO_Open__FPCc(name), 1, 1);

	FUN_8004cb10(buf);
	FUN_8004cdd0();
	Mess_LoadFont__FPcT0iii(name, buf, a, b, c);
}
