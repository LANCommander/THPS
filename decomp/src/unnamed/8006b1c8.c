/* FUN_8006b1c8 (0x8006b1c8) */
typedef struct {
	short m[3][3];
	int t[3];
} MATRIX;

typedef struct {
	int vx, vy, vz, pad;
} VECTOR;

typedef struct {
	unsigned int Style;
	VECTOR Position;
	VECTOR Focus;
	int Distance;
	int Height;
	short Angles[4];
	MATRIX Transform;
} SCamera;

typedef struct {
	char pad[12];
	short m;
} SViewport;

extern SCamera DAT_800c119c;
extern SViewport DAT_800bf614;

void FUN_8008b238(MATRIX *);
MATRIX *FUN_80093100(MATRIX *, VECTOR *);
void M3dInit_SetFoggingParams__FiiUi(int, int, unsigned int);

SViewport *FUN_8006b1c8(void) {
	DAT_800bf614.m = 3413;
	FUN_8008b238(&DAT_800c119c.Transform);

	DAT_800c119c.Position.vx = 0;
	DAT_800c119c.Position.vy = 0;
	DAT_800c119c.Position.vz = -200;
	FUN_80093100(&DAT_800c119c.Transform, &DAT_800c119c.Position);
	M3dInit_SetFoggingParams__FiiUi(10, 6000, 2048);
	return &DAT_800bf614;
}
