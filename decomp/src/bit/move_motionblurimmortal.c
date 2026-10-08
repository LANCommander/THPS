/* Move__19CMotionBlurImmortal (0x80029bdc) */
#include "names.h"
void __apl__7CVectorRC7CVector(char *, char *);
int CFT4Bit_Shrink(char *, int);
int CFT4Bit_Fade(char *, int);
void CFT4Bit_IncFrameWithWrap(char *);

void CMotionBlurImmortal_Move(char *t) {
	__apl__7CVectorRC7CVector(t + 0x18, t + 0x24);

	if (!CFT4Bit_Shrink(t, 0) && !CFT4Bit_Fade(t, 0))
		CFT4Bit_IncFrameWithWrap(t);
}
