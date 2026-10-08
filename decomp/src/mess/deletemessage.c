/* Mess_DeleteMessage__FP7Message (0x8001d590) */
typedef struct Message {
	char pad[0x14];
	struct Message *next;
	struct Message *prev;
} Message;

Message *DAT_800d15ec;

extern void Mem_Delete__FPv(void *);

void Mess_DeleteMessage(Message *m) {
	if (m->next)
		m->next->prev = m->prev;

	if (m->prev)
		m->prev->next = m->next;

	if (m == DAT_800d15ec)
		DAT_800d15ec = m->next;

	Mem_Delete__FPv(m);
}
