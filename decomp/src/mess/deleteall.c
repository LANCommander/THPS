/* Mess_DeleteAll__Fv (0x8001d5fc) */
#include "names.h"
typedef struct Message {
	char pad[0x14];
	struct Message *next;
	struct Message *prev;
} Message;

Message *DAT_800d15ec;

extern void Mem_Delete(void *);

void Mess_DeleteAll(void) {
	Message *m = DAT_800d15ec;
	Message *n;

	if (m) {
		n = m->next;
	loop:
		Mem_Delete(m);

		if (n) {
			m = n;
			n = n->next;
			goto loop;
		}
	}

	DAT_800d15ec = 0;
}
