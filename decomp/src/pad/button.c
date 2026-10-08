/* Pad_Button__FP7SButtoni (0x80070c74) */
typedef struct {
	unsigned char down, trig;
	int held, released, count;
} SButton;

int DAT_800d1f68;

extern void FUN_800241d4(void);

void Pad_Button(SButton *b, int pressed) {
	b->count++;

	if (!b->down && pressed) {
		b->trig = 1;
		b->count = 0;
	}

	if (pressed) {
		DAT_800d1f68 = 0;
		FUN_800241d4();

		b->down = 1;
	} else
		b->down = 0;

	if (b->down) {
		b->released = 0;
		b->held++;
	} else {
		b->held = 0;
		b->released++;
	}
}
