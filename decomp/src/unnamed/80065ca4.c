/* FUN_80065ca4 (0x80065ca4) */
extern int DAT_800d1afc;

void FileIO_Continue__Fv(int *p);
void Spool_Continue__Fv(void);
void FUN_8006582c(int *p);

void FUN_80065ca4(int *p) {
	FileIO_Continue__Fv(p);

	if (p[1] == 1)
		Spool_Continue__Fv();

	if (p[3] < p[2] && DAT_800d1afc == 0)
		FUN_8006582c(p);
}
