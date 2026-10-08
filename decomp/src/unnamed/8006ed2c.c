/* FUN_8006ed2c (0x8006ed2c) */
/* Copy of FUN_8006edb8 in the other direction; the loop keeps its entry jump, which comes from
   a goto loop (cc1 rotates while/for loops). */
typedef struct {
	char pad[20];
	int *p14;
	char q[64 - 24];
} S;

extern S DAT_800bf7a8[];
extern int *DAT_800c09a8[];

int *FUN_8004d068(int, int, int);

void FUN_8006ed2c(int i) {
	int *s = DAT_800bf7a8[i].p14;
	int *d = FUN_8004d068(30000, 1, 1);
	int j = 0;

	DAT_800c09a8[i] = d;
	goto test;
body:
	*d++ = *s++;
	j++;
test:
	if (j < 7500)
		goto body;
}
