/* OutOfBounds__10CPanelData (0x8006eba4) */
int Redbook_Rnd__Fi(int a);
void FUN_8001e014(char *p);

void OutOfBounds__10CPanelData(char *p) {
	*(int *)(p + 428) = Redbook_Rnd__Fi(4) + 1;
	FUN_8001e014(p + 432);
}
