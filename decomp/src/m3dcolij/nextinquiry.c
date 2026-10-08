/* NextInquiry__Fv (0x8007ea94) */
typedef struct Item {
	short _0;
	unsigned short inquiry;
	char _4[0x18];
	struct Item *next;
} Item;

unsigned short DAT_800d20c8;

extern Item *DAT_800d1eec __attribute__((section(".data"))),
    *DAT_800d19b0 __attribute__((section(".data")));

void NextInquiry(void) {
	Item *p;

	if (++DAT_800d20c8 == 0) {
		DAT_800d20c8 = 1;

		for (p = DAT_800d1eec; p; p = p->next)
			p->inquiry = 0;

		for (p = DAT_800d19b0; p; p = p->next)
			p->inquiry = 0;
	}
}
