/* ReplaceTexture__FUiPc (0x800247a8) */
typedef struct {
	char pad[24];
	unsigned char *info;
	unsigned short w, h;
} STexEntry;

extern int DAT_800d1a90;
extern int DAT_800d1a8c;

STexEntry *Spool_FindTextureEntry__FUi(unsigned);
void *FileIO_Open__FPCc(char *);
char *Mem_NewX__FUiii(void *, int, int);
void FileIO_Load__FPv(char *);
void FileIO_Sync__Fv(void);
void DownloadBMP__FPciiii(char *, int, int, int, int);
void Mem_Delete__FPv(char *);

void ReplaceTexture(unsigned id, char *name) {
	STexEntry *e = Spool_FindTextureEntry__FUi(id);

	if (e) {
		unsigned char *info = e->info;
		int pal = DAT_800d1a90;
		int w = e->w;
		int h = e->h;
		int k;
		char *bmp;

		pal += info[2];
		k = DAT_800d1a8c;
		bmp = Mem_NewX__FUiii(FileIO_Open__FPCc(name), 1, 1);
		FileIO_Load__FPv(bmp);
		FileIO_Sync__Fv();
		DownloadBMP__FPciiii(bmp, w, h, k, pal);
		Mem_Delete__FPv(bmp);
	}
}
