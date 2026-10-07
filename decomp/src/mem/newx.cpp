/* Mem_NewX__FUiii (0x8004d068) flags=-fstructure-noalias */
/* C++ (MEM.CPP). Demo twin (retail adds the scratch heap); locals and blocks from its MAIN.SYM.
   Heap 0 is the top heap (Mem_NewTop). Heap -2 is a two-ended scratch area between
   DAT_800d1b40 and DAT_800d1b44: one block from the bottom, one from the top. The other heaps are
   first-fit free lists: a big enough block is split (its tail goes back on the free list) or
   taken whole. An allocated block's pNext holds the allocation serial number. */
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
char *DAT_800d1b40;
char *DAT_800d1b44;
SBlockHeader *DAT_800d1b48;
SBlockHeader *DAT_800d1b4c;
void Bang(unsigned char, unsigned char, unsigned char);
void AddToFreeList(SBlockHeader *, int);
void *Mem_NewTop(uint);

void *Mem_NewX(uint size, int Heap, int AssertOnFailure)
{
	SBlockHeader *pBlock;
	SBlockHeader *pLast;
	char buf[40];

	if (!Heap)
		return Mem_NewTop(size);
	DAT_800d1b58 = (DAT_800d1b58 + 1) & 0x7fffffff;
	size = (size + 3) & ~3;
	if (Heap == -2) {
		int avail;
		if (!DAT_800d1b48) {
			if (DAT_800d1b4c)
				avail = (char *)DAT_800d1b4c - DAT_800d1b40 - 8;
			else
				avail = DAT_800d1b44 - DAT_800d1b40 - 16;
			if (avail < size || avail < 0) {
				if (AssertOnFailure)
					Bang(128, 128, 0);
				return 0;
			}
			DAT_800d1b48 = (SBlockHeader *)DAT_800d1b40;
			((uint *)DAT_800d1b48)[1] = (size << 4) | 14;
			DAT_800d1b48->pNext = (SBlockHeader *)DAT_800d1b58;
			return DAT_800d1b48 + 1;
		} else {
			int total = DAT_800d1b44 - DAT_800d1b40;
			int used = DAT_800d1b48->Size + 16;
			avail = total - used;
			if (avail < size) {
				if (AssertOnFailure)
					Bang(128, 128, 0);
				return 0;
			}
			DAT_800d1b4c = (SBlockHeader *)(DAT_800d1b44 - size) - 1;
			DAT_800d1b4c->pNext = (SBlockHeader *)DAT_800d1b58;
			((uint *)DAT_800d1b4c)[1] = (size << 4) | 14;
			return DAT_800d1b4c + 1;
		}
	}
	pBlock = DAT_800d1b64[Heap];
	pLast = 0;
	while (pBlock->Size < size) {
		if (!pBlock->pNext)
			break;
		pLast = pBlock;
		pBlock = pBlock->pNext;
	}
	if (pBlock->Size < size) {
		if (AssertOnFailure) {
			if (Heap == 1)
				Bang(128, 0, 0);
			else if (Heap == 0)
				Bang(0, 0, 128);
		}
		return 0;
	}
	if (pBlock->Size > size + 8) {
		SBlockHeader *pLeftOver = (SBlockHeader *)((char *)pBlock + (size + 8));
		pLeftOver->Size = pBlock->Size - size - 8;
		if (pLast)
			pLast->pNext = pBlock->pNext;
		else
			DAT_800d1b64[Heap] = pBlock->pNext;
		((uint *)pBlock)[1] = (Heap & 15) | (size << 4);
		pBlock->pNext = (SBlockHeader *)DAT_800d1b58;
		DAT_800d1b5c[Heap] += pBlock->Size + 8;
		AddToFreeList(pLeftOver, Heap);
		if (Heap == 1) {
			if (DAT_800d1b60 >= DAT_800d1b54)
				DAT_800d1b50 = Heap;
			else
				DAT_800d1b50 = 0;
		}
		return pBlock + 1;
	}
	if (pLast)
		pLast->pNext = pBlock->pNext;
	else
		DAT_800d1b64[Heap] = pBlock->pNext;
	pBlock->Flags = Heap;
	pBlock->pNext = (SBlockHeader *)DAT_800d1b58;
	DAT_800d1b5c[Heap] += pBlock->Size + 8;
	if (Heap == 1) {
		if (DAT_800d1b60 >= DAT_800d1b54)
			DAT_800d1b50 = Heap;
		else
			DAT_800d1b50 = 0;
	}
	return pBlock + 1;
}
