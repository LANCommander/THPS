/* FUN_80010bb8 (0x80010bb8) */
typedef struct {
	int a0, a1, a2, a3, a4, a5;
} S;

typedef struct {
	char p[0x4c];
	int f4c;
	char q[0x78 - 0x50];
} E;

extern E DAT_800a5398[];
extern S DAT_800a42b8[];
extern int DAT_800d1e28;
extern int DAT_800d16a4;

int DAT_800d10ec;

int Crowd_MoveTowards__FRiii(int *, int, int);
void FUN_80011060(int);
void FUN_8004b7cc(int, int, int);
int Redbook_Rnd__Fi(int);

void FUN_80010bb8(void) {
	int i;

	if (DAT_800a5398[DAT_800d1e28].f4c) {
		if (DAT_800d16a4 == 1) {
			for (i = 0; i <= 0; i++) {
				if (DAT_800a42b8[i].a0) {
					if (Crowd_MoveTowards__FRiii(&DAT_800a42b8[i].a1, DAT_800a42b8[i].a3, 100) ||
					    Crowd_MoveTowards__FRiii(&DAT_800a42b8[i].a2, DAT_800a42b8[i].a4, 100)) {
						FUN_8004b7cc(DAT_800a42b8[i].a0, (DAT_800a42b8[i].a1 * 2) / 3,
						             (DAT_800a42b8[i].a2 * 2) / 3);
					} else {
						if (Redbook_Rnd__Fi(30) == 0) {
							DAT_800a42b8[i].a3 = Redbook_Rnd__Fi(8192);
							DAT_800a42b8[i].a4 = Redbook_Rnd__Fi(8192);
						}
					}
				}
			}

			if (DAT_800d10ec && Redbook_Rnd__Fi(50) == 0) {
				FUN_80011060(DAT_800d10ec << 13);

				DAT_800d10ec--;
			}
		}
	}
}
