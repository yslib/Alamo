
#ifndef _ALAMO_DEBUG_H_
#define _ALAMO_DEBUG_H_
//#include "Alamo.h"
#ifndef DEBUGOFF
#define ASSERT(expr) assert(expr)

#else 

#define ASSERT(expr)


#endif // !DEBUGOFF


#endif // !_ALAMO_DEBUG_H_
