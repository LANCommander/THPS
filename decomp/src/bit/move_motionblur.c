/* Move__11CMotionBlur (0x80029b2c) */
void __apl__7CVectorRC7CVector(char *, char *);
int Shrink__7CFT4Biti(char *, int);
int Fade__7CFT4Biti(char *, int);
void IncFrameWithWrap__7CFT4Bit(char *);

void Move__11CMotionBlur(char *t) {
	__apl__7CVectorRC7CVector(t + 0x18, t + 0x24);

	if (!Shrink__7CFT4Biti(t, 1) && !Fade__7CFT4Biti(t, 1))
		IncFrameWithWrap__7CFT4Bit(t);
}
