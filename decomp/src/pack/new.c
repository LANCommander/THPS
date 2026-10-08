/* Pack_New__FPP6TSPack (0x8004961c) */
typedef struct TSPack {
	unsigned short x, y, w, h;
	struct TSPack *next;
} TSPack;

TSPack *Pack_GetSlot__Fv(void);

TSPack *Pack_New__FPP6TSPack(TSPack **list) {
	TSPack *p = Pack_GetSlot__Fv();

	p->next = *list;
	*list = p;
	return p;
}
