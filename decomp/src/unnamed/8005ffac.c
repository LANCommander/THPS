/* FUN_8005ffac (0x8005ffac) */
typedef struct {
	char p[0x184];
	int f184;
	int f188;
} G;

typedef struct {
	char p[0xf0];
	int f0;
	int f4;
	int f8;
	int fc;
} Z;

extern unsigned char DAT_800c0a48[];
extern G DAT_800a4118;
extern Z DAT_800a5d5c;
extern char DAT_800d1d40[];

void FUN_800648c0(int, int, int);
int getSelected__12VerticalMenu(int);
void SFX_PlayX__FUisi(int, int, int);
void FUN_8008b900(char *, char *, int, int);
void setString__12VerticalMenuiPc(int, int, char *);
void Pad_ClearTriggers__FP8SControl(unsigned char *);

int FUN_8005ffac(int a) {
	char buf[32];
	int s3, s1, t;
	unsigned char *v;
	unsigned char *s0;

	s0 = DAT_800c0a48;
	FUN_800648c0(a, 1, *(int *)(s0 + 0x2b8) == 0);

	if (s0[0x81] || s0[0x1ed] || s0[0x91] || s0[0x1fd]) {
		s3 = 0;

		if (DAT_800c0a48[0x81] || DAT_800c0a48[0x1ed])
			s3 = 1;

		Pad_ClearTriggers__FP8SControl(DAT_800c0a48);
		Pad_ClearTriggers__FP8SControl(DAT_800c0a48 + 364);

		if (getSelected__12VerticalMenu(a) == 3) {
			if (s3 != DAT_800a4118.f184)
				SFX_PlayX__FUisi(144, 0x2000, 0);

			s1 = s3 != 0;
			DAT_800a4118.f184 = s1;
			FUN_8008b900(buf, DAT_800d1d40, DAT_800a5d5c.f8,
			             s1 ? DAT_800a5d5c.f0 : DAT_800a5d5c.f4);
			setString__12VerticalMenuiPc(a, 3, buf);
		}

		if (getSelected__12VerticalMenu(a) == 4) {
			s1 = s3 != 0;

			if (s3 != DAT_800a4118.f188)
				SFX_PlayX__FUisi(144, 0x2000, 0);

			DAT_800a4118.f188 = s1;
			FUN_8008b900(buf, DAT_800d1d40, DAT_800a5d5c.fc,
			             s1 ? DAT_800a5d5c.f0 : DAT_800a5d5c.f4);
			setString__12VerticalMenuiPc(a, 4, buf);
		}
	}

	if (DAT_800c0a48[0xe1] || DAT_800c0a48[0x24d] || DAT_800c0a48[0x31] || DAT_800c0a48[0x19d]) {
		t = getSelected__12VerticalMenu(a);

		if (t < 5) {
			if (t >= 3) {
				Pad_ClearTriggers__FP8SControl(DAT_800c0a48);
				Pad_ClearTriggers__FP8SControl(DAT_800c0a48 + 364);
			}
		}
	}
}
