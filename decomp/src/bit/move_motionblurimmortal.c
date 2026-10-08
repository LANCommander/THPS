/* Move__19CMotionBlurImmortal (0x80029bdc) */
void __apl__7CVectorRC7CVector(char *, char *);
int Shrink__7CFT4Biti(char *, int);
int Fade__7CFT4Biti(char *, int);
void IncFrameWithWrap__7CFT4Bit(char *);

void Move__19CMotionBlurImmortal(char *t) {
	__apl__7CVectorRC7CVector(t + 0x18, t + 0x24);

	if (!Shrink__7CFT4Biti(t, 0) && !Fade__7CFT4Biti(t, 0))
		IncFrameWithWrap__7CFT4Bit(t);
}
