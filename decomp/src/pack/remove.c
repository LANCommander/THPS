/* Pack_Remove__FPP6TSPackP6TSPack (0x80049710) */
typedef struct TSPack {
	unsigned short x, y, w, h;
	struct TSPack *next;
} TSPack;

void Pack_KillSlot__FP6TSPack(TSPack *);

void Pack_Remove__FPP6TSPackP6TSPack(TSPack **list, TSPack *p) {
	TSPack *q;

	if (*list == p) {
		*list = p->next;
	} else {
		q = *list;

		while (q->next != p)
			q = q->next;

		q->next = p->next;
	}

	Pack_KillSlot__FP6TSPack(p);
}
