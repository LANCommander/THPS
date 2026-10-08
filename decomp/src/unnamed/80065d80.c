/* FUN_80065d80 (0x80065d80) */
void Spool_Sync__Fv(void);
void FileIO_Sync__Fv(void);
void FUN_80065e04(int *p, int i);

void FUN_80065d80(int *p) {
	int i;

	if (p[1] == 1)
		Spool_Sync__Fv();
	else
		FileIO_Sync__Fv();

	for (i = 0; i < p[2]; i++)
		FUN_80065e04(p, i);

	p[3] = 0;
}
