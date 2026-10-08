/* Mess_LoadFont__FPciii (0x8001eed4) */
extern int FileIO_Open__FPCc(char *);
extern void *Mem_NewX__FUiii(int, int, int);
extern void FileIO_Load__FPv(void *);
extern void FileIO_Sync__Fv(void);
extern void Mess_LoadFont__FPcT0iii(char *, void *, int, int, int);

void Mess_LoadFont(char *name, int a, int b, int c) {
	void *buf = Mem_NewX__FUiii(FileIO_Open__FPCc(name), 1, 1);

	FileIO_Load__FPv(buf);
	FileIO_Sync__Fv();
	Mess_LoadFont__FPcT0iii(name, buf, a, b, c);
}
