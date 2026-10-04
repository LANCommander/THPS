/* FUN_8006e454 (0x8006e454) */
/* C++. Counts a skater event (+0xe00) in career mode: the 5th ends it (99, FUN_8006e2fc(1));
   before that it shows "n of N" for the current level. */
struct SMessageProg;
struct SLevel {
	char pad0[0x38];
	int Goal;                 /* 0x38 */
	char pad3c[120 - 0x3c];
};
extern SLevel DAT_800a5398[];
extern char DAT_800a23a0[];
extern SMessageProg DAT_800a5fd0;
extern char DAT_800d3888[];
extern int DAT_800d16a4;
extern char *DAT_800d19a4;
extern int DAT_800d1e28;
void Mess_Message(const char *, SMessageProg *, bool, short, short);
extern "C" {
void FUN_8006e2fc(int);
int FUN_8008b900(char *, const char *, ...);
}
extern "C" void FUN_8006e454(void)
{
	if (DAT_800d16a4 != 1)
		return;
	char *pSkater = DAT_800d19a4;
	int n = ++*(int *)(pSkater + 0xe00);
	if (n == 5) {
		*(int *)(pSkater + 0xe00) = 99;
		FUN_8006e2fc(1);
		return;
	}
	FUN_8008b900(DAT_800d3888, DAT_800a23a0, n, DAT_800a5398[DAT_800d1e28].Goal);
	Mess_Message(DAT_800d3888, &DAT_800a5fd0, 1, 0, 0);
}
