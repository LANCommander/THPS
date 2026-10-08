/* FUN_80066214 (0x80066214) */
#include "names.h"
void PREManager_spoolPRE(void);
void FileIO_Sync(void);

void FUN_80066214(void) {
	PREManager_spoolPRE();
	FileIO_Sync();
}
