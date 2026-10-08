/* FUN_80048c74 (0x80048c74) */
extern int GNumberOfPlayers;

int FUN_80048c74(void) {
	return (GNumberOfPlayers << 12) | 2;
}
