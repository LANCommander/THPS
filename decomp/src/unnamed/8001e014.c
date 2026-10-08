/* FUN_8001e014 (0x8001e014) */
int Redbook_Rnd__Fi(int a);

void FUN_8001e014(short *p) {
	int i = 0;
	short *q = p;

	for (; i < 32; i++) {
		*q = Redbook_Rnd__Fi(30) + 15;
		q++;
	}

	p[32] = 280;
	p[35] = 240;
}
