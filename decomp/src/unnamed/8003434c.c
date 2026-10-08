/* FUN_8003434c (0x8003434c) */
void FUN_8002f980(char *p, int a, int b);
void FUN_8002f1a0(char *p);
void FUN_8002fcdc(char *p, int a, int b);

void FUN_8003434c(char *p) {
	int v;

	if (*(int *)(p + 1844) == 2) {
		FUN_8002f980(p, 1, 3707);
	} else {
		FUN_8002f980(p, 1, 3713);
		FUN_8002f1a0(p);

		v = *(int *)(p + 856);
		*(int *)(p + 808) = 0;
		*(int *)(p + 812) = 0;
		*(int *)(p + 860) = 0;
		*(int *)(p + 1856) = 1;

		if (v == 0) {
			*(int *)(p + 336) = 0x10000;

			if (*(int *)(p + 1852))
				FUN_8002fcdc(p, 26, 3730);
			else
				FUN_8002fcdc(p, 27, 3732);
		}
	}
}
