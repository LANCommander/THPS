/* FUN_8004ba34 (0x8004ba34) */
int nko_flag;
int keyon_queue;
int keyoff_queue;
int voiceon_flag;
int exp_flag;
int loop_flag;
int voicefree_flag;
char reverb_changed;

void FUN_800947e4(int a, int b);

void FUN_8004ba34(void) {
	FUN_800947e4(0, -1);

	nko_flag = 0;
	keyon_queue = 0;
	keyoff_queue = 0;
	voiceon_flag = 0;
	exp_flag = 0;
	loop_flag = 0;
	voicefree_flag = 0xffffff;
	reverb_changed = 0;
}
