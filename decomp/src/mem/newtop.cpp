/* Mem_NewTop__FUi (0x8004d3a4) flags=-fstructure-noalias */
/* C++ (MEM.CPP). Fuzzy demo twin (0.69); locals from its MAIN.SYM. Allocates from the top heap:
   best-fit over the free list (the last block big enough), splitting the block's tail off if
   there's room for another header, else taking it whole. An allocated block's pNext holds the
   allocation serial number. */
#pragma interface
typedef unsigned int uint;
struct SBlockHeader {
	SBlockHeader *pNext;
	uint Flags : 4;
	uint Size : 28;
};
int DAT_800d1b50;
uint DAT_800d1b54;
uint DAT_800d1b58;
int DAT_800d1b5c[2];
uint DAT_800d1b60;
SBlockHeader *DAT_800d1b64[2];
void Bang(unsigned char, unsigned char, unsigned char);

void *Mem_NewTop(uint size)
{
	int Heap = 1;
	int AssertOnFailure = 1;
	SBlockHeader *pBlock;
	SBlockHeader *pLast;
	SBlockHeader *pChoice;
	SBlockHeader *pChoiceLast;

	DAT_800d1b58 = (DAT_800d1b58 + 1) & 0x7fffffff;
	size = (size + 3) & ~3;
	pBlock = DAT_800d1b64[Heap];
	pLast = 0;
	pChoice = pBlock;
	pChoiceLast = 0;
	while (pBlock) {
		if (pBlock->Size >= size) {
			pChoice = pBlock;
			pChoiceLast = pLast;
		}
		pLast = pBlock;
		pBlock = pLast->pNext;
	}
	if (pChoice->Size < size) {
		if (AssertOnFailure) {
			if (Heap == 1)
				Bang(128, 0, 0);
			else if (Heap == 0)
				Bang(0, 0, 128);
		}
		return 0;
	}
	if (size + 8 < pChoice->Size) {
		uint t;
		uint *pMem = (uint *)((char *)pChoice + (t = pChoice->Size + 8) - size);
		pChoice->Size = pChoice->Size - size - 8;
		pBlock = (SBlockHeader *)pMem - 1;
		pBlock->Size = size;
		pBlock->pNext = (SBlockHeader *)DAT_800d1b58;
		pBlock->Flags = 1;
		DAT_800d1b5c[Heap] += pBlock->Size + 8;
		if (Heap == 1) {
			if (DAT_800d1b60 >= DAT_800d1b54)
				DAT_800d1b50 = Heap;
			else
				DAT_800d1b50 = 0;
		}
		return pBlock + 1;
	}
	pLast = pChoiceLast;
	if (pLast)
		pLast->pNext = pChoice->pNext;
	else
		DAT_800d1b64[Heap] = pChoice->pNext;
	pChoice->Flags = 1;
	pChoice->pNext = (SBlockHeader *)DAT_800d1b58;
	DAT_800d1b5c[Heap] += pChoice->Size + 8;
	if (Heap == 1) {
		if (DAT_800d1b60 >= DAT_800d1b54)
			DAT_800d1b50 = Heap;
		else
			DAT_800d1b50 = 0;
	}
	return pChoice + 1;
}
