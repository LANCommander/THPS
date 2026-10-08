/* FUN_80065d14 (0x80065d14) */
void FUN_8006582c(int *p);
void Spool_Sync__Fv(void);
void FileIO_Sync__Fv(void);

void FUN_80065d14(int *p) {
	while (p[3] < p[2])
		FUN_8006582c(p);

	if (p[1] == 1)
		Spool_Sync__Fv();
	else
		FileIO_Sync__Fv();
}
