/* FUN_8005ca88 (0x8005ca88) */
extern char *DAT_800d1b10;
extern char DAT_800a1a98[];
extern char DAT_800a1ab0[];

void FUN_8008c190(char *a);
char *__nw__6CClassUi(unsigned n);
char *FUN_8006613c(char *p);
void FUN_80066214(char *p, char *a);

void FUN_8005ca88(void) {
	char *p;

	if (DAT_800d1b10)
		FUN_8008c190(DAT_800a1a98);

	p = __nw__6CClassUi(324);

	if (p)
		p = FUN_8006613c(p);

	DAT_800d1b10 = p;
	FUN_80066214(p, DAT_800a1ab0);
}
