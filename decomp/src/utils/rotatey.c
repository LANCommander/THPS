/* Utils_RotateY__FR7CVectorRC7CVectori (0x800479a8) */
typedef struct { int x, y, z; } V;
typedef struct { short s, c; } SC;
extern SC DAT_800c9670[];
void Utils_RotateY(V *out, V *in, int a){ SC *t; a &= 4095; t = DAT_800c9670 + a; out->x = ((in->x >> 3) * t->c + (in->z >> 3) * t->s) >> 9; out->y = in->y; out->z = ((in->z >> 3) * t->c - (in->x >> 3) * t->s) >> 9; }
