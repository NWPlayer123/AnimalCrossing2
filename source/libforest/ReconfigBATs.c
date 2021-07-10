#include "libforest/ReconfigBATs.h"
#include <dolphin/os.h>

void Config24MB(void);
void Config48MB(void);

#ifdef __MWERKS__
asm void Config24MB(void) {
	mfmsr   r3
	rlwinm  r3, r3, 0, 28, 26
	mtmsr   r3
	isync
	li      r7, 0
	lis     r4, 0
	addi    r4, r4, 2
	lis     r3, -0x8000
	addi    r3, r3, 0x1FF
	lis     r6, 0x100
	addi    r6, r6, 2
	lis     r5, -0x7F00
	addi    r5, r5, 0xFF
	isync
	mtspr   dbat0u, r7
	mtspr   dbat0l, r4
	mtspr   dbat0u, r3
	isync
	mtspr   dbat2u, r7
	mtspr   dbat2l, r6
	mtspr   dbat2u, r5
	isync
	mfmsr   r3
	ori     r3, r3, 0x10
	mtmsr   r3
	isync
	blr
}

asm void Config48MB(void) {
	mfmsr   r3
	rlwinm  r3, r3, 0, 28, 26
	mtmsr   r3
	isync
	li      r7, 0
	lis     r4, 0
	addi    r4, r4, 2
	lis     r3, -0x8000
	addi    r3, r3, 0x3FF
	lis     r6, 0x200
	addi    r6, r6, 2
	lis     r5, -0x7E00
	addi    r5, r5, 0x1FF
	isync
	mtspr   dbat0u, r7
	mtspr   dbat0l, r4
	mtspr   dbat0u, r3
	isync
	mtspr   dbat2u, r7
	mtspr   dbat2l, r6
	mtspr   dbat2u, r5
	isync
	mfmsr   r3
	ori     r3, r3, 0x10
	mtmsr   r3
	isync
	blr
}
#endif

void ReconfigBATs(void) {
	BOOL level;
	level = OSDisableInterrupts();
	if (OSGetConsoleSimulatedMemSize() <= 0x1800000) {
		Config48MB();
	} else {
		Config24MB();
	}
	OSRestoreInterrupts(level);
}