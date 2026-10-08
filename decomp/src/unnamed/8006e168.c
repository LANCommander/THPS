/* FUN_8006e168 (0x8006e168) */
void FUN_8006e7fc(char *p);
void Video_HighlightStart__FP6CBruce(char *p);

void FUN_8006e168(char *p) {
	FUN_8006e7fc(p + 2340);

	*(int *)(p + 3548) = 0;
	Video_HighlightStart__FP6CBruce(p);
}
