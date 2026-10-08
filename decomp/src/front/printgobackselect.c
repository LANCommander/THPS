/* Front_PrintGoBackSelect__Fv (0x80017a08) */
void Front_PrintGoBack__Fv(void);
void Front_PrintSelect__Fv(void);

void Front_PrintGoBackSelect(void) {
	Front_PrintGoBack__Fv();
	Front_PrintSelect__Fv();
}
