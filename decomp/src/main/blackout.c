/* BlackOut__Fiiii (0x80024f64) */
void FUN_80024e98(int, int, int, int, int, int, int, int, int);

void BlackOut(int x, int y, int w, int h) {
	FUN_80024e98(x, y, x + w, y, x + w, y + h, x, y + h, 0x40000000);
}
