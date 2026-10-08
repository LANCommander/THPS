/* FUN_800109b8 (0x800109b8) */
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
extern char DAT_8009d0e0[];
extern int DAT_800d1e28;
extern int DAT_800d16a4;

int DAT_800d10ec;

int SFX_PlayX__FUisi(int, int, int);
int SFX_GetVoicePitch__FUi(int);
void FUN_8008c190(char *, int);

void FUN_800109b8(void) {
	int i;

	if (DAT_800a5398[DAT_800d1e28].f4c) {
		if (DAT_800d16a4 == 1) {
			DAT_800d10ec = 0;

			for (i = 0; i < 1; i++) {
				DAT_800a42b8[i].a0 = SFX_PlayX__FUisi(44, 0, 0);
				FUN_8008c190(DAT_8009d0e0, SFX_GetVoicePitch__FUi(DAT_800a42b8[i].a0));

				DAT_800a42b8[i].a1 = DAT_800a42b8[i].a3 = DAT_800a42b8[i].a4 = DAT_800a42b8[i].a2 =
				    0;
			}
		}
	}
}
