/* SetScale__7CRibboni (0x8002a178) */
void SetScale__7CFT4BitUs(void *, unsigned short);

void SetScale__7CRibboni(char *t, int s) {
	int i;

	for (i = 0; i < *(int *)(t + 0x48); i++)
		SetScale__7CFT4BitUs((*(void ***)(t + 0x5c))[i], s);
}
