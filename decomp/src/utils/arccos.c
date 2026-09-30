/* Utils_ArcCos__Fi (0x800480f8) */
typedef struct { short s, c; } SC;
extern SC DAT_800c9670[];
int Utils_ArcCos(int c){ int neg = 0, step, i, v; if (c < 0) { c = -c; neg = 1; } step = 256; i = 512; for (;;) { v = DAT_800c9670[i].c; if (c < v) i += step; else if (v == c) break; else i -= step; step >>= 1; if (!step) break; } if (neg) return 2048 - i; return i; }
