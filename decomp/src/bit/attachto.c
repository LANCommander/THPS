/* AttachTo__4CBitPv (0x80027d90) */
#include "names.h"
void CBit_AttachTo(void **t, void **head) {
	void *h = *head;

	t[0] = 0;
	t[1] = h;
	*head = t;

	if (t[1])
		*(void **)t[1] = t;
}
