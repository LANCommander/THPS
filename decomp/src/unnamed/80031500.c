/* FUN_80031500 (0x80031500) */
typedef struct {
	char pad[28];
	int v;
	char pad2[44 - 32];
} T;

extern T Group[];

int FUN_8002f290(void *, int, int);
void FUN_8002f438(void *, int);

void FUN_80031500(char *p) {
	int f = *(int *)(p + 0x368);
	int n = 0;

	if (f & 0x800) {
		int t = f & 0xff;

		if (f & 0x6000)
			n = FUN_8002f290(p, t, Group[t].v) / 20;

		if (n)
			FUN_8002f438(p, n);
	}
}
