
#ifndef _ALAMO_IMAGE_FILE_BASE_H_
#define _ALAMO_IMAGE_FILE_BASE_H_
//#include "Alamo.h"
#include "AlamoType.h"
namespace Alamo
{

	typedef unsigned char alaRawPixelData;

	class alaImageFileBase
	{
	public:
		enum alaImageFileFormat
		{
			ALAIFF_WINDOWS_BMP,
			ALAIFF_TGA
		};

	public:
		virtual bool Load(alaString fileName)
		{
			return true;
		}

		virtual int Height()
		{
			return 0;
		}

		virtual int Width()
		{
			return 0;
		}

		virtual alaRawPixelData *Pixel_Data()
		{
			return NULL;
		}

		virtual bool Render()
		{
			return true;
		}
	};

}//Namespace


#endif /*_ALAMO_IMAGE_FILE_BASE_H_*/