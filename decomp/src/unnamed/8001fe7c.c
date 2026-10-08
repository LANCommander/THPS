/* FUN_8001fe7c (0x8001fe7c) */
void FUN_8001fe7c(char *p) {
	char *vt;

	void (*fn)(char *);
	*(unsigned short *)p |= 65;
	vt = *(char **)(p + 72);
	fn = *(void (**)(char *))(vt + 60);
	fn(p + *(short *)(vt + 56));
}
