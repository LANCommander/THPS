/* Pack_Merge__FP6TSPack (0x8004a590) */
typedef struct TSPack {
	unsigned short x, y, w, h;
	struct TSPack *next;
} TSPack;

TSPack *DAT_800d1a60;

TSPack *Pack_MergeAdjacent__FP6TSPackT0(TSPack *, TSPack *);

int Pack_Merge__FP6TSPack(TSPack *p) {
	int merged = 0;
	int again;
	TSPack *q;

	do {
		again = 0;

		for (q = DAT_800d1a60; q; q = q->next) {
			unsigned short py = p->y, qy = q->y;

			if (py == qy && p->h == q->h) {
				if (q->x + q->w == p->x || p->x + p->w == q->x)
					goto merge;
			} else if (p->x == q->x && p->w == q->w && (qy & 0x100) == (py & 0x100)) {
				if (q->y + q->h == p->y || p->y + p->h == q->y)
					goto merge;
			}

			continue;
		merge:
			again = 1;
			p = Pack_MergeAdjacent__FP6TSPackT0(q, p);
			merged = 1;
			break;
		}
	} while (again);

	return merged;
}
