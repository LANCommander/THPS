/* Trick_PlayerInit__6CBruceUs (0x8002f178) */
#include "names.h"
extern void Panel_PlayerInit(unsigned short, void *);

void Trick_PlayerInit(void *b, unsigned short n) {
	Panel_PlayerInit(n, b);
}
