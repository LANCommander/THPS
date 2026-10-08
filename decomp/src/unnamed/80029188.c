/* FUN_80029188 (0x80029188) */
extern char DAT_8009f7e8[];

void FUN_80028d54(char *p, int a, int b, int c, unsigned char b1, unsigned char b2,
                  unsigned char b3, unsigned char b4, unsigned char b5, unsigned char b6);
int Redbook_Rnd__Fi(int a);

char *FUN_80029188(char *p, int a, int s, int c, int e, unsigned char b1, unsigned char b2,
                   unsigned char b3, unsigned char b4, unsigned char b5, unsigned char b6) {
	unsigned i;

	FUN_80028d54(p, a, s, c, b1, b2, b3, b4, b5, b6);

	*(char **)(p + 68) = DAT_8009f7e8;
	*(int *)(p + 172) = s;
	*(int *)(p + 168) = (s * e) / 256;

	for (i = 0; i < *(unsigned *)(p + 80); i++) {
		*(int *)(p + 136 + i * 4) = Redbook_Rnd__Fi(4096);
		*(int *)(p + 104 + i * 4) = Redbook_Rnd__Fi(50) + 50;
	}

	return p;
}
