#include "libforest/ReconfigBATs.h"
#include "libultra/gettime.h"
#include <dolphin/os.h>
#include <string.h>

//.bss
BOOL fakemain_check;
OSTime InitialStartTime;

//local prototypes
void version_check(void);

void version_check(void) {
    if (strcmp("08May2003Patch3", "08May2003Patch3")) {
        while (1) { ; }
    }
}

int main(void) {
    version_check();
    ReconfigBATs();
    if (fakemain_check) {
        return -1;
    }
    fakemain_check = TRUE;
    InitialStartTime = osGetTime();
    OSInit();
    OSInitAlarm();

    return 0;
}