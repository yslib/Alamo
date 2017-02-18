
#ifndef _ALAMO_LEVEL_BASE_H_
#define _ALAMO_LEVEL_BASE_H_

#include "AlamoType.h"

namespace Alamo
{
	class alaLevelFileBase
	{
	public:
		enum alaLevelFileFormat
		{
			ALALFF_XML,
			ALALFF_SIMPLEBINARY
		};

	public:
		virtual bool Load(alaString fileName)
		{
			return (true);
		}
	};
}

#endif/*_ALAMO_LEVEL_H_*/