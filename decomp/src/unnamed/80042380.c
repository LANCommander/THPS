/* FUN_80042380 (0x80042380) */
extern char DAT_800a0534[];

char DAT_800d19a4[8];
int DAT_800d19a0;

void SFX_Stop__FUi(int a);
void FUN_8004d5d0(int a);
void DeleteFrom__5CBodyPP5CBody(char *p, char *l);
void FUN_800427bc(char *p);
void FUN_8001dfec(char *p, int a);
void dt_6CSuper(char *p, int a);
void FUN_80043530(char *p);

void FUN_80042380(char *p, int f) {
	*(char **)(p + 72) = DAT_800a0534;

	if (*(int *)(p + 1736)) {
		SFX_Stop__FUi(*(int *)(p + 1736));

		*(int *)(p + 1736) = 0;
	}

	if (*(int *)(p + 1740)) {
		SFX_Stop__FUi(*(int *)(p + 1740));

		*(int *)(p + 1740) = 0;
	}

	if (*(int *)(p + 348))
		FUN_8004d5d0(*(int *)(p + 348));

	if (*(int *)(p + 352))
		FUN_8004d5d0(*(int *)(p + 352));

	DeleteFrom__5CBodyPP5CBody(p, DAT_800d19a4);

	DAT_800d19a0--;
	FUN_800427bc(p);
	FUN_8001dfec(p + 2772, 2);
	FUN_8001dfec(p + 2696, 2);
	dt_6CSuper(p, 0);

	if (f & 1)
		FUN_80043530(p);
}
