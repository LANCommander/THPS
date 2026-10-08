/* StartCompetitionIntro__7CCamera (0x8007c814) */
void Competition_ResetMarquee__Fv(void *c);

void StartCompetitionIntro(char *c) {
	*(int *)(c + 0x5dc) = 0;
	*(int *)(c + 0x584) = 23;
	Competition_ResetMarquee__Fv(c);
}
