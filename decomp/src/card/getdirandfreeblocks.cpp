/* Card_GetDirAndFreeBlocks__Fii (0x80015164) */
struct DIRENTRY {
	char name[20];
	long attr;
	long size;
	struct DIRENTRY *next;
	long head;
	char system[4];
};
extern "C" {
extern struct DIRENTRY *firstfile(char *, struct DIRENTRY *);
extern struct DIRENTRY *nextfile(struct DIRENTRY *);
int sprintf(char *, const char *, ...);
}
int Utils_CompareStrings(const char *, const char *, unsigned int);
extern long DAT_800a5880[];
extern char DAT_800a584d[];
extern char DAT_800a5869[];
extern struct DIRENTRY DAT_800a58bc[];
extern char DAT_8009e118[];

int Card_GetDirAndFreeBlocks(int cnct, int slot)
{
	long i;
	long size = 0;
	char key[32];
	struct DIRENTRY *d;

	for (i = 0; i < 15; i++)
		DAT_800a5880[i] = 3;
	sprintf(key, DAT_8009e118, cnct, slot);
	d = DAT_800a58bc;
	i = 0;
	if (firstfile(key, d) == d)
	{
		do
		{
			size += d->size;
			if (Utils_CompareStrings(d->name, DAT_800a584d, 17))
				DAT_800a5880[i] = 0;
			else if (Utils_CompareStrings(d->name, DAT_800a5869, 17))
				DAT_800a5880[i] = 1;
			i++;
			d++;
		} while (nextfile(d) == d);
	}
	size /= 8192;
	return 15 - size;
}
