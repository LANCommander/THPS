/* SetTint__7CRibbonUcUcUc (0x8002a0e8) */
void SetTint__7CFT4BitUcUcUc(void *, unsigned char, unsigned char, unsigned char);

void SetTint__7CRibbonUcUcUc(char *t, unsigned char r, unsigned char g, unsigned char b) {
	int i;

	for (i = 0; i < *(int *)(t + 0x48); i++)
		SetTint__7CFT4BitUcUcUc((*(void ***)(t + 0x5c))[i], r, g, b);
}
