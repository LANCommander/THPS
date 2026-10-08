/* Move__11CSmokeTrail (0x8002a49c) */
int Fade__7CFT4Biti(void *, int);
void Die__4CBit(char *);

void Move__11CSmokeTrail(char *t) {
	int i;
	int dead = 1;

	if (*(int *)(t + 0x60)) {
		for (i = 0; i < *(int *)(t + 0x48); i++)
			if (!Fade__7CFT4Biti((*(void ***)(t + 0x5c))[i], 0))
				dead = 0;

		if (dead)
			Die__4CBit(t);
	}
}
