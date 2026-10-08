/* Card_FormatCard__Fii (0x80015474) */
extern char DAT_8009e124[];

void FUN_8008b900(char *, char *, int, int);
void _clear_event_x__Fv(void);
int FUN_8008eaa8(char *);
int _card_event_x__Fv(void);

int Card_FormatCard__Fii(int a, int b) {
	char buf[8];
	int s, r;

	FUN_8008b900(buf, DAT_8009e124, a, b);
	_clear_event_x__Fv();

	s = FUN_8008eaa8(buf);
	r = _card_event_x__Fv();

	if (r == 1)
		r = 1;
	else if (r == 3)
		r = -1;
	else
		r = -3;

	if (s == 0 && r == 1)
		r = -3;

	return r;
}
