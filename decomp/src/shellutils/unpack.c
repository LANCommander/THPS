/* unpack__11SlicedImage (0x80062d00) */
typedef struct {
	short a, b, c, d;
} SEnt;

typedef struct {
	char pad[24];
	SEnt *data;
	int w;
	int h;
	char pad2[8];
	int flag;
} SSliced;

void Pack_Unpack__Fss(short, short);
void FUN_8004d5d0(SEnt *);

void unpack__11SlicedImage(SSliced *t) {
	int i, j;

	i = 0;

	if (t->flag == 0) {
		if (t->data == 0)
			return;

		Pack_Unpack__Fss(t->data->a, t->data->b);
	} else {
		t->flag = 0;

		for (i = 0; i < t->h; i++) {
			for (j = 0; j < t->w; j++) {
				Pack_Unpack__Fss(t->data[i * t->w + j].a, t->data[i * t->w + j].b);
			}
		}
	}

	FUN_8004d5d0(t->data);

	t->data = 0;
}
