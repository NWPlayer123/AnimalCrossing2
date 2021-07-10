#include "libultra/gettime.h"

//.sbss
OSTime __osTimeOffset;

OSTime osGetTime(void) {
	return __osTimeOffset + OSGetTime();
}