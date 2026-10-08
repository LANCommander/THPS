/* FUN_8003434c (0x8003434c) */
void StateTransition__6CBruce13EPhysicsStatei(char *p, int a, int b);
void FUN_8002f1a0(char *p);
void Debug_RunAnim__6CBruceii(char *p, int a, int b);

void FUN_8003434c(char *p) {
	int v;

	if (*(int *)(p + 1844) == 2) {
		StateTransition__6CBruce13EPhysicsStatei(p, 1, 3707);
	} else {
		StateTransition__6CBruce13EPhysicsStatei(p, 1, 3713);
		FUN_8002f1a0(p);

		v = *(int *)(p + 856);
		*(int *)(p + 808) = 0;
		*(int *)(p + 812) = 0;
		*(int *)(p + 860) = 0;
		*(int *)(p + 1856) = 1;

		if (v == 0) {
			*(int *)(p + 336) = 0x10000;

			if (*(int *)(p + 1852))
				Debug_RunAnim__6CBruceii(p, 26, 3730);
			else
				Debug_RunAnim__6CBruceii(p, 27, 3732);
		}
	}
}
