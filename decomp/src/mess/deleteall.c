/* Mess_DeleteAll__Fv (0x8001d5fc) */
typedef struct Message {
	char pad[0x14];
	struct Message *next;
	struct Message *prev;
} Message;

Message *DAT_800d15ec;

extern void FUN_8004d5d0(void *);

void Mess_DeleteAll(void) {
	Message *m = DAT_800d15ec;
	Message *n;

	if (m) {
		n = m->next;
	loop:
		FUN_8004d5d0(m);

		if (n) {
			m = n;
			n = n->next;
			goto loop;
		}
	}

	DAT_800d15ec = 0;
}
