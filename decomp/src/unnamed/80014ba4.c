/* FUN_80014ba4 (0x80014ba4) */
typedef struct {
	int a, b;
} T;

typedef struct {
	char pad[44];
	short s[5];
} H;

extern int DAT_800a42f4[];

typedef struct {
	char pad[28];
	int f;
	char pad2[48];
	T t[5];
} S;

extern S DAT_800bf318;

char *FileIO_Open__FPCc(void);
char *Mem_NewX__FUiii(char *a, int b, int c);
void FileIO_Load__FPv(char *a);
void FileIO_Sync__Fv(void);
void Mem_Delete__FPv(char *a);

short FUN_80014ba4(void) {
	H *h;
	char *b;
	int i;

	b = Mem_NewX__FUiii(FileIO_Open__FPCc(), 1, 1);

	if (b) {
		FileIO_Load__FPv(b);
		FileIO_Sync__Fv();
	}

	h = (H *)(b + 512);
	DAT_800a42f4[0] = h->s[0];
	DAT_800a42f4[1] = h->s[1];
	DAT_800a42f4[2] = h->s[2];
	DAT_800a42f4[3] = h->s[3];
	DAT_800a42f4[4] = h->s[4];
	DAT_800bf318.f = *(int *)(b + 512);

	for (i = 0; i < 5; i++)
		DAT_800bf318.t[i] = ((T *)(b + 516))[i];

	Mem_Delete__FPv(b);
	return h->s[0];
}
