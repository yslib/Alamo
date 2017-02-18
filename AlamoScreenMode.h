
#ifndef _ALAMO_SCREEN_MODE_H_
#define _ALAMO_SCREEN_MODE_H_

#include <vector>

namespace Alamo {
	enum alaScreenResolution
	{
		ALASR_UNKNOWN = 0,
		ALASR_640X480X24,
		ALASR_640X480X32,
		ALASR_800X600X24,
		ALASR_800X600X32,
		ALASR_1024X768X24,
		ALASR_1024X768X32,
		ALASR_1152X864X24,
		ALASR_1152X864X32
	};

	class alaScreenMode 
	{
	public:
		alaScreenMode();

		void Add_Supported_Resolution(alaScreenResolution screenResolution);
		void Add_All();
	private:

		friend class AlamoApp;

	private:
		std::vector<alaScreenResolution> resolutions;
		int totalItems;
	};

	inline alaScreenMode::alaScreenMode()
	{
		totalItems = 0;
	}

	inline void alaScreenMode::Add_Supported_Resolution(alaScreenResolution screenResolution)
	{
		resolutions.push_back(screenResolution);
		totalItems++;
	}

	inline void alaScreenMode::Add_All()
	{
		for (int i = (int)ALASR_640X480X24; i <= (int)ALASR_1152X864X32; i++) 
		{
			Add_Supported_Resolution((alaScreenResolution)i);
		}
	}
}

#endif // !_ALAMO_SCREEN_MODE_H_