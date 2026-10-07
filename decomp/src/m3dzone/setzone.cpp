/* M3dZone_SetZone__FiPUi (0x8008301c) */
/* C++ (M3DZONE.CPP). Exact demo twin; locals from its MAIN.SYM. Reads a zone header from the packed
   PSX data (box, cell counts), then each cell's item list, relocating item indices into pointers
   into the environment's PSX item table.
   Levers: the two short reads use g++'s cast-as-lvalue post-increment (`*((short *)pPack)++`),
   which keeps retail's unfolded pointer copies; `(DAT_800bf7bc + i)->pPSX` and the sized `[1]`
   extern give retail's loop-preheader order. */
typedef unsigned int uint;
struct Item;
struct SZone {
	int Active;
	int xL;
	int zL;
	int xH;
	int zH;
	int CellSize;
	int pad18;
	short NumX;
	short NumZ;
	Item *Cells[20][20];
};
struct SEnvPSX {
	uint *pPSX;
	char pad[60];
};
extern SZone DAT_800c4e0c[2];
extern int DAT_800d1ed0[1];
extern SEnvPSX DAT_800bf7bc[];

void M3dZone_SetZone(int EnvIndex, uint *pPack)
{
	{
		int Z;
		DAT_800c4e0c[EnvIndex].xL = *pPack++;
		DAT_800c4e0c[EnvIndex].zL = *pPack++;
		DAT_800c4e0c[EnvIndex].xH = *pPack++;
		DAT_800c4e0c[EnvIndex].zH = *pPack++;
		DAT_800c4e0c[EnvIndex].NumX = *((short *)pPack)++;
		DAT_800c4e0c[EnvIndex].NumZ = *((short *)pPack)++;
		DAT_800c4e0c[EnvIndex].Active = 1;
		DAT_800c4e0c[EnvIndex].CellSize = (DAT_800c4e0c[EnvIndex].xH - DAT_800c4e0c[EnvIndex].xL) / DAT_800c4e0c[EnvIndex].NumX;
		for (Z = 0; Z < DAT_800c4e0c[EnvIndex].NumZ; Z++) {
			int X;
			for (X = 0; X < DAT_800c4e0c[EnvIndex].NumX; X++) {
				int count;
				uint *pPSX;
				pPack += 2;
				count = *pPack++;
				DAT_800c4e0c[EnvIndex].Cells[X][Z] = (Item *)pPack;
				pPSX = (DAT_800bf7bc + DAT_800d1ed0[EnvIndex])->pPSX;
				while (count-- > 0) {
					*pPack = (uint)pPSX + 12 + *pPack * 36;
					pPack++;
				}
				pPack++;
			}
		}
	}
}
