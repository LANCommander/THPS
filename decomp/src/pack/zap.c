/* Pack_Zap__Fiiii (0x8004a69c) */
typedef struct TSPack {
	unsigned short x, y, w, h;
	struct TSPack *next;
} TSPack;

TSPack *DAT_800d1a64;

TSPack *Pack_NewFree__Fiiii(int, int, int, int);
int Pack_Merge__FP6TSPack(TSPack *);

void Pack_Zap__Fiiii(int x, int y, int w, int h) {
	TSPack *p;
	int d;
restart:
	for (p = DAT_800d1a64; p; p = p->next) {
		if (p->w + (p->x - 1) < x)
			continue;

		if (!(p->x < x + w))
			continue;

		if (p->h + (p->y - 1) < y)
			continue;

		if (p->y < y + h)
			break;
	}

	if (!p) {
		Pack_Merge__FP6TSPack(Pack_NewFree__Fiiii(x, y, w, h));
		return;
	}

	d = p->x;

	if (!(x < d) && !(y < p->y) && !(d + p->w < x + w) && !(p->y + p->h < y + h))
		return;

	if (w < 32 && h < 32) {
		if (x < d) {
			d = d - x;
			Pack_Zap__Fiiii(x, y, d, h);

			x += d;
			w -= d;
			goto restart;
		}

		d = d + p->w;

		if (d < x + w) {
			d = d - x;
			Pack_Zap__Fiiii(x, y, d, h);

			x += d;
			w -= d;
			goto restart;
		}

		d = p->y;

		if (y < d) {
			d = d - y;
			Pack_Zap__Fiiii(x, y, w, d);

			y += d;
			h -= d;
			goto restart;
		}

		d = d + p->h;

		if (d < y + h) {
			d = d - y;
			Pack_Zap__Fiiii(x, y, w, d);

			y += d;
			h -= d;
			goto restart;
		}
	}

	if (w < h) {
		d = h / 2;
		Pack_Zap__Fiiii(x, y, w, d);

		y += d;
		h -= d;
	} else {
		d = w / 2;
		Pack_Zap__Fiiii(x, y, d, h);

		x += d;
		w -= d;
	}

	goto restart;
}
