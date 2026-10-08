/* __7CFT4Bit (0x80028004) */
extern char DAT_8009f860[];

char *__4CBit(char *p);

char *__7CFT4Bit(char *p) {
	__4CBit(p);

	*(char **)(p + 68) = DAT_8009f860;
	*(short *)(p + 92) = 128;
	*(short *)(p + 94) = 400;
	*(int *)(p + 76) = 0x2c808080;
	return p;
}
