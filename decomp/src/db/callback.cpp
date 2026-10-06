/* Db_CallBack__Fv (0x80048e40) */
/* C++ (DB.CPP). Demo twin; locals from its MAIN.SYM. Draw-sync callback for the two display
   buffers: once the GPU is idle, any buffer waiting to be drawn is marked done. */
struct SDb {
	char pad0[120];
	int Pending;               /* 120 */
	int Done;                  /* 124 */
	char pad80[32940 - 128];
};
extern SDb DAT_800a891c[2];
extern "C" int FUN_8008c468(int);

void Db_CallBack()
{
	if (!DAT_800a891c[0].Pending && !DAT_800a891c[1].Pending)
		return;
	if (!FUN_8008c468(1)) {
		int i;
		for (i = 0; i < 2; i++) {
			if (DAT_800a891c[i].Pending) {
				DAT_800a891c[i].Pending = 0;
				DAT_800a891c[i].Done = 1;
			}
		}
	}
}
