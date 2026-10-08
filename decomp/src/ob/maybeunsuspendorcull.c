/* Ob_MaybeUnSuspendOrCull__Fv (0x800446d4) */
typedef struct CBody {
	char _0[4];
	int pos[3];
	char _10[0x0c];
	struct CBody *next;
	char _20[0x32];
	unsigned short flags;
} CBody;

CBody *DAT_800d19b4;
unsigned DAT_800d19c0;

extern CBody *DAT_800d19a4 __attribute__((section(".data")));
extern int DAT_800d1780 __attribute__((section(".data")));
unsigned Utils_CrapDist__FRC7CVectorT0(int *, int *);
void UnSuspend__5CBody(CBody *);

void Ob_MaybeUnSuspendOrCull(void) {
	CBody *b = DAT_800d19b4;
	CBody *n;

	if (!b)
		return;

	n = b->next;

	for (;;) {
		if (b->flags & 2) {
			unsigned d = Utils_CrapDist__FRC7CVectorT0(DAT_800d19a4->pos, b->pos);

			if (DAT_800d1780 == 2) {
				unsigned d2 = Utils_CrapDist__FRC7CVectorT0(DAT_800d19a4->next->pos, b->pos);

				if (d2 < d)
					d = d2;
			}

			if (!(DAT_800d19c0 < d))
				UnSuspend__5CBody(b);
		}

		b = n;

		if (n)
			n = n->next;
		else
			break;
	}
}
