/* OutOfBounds__10CPanelData (0x8006eba4) */
int Redbook_Rnd__Fi(int a);
void init__17FallingTextEffect(char *p);

void OutOfBounds__10CPanelData(char *p) {
	*(int *)(p + 428) = Redbook_Rnd__Fi(4) + 1;
	init__17FallingTextEffect(p + 432);
}
