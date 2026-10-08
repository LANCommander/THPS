/* Mess_TextHeight__FPCc (0x8001ddb0) */
extern int FUN_8001d440(const char *);
extern int FUN_8001dc9c(void);
extern int FUN_8001db80(const char *);

char DAT_800d1602;

int Mess_TextHeight(const char *s) {
	if (DAT_800d1602 == 0)
		return FUN_8001d440(s);

	return FUN_8001dc9c() + FUN_8001db80(s);
}
