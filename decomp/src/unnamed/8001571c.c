/* FUN_8001571c (0x8001571c) */
struct B {
	int w[628];
};

extern int DAT_800a5880[];
extern char DAT_800a58bc[];

int DAT_800d1398;

int SyncToGoodState__Fv(void);
int Mem_NewX__FUiii(int, int, int);
void Card_SetSelectedFile__FPc(char *);
int Card_Load__F9EFileTypePUlT1(int, int, int);
void FUN_8004d5d0(int);

void FUN_8001571c(void) {
	struct B buf;
	int i, p;
	char *name;
	int *flag;

	DAT_800d1398 = 0;

	if (SyncToGoodState__Fv() == 0) {
		i = 0;
		name = DAT_800a58bc;
		flag = DAT_800a5880;

		do {
			if (*flag == 0) {
				p = Mem_NewX__FUiii(3200, 1, 1);
				Card_SetSelectedFile__FPc(name);

				if (Card_Load__F9EFileTypePUlT1(0, p, 0) == 0) {
					buf = *(struct B *)(p + 640);

					if (((unsigned short *)&buf)[1047] >= DAT_800d1398)
						DAT_800d1398 = ((unsigned short *)&buf)[1047] + 1;
				}

				FUN_8004d5d0(p);
			}

			name += 40;
			i++;
			flag++;
		} while (i < 15);
	}
}
