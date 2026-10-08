/* MoveTo__9CPlatformR7CVector (0x8003ebdc) */
typedef struct {
	int x, y, z;
} V;

int __ne__7CVectorRC7CVector(V *, V *);

void MoveTo__9CPlatformR7CVector(char *t, V *v) {
	if (__ne__7CVectorRC7CVector((V *)(t + 0x204), v)) {
		*(V *)(t + 0x204) = *v;
		*(int *)(t + 0x1ac) |= 1;
	}
}
