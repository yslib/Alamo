
#ifndef _ALAMO_SCREEN_OBJECT_H_
#define _ALAMO_SCREEN_OBJECT_H_
#include "AlamoType.h"

namespace Alamo
{
	class alaScreenObject
	{
	public:
		virtual ~alaScreenObject() {}

		virtual alaString Type() = 0
		{
			return ("alaScreenObject");
		}

		virtual bool Render() = 0
		{
			return (false);
		}
	};
}

#endif /*_ALAMO_SCREEN_OBJECT_H_*/