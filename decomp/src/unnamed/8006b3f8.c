/* FUN_8006b3f8 (0x8006b3f8) */
extern char DAT_800a2320[];

void FUN_800171f0(void);
void ResetMainDemoTimer__Fv(void);
void FUN_8004b09c(char *p);
void FUN_8005bb70(void);

void FUN_8006b3f8(void) {
	volatile int pad[2];

	FUN_800171f0();
	ResetMainDemoTimer__Fv();
	FUN_8004b09c(DAT_800a2320);
	FUN_8005bb70();
}
