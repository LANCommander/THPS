/* PowerUp_Create__FUsRC7CVectorUiiR7CVector (0x80020b18) */
void *__nw__5CItemUi(unsigned);
void *__8CPowerUpUsRC7CVectorT2Uii(void *, unsigned short, void *, void *, unsigned, int);

void PowerUp_Create__FUsRC7CVectorUiiR7CVector(unsigned short type, void *pos, unsigned a, int b,
                                               void *v) {
	void *p = __nw__5CItemUi(356);

	if (p)
		__8CPowerUpUsRC7CVectorT2Uii(p, type, pos, v, a, b);
}
