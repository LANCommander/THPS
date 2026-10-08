/* SetVariable__6CBaddyUs (0x80040ccc) */
typedef struct {
	unsigned short us0;
	char _2[2];
	int f4, f8, f12;
	char _10[6];
	unsigned short us22;
	char _18[3];
	unsigned char b27;
	char _1c[196];
	unsigned short us224;
	char _e2[4];
	unsigned short us230;
	char _e8[104];
	int f336;
	char _154[75];
	unsigned char b415, b416;
	char _1a1[7];
	unsigned short us424;
	char _1aa[4];
	unsigned short *pc;
} Bad;

int GetScriptValue__6CBaddy(Bad *);
int Spool_GetModel__FUii(unsigned, int);

void SetVariable__6CBaddyUs(Bad *t, unsigned short cmd) {
	unsigned *wp;
	unsigned *w2;
	char *d;
	unsigned dv, dw;
	unsigned short *p;
	int r;
	unsigned short v, u, x;

	switch (cmd) {
		case 8501:
			w2 = (unsigned *)(((int)t->pc + 3) & -4);
			*(unsigned *)((char *)t + 512) = *w2;
			t->pc = (unsigned short *)(w2 + 1);
			break;
		case 8495:
			wp = (unsigned *)(((int)t->pc + 3) & -4);
			t->us22 = Spool_GetModel__FUii(*wp, t->b27);
			t->pc = (unsigned short *)(wp + 1);
			break;
		case 8512:
			t->f4 = (short)GetScriptValue__6CBaddy(t) << 12;
			break;
		case 8513:
			t->f8 = (short)GetScriptValue__6CBaddy(t) << 12;
			break;
		case 8514:
			t->f12 = (short)GetScriptValue__6CBaddy(t) << 12;
			break;
		case 8497:
			x = *t->pc++;

			if (x)
				t->us0 |= 8;
			else
				t->us0 &= ~8;

			break;
		case 8494:
			t->us424 = *t->pc++;
			break;
		case 8492:
			t->b416 = *(unsigned char *)t->pc;
			t->pc++;
			break;
		case 8493:
			t->b415 = *(unsigned char *)t->pc;
			t->pc++;
			break;
		case 8448:
			t->us230 = *t->pc++;
			break;
		case 8449:
			t->us224 = *t->pc++;
			break;
		case 8485:
			p = t->pc;
			x = *p++;
			t->pc = p;
			u = *p++;
			d = (char *)t;
			d += x * 2;
			*(unsigned short *)(d + 468) = u;
			t->pc = p;
			break;
		case 8468:
			*(unsigned short *)((char *)t + 504) = *t->pc++;
			break;
		case 8469:
			*(unsigned short *)((char *)t + 506) = *t->pc++;
			break;
		case 8480:
			dv = *t->pc++;
			r = GetScriptValue__6CBaddy(t);
			dv &= 255;
			dv <<= 1;
			dw = (unsigned)t + dv;
			*(unsigned short *)(dw + 492) = r;
			break;
		case 8481:
			t->f336 = *(short *)t->pc++;
			break;
		case 8482:
			*(unsigned short *)((char *)t + 488) = *t->pc++;
			break;
	}
}
