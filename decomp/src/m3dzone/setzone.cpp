/* M3dZone_SetZone__FiPUi (0x8008301c) */
/* C++ (M3DZONE.CPP). Exact demo twin; locals from its MAIN.SYM. Reads a zone header from the packed
   PSX data (box, cell counts), then each cell's item list, relocating item indices into pointers
   into the environment's PSX item table.
   Levers: the two short reads use g++'s cast-as-lvalue post-increment (`*((short *)pPack)++`),
   which keeps retail's unfolded pointer copies; `(PSXRegion_14 + i)->pPSX` and the sized `[1]`
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

extern SZone Zones[2];
extern int EnvRegions[1];
extern SEnvPSX PSXRegion_14[];

void M3dZone_SetZone(int EnvIndex, uint *pPack) {
	{
		int Z;

		Zones[EnvIndex].xL = *pPack++;
		Zones[EnvIndex].zL = *pPack++;
		Zones[EnvIndex].xH = *pPack++;
		Zones[EnvIndex].zH = *pPack++;
		Zones[EnvIndex].NumX = *((short *)pPack)++;
		Zones[EnvIndex].NumZ = *((short *)pPack)++;
		Zones[EnvIndex].Active = 1;
		Zones[EnvIndex].CellSize =
		    (Zones[EnvIndex].xH - Zones[EnvIndex].xL) / Zones[EnvIndex].NumX;

		for (Z = 0; Z < Zones[EnvIndex].NumZ; Z++) {
			int X;

			for (X = 0; X < Zones[EnvIndex].NumX; X++) {
				int count;
				uint *pPSX;

				pPack += 2;
				count = *pPack++;
				Zones[EnvIndex].Cells[X][Z] = (Item *)pPack;
				pPSX = (PSXRegion_14 + EnvRegions[EnvIndex])->pPSX;

				while (count-- > 0) {
					*pPack = (uint)pPSX + 12 + *pPack * 36;
					pPack++;
				}

				pPack++;
			}
		}
	}
}
