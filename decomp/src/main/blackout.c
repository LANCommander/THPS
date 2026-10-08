/* BlackOut__Fiiii (0x80024f64) */
void Draw_Rect__Fiiiiiiiii(int, int, int, int, int, int, int, int, int);

void BlackOut(int x, int y, int w, int h) {
	Draw_Rect__Fiiiiiiiii(x, y, x + w, y, x + w, y + h, x, y + h, 0x40000000);
}
