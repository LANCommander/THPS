/* __11CSmokeTrailR7CVectoriiii (0x8002a2ec) */
typedef struct {
	char p0[0x44];
	char *vt;
	int n;
	char p1[0x5c - 0x4c];
	int *arr;
} B;

extern char DAT_8009f6a0[];
extern char DAT_800d18c4[];

void __7CRibbonRC7CVectoriiPcT4ii(B *, int, int, int, char *, char *, int, int);
void SetTint__7CFT4BitUcUcUc(int, int, int, int);
void FUN_800280f8(int, int);

B *__11CSmokeTrailR7CVectoriiii(B *p, int a1, int a2, int r, int g, int b) {
	int i, j, t, n, dr, dg, db;

	__7CRibbonRC7CVectoriiPcT4ii(p, a1, a2, 2, DAT_800d18c4, DAT_800d18c4, 400, 1);

	n = p->n;
	dr = r / n;
	dg = g / n;
	i = 0;
	db = b / n;
	p->vt = DAT_8009f6a0;

	if (n > 0) {
		do {
			j = i + 1;
			t = n - j;
			SetTint__7CFT4BitUcUcUc(p->arr[i], (r - t * dr) & 255, (g - t * dg) & 255,
			                        (b - t * db) & 255);
			FUN_800280f8(p->arr[i], 8);

			n = p->n;
			i = j;
		} while (i < n);
	}

	return p;
}
