/* RestartCompFrig__Fv (0x8001a6a8) */
extern int DAT_800d1e28;
extern int DAT_800d19e4;
extern char DAT_8009e4dc[];

void Trig_SetRestart__FPc(char *);
void FUN_80044c84(void);

void RestartCompFrig(void) {
	if (DAT_800d1e28 == 8) {
		int s = DAT_800d19e4;

		Trig_SetRestart__FPc(DAT_8009e4dc);
		FUN_80044c84();

		DAT_800d19e4 = s;
	}
}
