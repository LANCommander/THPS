/* EntryOn__5CMenuPCc (0x80016878) */
int FindEntry__5CMenuPCc(char*, const char*);
void EntryOn(char *m, const char *s){ m += FindEntry__5CMenuPCc(m, s)*0x18; m[0x25] = 1; }
