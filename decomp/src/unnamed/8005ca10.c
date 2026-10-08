/* FUN_8005ca10 (0x8005ca10) */
extern char DAT_800bec34[];

int DAT_800d1ca8;

void FUN_80065d80(char *p);

void FUN_8005ca10(void) {
	if (DAT_800d1ca8)
		FUN_80065d80(DAT_800bec34);

	DAT_800d1ca8 = 0;
}
