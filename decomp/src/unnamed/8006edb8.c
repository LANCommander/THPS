/* FUN_8006edb8 (0x8006edb8) */
typedef struct { char pad[20]; int *p14; char q[64 - 24]; } S;
extern S DAT_800bf7a8[];
extern int *DAT_800c09a8[];
void FUN_8004d5d0(int *);
void FUN_8006edb8(int i)
{
	int *d = DAT_800bf7a8[i].p14;
	int *s = DAT_800c09a8[i];
	do {
		int j = 0;
		goto test;
	body:
		*d++ = *s++;
	test:
		if (j < 7500) {
			j++;
			goto body;
		}
	} while (0);
	FUN_8004d5d0(DAT_800c09a8[i]);
	DAT_800c09a8[i] = 0;
}
