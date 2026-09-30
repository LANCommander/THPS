/* EntryOff__5CMenuPCc (0x800168b4) */
int FindEntry__5CMenuPCc(char*, const char*);
void EntryOff(char *m, const char *s){ m += FindEntry__5CMenuPCc(m, s)*0x18; m[0x25] = 0; }
