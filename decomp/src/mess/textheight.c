/* Mess_TextHeight__FPCc (0x8001ddb0) */
extern int Mess_TextHeight2__FPCc(const char *);
extern int Mess_TextHeightAboveBaseline__FPCc(void);
extern int Mess_TextHeightBelowBaseline__FPCc(const char *);

char DAT_800d1602;

int Mess_TextHeight(const char *s) {
	if (DAT_800d1602 == 0)
		return Mess_TextHeight2__FPCc(s);

	return Mess_TextHeightAboveBaseline__FPCc() + Mess_TextHeightBelowBaseline__FPCc(s);
}
