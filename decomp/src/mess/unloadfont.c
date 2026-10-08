/* Mess_UnloadFont__Fv (0x8001ef60) */
typedef struct {
	char pad[16];
	int count;
	char *ptr;
	char rest[12];
} Font;

extern Font DAT_800a6110[];

int DAT_800d15e4, DAT_800d15e0;

void Pack_Unpack__Fss(short, short);
void Free16Slot__FUs(unsigned short);
void FUN_8004d5d0(char *);

void Mess_UnloadFont__Fv(void) {
	int i;

	for (i = 0; i < DAT_800a6110[DAT_800d15e4].count; i++) {
		char *p = (char *)(i * 36 + (int)DAT_800a6110[DAT_800d15e4].ptr);

		Pack_Unpack__Fss(*(short *)(p + 8), *(short *)(p + 12));
	}

	Free16Slot__FUs(*(unsigned short *)(DAT_800a6110[DAT_800d15e4].ptr + 22));
	FUN_8004d5d0(DAT_800a6110[DAT_800d15e4].ptr);

	DAT_800a6110[DAT_800d15e4].ptr = 0;

	{
		int n = DAT_800d15e0, i, m;

		if (DAT_800d15e4 == n - 1) {
			for (;;) {
				if (n <= 0)
					return;

				m = n - 1;
				i = n;
				DAT_800d15e0 = m;
				n = m;

				if (DAT_800a6110[i - 2].ptr)
					return;
			}
		}
	}
}
