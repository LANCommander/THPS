/* CalcScreenNormal__FP11SCalcBufferRiT1i (0x8002dad8) */
struct SCalcBuffer {
	short x, y;
	char pad[0x14];
	int Bad;
};
void CalcScreenNormal(SCalcBuffer *pBuf, int &UnitX, int &UnitY, int ClosenessLimit)
{
	if (pBuf[0].Bad == 0 && pBuf[1].Bad == 0) {
		int xa, ya, xb, yb, dx, dy, l;
		xa = pBuf[0].x;
		ya = pBuf[0].y;
		xb = pBuf[1].x;
		yb = pBuf[1].y;
		dx = xb - xa;
		dy = yb - ya;
		dx = (dx * 320) / 512;
		UnitX = dy;
		UnitY = -dx;
		if (dx < 0) dx = -dx;
		if (dy < 0) dy = -dy;
		if (dy < dx)
			l = dx + dy / 2;
		else
			l = dy + dx / 2;
		if (l >= ClosenessLimit) {
			UnitX = (UnitX << 6) / l;
			UnitY = (UnitY << 6) / l;
			UnitX = (UnitX << 9) / 320;
			return;
		}
	}
	UnitX = UnitY = 0;
}
