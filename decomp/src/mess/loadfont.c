/* Mess_LoadFont__FPciii (0x8001eed4) */
extern int FUN_8004c8a4(char *);
extern void *FUN_8004d068(int, int, int);
extern void FUN_8004cb10(void *);
extern void FUN_8004cdd0(void);
extern void Mess_LoadFont__FPcT0iii(char *, void *, int, int, int);

void Mess_LoadFont(char *name, int a, int b, int c) {
	void *buf = FUN_8004d068(FUN_8004c8a4(name), 1, 1);

	FUN_8004cb10(buf);
	FUN_8004cdd0();
	Mess_LoadFont__FPcT0iii(name, buf, a, b, c);
}
