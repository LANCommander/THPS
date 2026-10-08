/* FUN_80065340 (0x80065340) */
extern char DAT_800a2140[];

int BASEF(char *p, int a);
void FUN_80024238(void *p);

void FUN_80065340(char *p, int f) {
	*(char **)p = DAT_800a2140;
	BASEF(p, 0);

	if (f & 1)
		FUN_80024238(p);
}
