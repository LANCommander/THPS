/* FUN_80023528 (0x80023528) */
short DAT_800d1658;

struct S {
	int a, b, c;
};

void GameFMV_StopFMV__Fv(void);
void FUN_80023168(int a);
void FUN_80022aec(struct S *p);
void GameFMV_StartFMV__Fi(int a);

void FUN_80023528(void) {
	struct S st;
	struct S *s;

	GameFMV_StopFMV__Fv();

	s = &st;
	st.a = 0;
	s->b = 0;
	s->c = 0;
	FUN_80023168(2);
	FUN_80022aec(s);
	GameFMV_StartFMV__Fi(DAT_800d1658 != -1);
}
