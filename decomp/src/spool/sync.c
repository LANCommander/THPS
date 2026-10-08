/* Spool_Sync__Fv (0x8007079c) */
extern char DAT_800bf654[][17];
extern int DAT_800d1afc;

int DAT_800d1ef4;

void Spool_Continue__Fv(void);
void FUN_8004cc18(void);

void Spool_Sync__Fv(void) {
	while (DAT_800d1afc || DAT_800bf654[DAT_800d1ef4][13]) {
		Spool_Continue__Fv();
		FUN_8004cc18();
	}
}
