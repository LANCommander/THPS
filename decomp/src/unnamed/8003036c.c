/* FUN_8003036c (0x8003036c) */
/* Awards the combo: the sum of the queued trick scores times a multiplier from the trick count
   and the bonus level (+0x32c), halved. */
typedef struct {
	int Score;
	char pad[16];
} STrick;

typedef struct {
	char pad0[0x32c];
	int Bonus; /* 0x32c */
	char pad330[0x418 - 0x330];
	int Target;                /* 0x418 */
	char Timer[0xb20 - 0x41c]; /* 0x41c */
	STrick Tricks[19];
	char padc9c[0xcac - 0xc9c];
	int NumTricks; /* 0xcac */
} SSkater;

int FUN_8004d83c(void *);
void FUN_8004f000(int, SSkater *, int, int);

void FUN_8003036c(SSkater *s) {
	int i, sum, n, score;

	if (!s->Target || !FUN_8004d83c(s->Timer))
		return;

	sum = 0;
	n = s->NumTricks;

	for (i = 0; i < n; i++)
		sum += s->Tricks[i].Score;

	{
		int b = s->Bonus;
		int n2 = n * 2;

		if (b < 3)
			score = sum * (n2 + b) / 2;
		else {
			int t = n2 - 2;

			score = sum * (t + b * 2) / 2;
		}
	}

	if (score > 0)
		FUN_8004f000(s->Target, s, score, sum);
}
