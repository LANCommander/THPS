/* _._7CCamera (0x800788b8) flags=-fstructure-noalias */
extern char DAT_800a3554[];
extern char DAT_800a35c4[];
extern char DAT_800a3594[];

char DAT_800d2044[8];
int DAT_800d2040;

void DeleteFrom__5CBodyPP5CBody(char *p, char *l);
void FUN_8007d20c(char *p, int a);
void FUN_80043860(char *p, int a);
void __dl__5CItemPv(char *p);

typedef struct {
	char *v[419];
} S;

void FUN_800788b8(char *q, int f) {
	S *p = (S *)q;
	int n;

	p->v[18] = DAT_800a3554;
	DeleteFrom__5CBodyPP5CBody(q, DAT_800d2044);

	p->v[418] = DAT_800a35c4;
	n = DAT_800d2040 - 1;
	p->v[357] = DAT_800a3594;
	p->v[359] = DAT_800a35c4;
	p->v[357] = DAT_800a35c4;
	p->v[324] = DAT_800a35c4;
	p->v[319] = DAT_800a35c4;
	p->v[314] = DAT_800a35c4;
	p->v[309] = DAT_800a35c4;
	p->v[304] = DAT_800a35c4;
	DAT_800d2040 = n;
	FUN_8007d20c(q + 864, 2);
	FUN_8007d20c(q + 680, 2);
	FUN_8007d20c(q + 496, 2);
	FUN_8007d20c(q + 312, 2);
	FUN_80043860(q, 0);

	if (f & 1)
		__dl__5CItemPv(q);
}
