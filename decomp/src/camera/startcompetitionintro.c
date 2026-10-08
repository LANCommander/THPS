/* StartCompetitionIntro__7CCamera (0x8007c814) */
void FUN_8007657c(void *c);

void StartCompetitionIntro(char *c) {
	*(int *)(c + 0x5dc) = 0;
	*(int *)(c + 0x584) = 23;
	FUN_8007657c(c);
}
