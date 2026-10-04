/* Video_SortAndMerge__Fv (0x80069164) */
struct SHighlight { short FromFrame; short ToFrame; int Score; };
struct SVideoInfo {
	char pad0[0x1c];
	unsigned long NumFrames;
	char pad1[0x30];
	SHighlight Highlights[5];
	char pad2[0x48];
};
extern SVideoInfo DAT_800bf318[2];
void Video_SortAndMerge(void)
{
	SHighlight TempHL[5];
	SHighlight NullHL;
	NullHL.FromFrame = NullHL.ToFrame = NullHL.Score = 0;
	{
		int i;
		for (i = 0; i < 5; i++) {
			TempHL[i] = NullHL;
			{
				int BestFrom = 0x7fffffff;
				int BestIndex = -1;
				int j;
				for (j = 0; j < 5; j++) {
					if (DAT_800bf318[0].Highlights[j].ToFrame >= DAT_800bf318[0].NumFrames)
						DAT_800bf318[0].Highlights[j].ToFrame = DAT_800bf318[0].NumFrames - 1;
					if (DAT_800bf318[0].Highlights[j].Score && DAT_800bf318[0].Highlights[j].FromFrame < BestFrom) {
						BestFrom = DAT_800bf318[0].Highlights[j].FromFrame;
						BestIndex = j;
					}
				}
				if (BestIndex != -1) {
					TempHL[i] = DAT_800bf318[0].Highlights[BestIndex];
					DAT_800bf318[0].Highlights[BestIndex].Score = 0;
				}
			}
		}
	}
	{
		int i;
		for (i = 4; i > 0; i--) {
			if (TempHL[i].FromFrame <= TempHL[i - 1].ToFrame + 15 && TempHL[i].FromFrame > TempHL[i - 1].FromFrame) {
				if (TempHL[i - 1].ToFrame < TempHL[i].ToFrame)
					TempHL[i - 1].ToFrame = TempHL[i].ToFrame;
				TempHL[i - 1].Score += TempHL[i].Score;
				TempHL[i] = NullHL;
			}
		}
	}
	{
		int i;
		int n = 0;
		for (i = 0; i < 5; i++) {
			DAT_800bf318[0].Highlights[i] = NullHL;
			if (TempHL[i].Score) {
				DAT_800bf318[0].Highlights[n] = TempHL[i];
				n++;
			}
		}
	}
}
