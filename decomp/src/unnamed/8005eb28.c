/* FUN_8005eb28 (0x8005eb28) */
typedef struct { int a, b, c, d; } Q;
typedef struct { char pad[288]; Q q[1]; } D;
extern D DAT_800a4118;
extern Q DAT_800bf260[];
void FUN_8005eb28(int i)
{
	DAT_800a4118.q[i].a = DAT_800bf260[i].a;
	DAT_800a4118.q[i].c = DAT_800bf260[i].c;
	DAT_800a4118.q[i].b = DAT_800bf260[i].b;
	DAT_800a4118.q[i].d = DAT_800bf260[i].d;
}
