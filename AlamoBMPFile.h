
#ifndef _ALAMO_BMP_FILE_H_
#define _ALAMO_BMP_FILE_H_

#include "AlamoImageFileBase.h"

namespace Alamo
{
	class alaBMPFile :public alaImageFileBase
	{
	public:

		alaBMPFile();
		alaBMPFile(alaString fileName);
		~alaBMPFile();
		//Override
		bool Load(alaString fileName);
		bool Render();
		int Height();
		int Width();
		alaRawPixelData * Pixel_Data();
		//-------------------

		int Image_Size();

		alaString File_Name();

	private:
		BITMAPINFOHEADER bitmapInfoHeader;
		alaRawPixelData *bitmapImage;
		alaString fileName;

	};


}
#endif /*_ALAMO_BMP_FILE_H_*/
