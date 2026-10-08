/* AttachTo__5CBodyPP5CBody (0x800438dc) */
#include "names.h"
struct N {
	int a[7];
	struct N *next;
	int b[4];
	struct N *prev;
};

void CBody_AttachTo(struct N *n, struct N **head) {
	struct N *h = *head;

	n->prev = 0;
	n->next = h;
	*head = n;

	if (n->next)
		n->next->prev = n;
}
