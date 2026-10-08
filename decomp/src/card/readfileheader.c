/* Card_ReadFileHeader__FPcP9SCardHead (0x8001508c) */
extern char DAT_800d1388[];

void FUN_8008b900(char *, char *, char *);
int FUN_8008eb4c(char *, int);
void _clear_event__Fv(void);
int FUN_8008ead8(int, void *, int);
int FUN_8008e934(int);
void Pause__Fi(int);
int Card_CheckStatus__Fii(int, int);

int Card_ReadFileHeader__FPcP9SCardHead(char *name, short *out) {
	char buf[32];
	int i, fd, n;

	FUN_8008b900(buf, DAT_800d1388, name);

	for (i = 0; i < 8; i++) {
		fd = FUN_8008eb4c(buf, 1);

		if (fd == -1) {
			*out = 26214;
			Pause__Fi(1);
			Card_CheckStatus__Fii(0, 0);
		} else {
			_clear_event__Fv();

			n = FUN_8008ead8(fd, out, 512);
			FUN_8008e934(fd);

			if (n == 512)
				return 0;
		}
	}

	return 1;
}
