/* CreateMessage__Fv (0x8001d550) */
typedef struct Message {
	char pad[0x14];
	struct Message *next;
	struct Message *prev;
} Message;

Message *DAT_800d15ec;

extern Message *Mem_NewX__FUiii(int, int, int);

void CreateMessage(void) {
	Message *m = Mem_NewX__FUiii(0x1c, 0, 1);
	Message *h = DAT_800d15ec;

	m->prev = 0;
	DAT_800d15ec = m;
	m->next = h;

	if (h)
		h->prev = m;
}
