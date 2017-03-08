#include "Alamo.h"
#include "AlamoBMPFile.h"
#include "AlamoApp.h"
#include <errno.h>
namespace Alamo
{

	

	static const unsigned BITMAP_ID = 0x4D42;


	alaBMPFile::alaBMPFile()
	{
		bitmapImage = NULL;
	}

	alaBMPFile::alaBMPFile(alaString fileName)
	{
		//Load the BMP file
		//...
		if (Load(fileName) != true)
		{
			theApp.App_Error(ALAES_COULD_NOT_OPEN_FILE);
		}
	}

	alaBMPFile::~alaBMPFile()
	{
		if (bitmapImage != NULL)
		{
			try {
				delete[] bitmapImage;
			}
			catch (...)
			{

			}
			bitmapImage = NULL;
		}
	}

	bool alaBMPFile::Load(alaString fn)
	{
		bool ok = true;
		FILE * bmpFile;
		BITMAPFILEHEADER bitmapFileHeader;
		int itemsRead = 0;

		bmpFile = fopen(fn.c_str(), "rb");

		if (bmpFile == NULL)
		{
			ok = false;
			theApp.App_Error(ALAES_COULD_NOT_OPEN_FILE);
			throw alaError(ALAES_COULD_NOT_OPEN_FILE,std::strerror(errno));
		}

		if (ok == true)
		{
			itemsRead = fread(&bitmapFileHeader,
				sizeof(BITMAPFILEHEADER),
				1, 
				bmpFile);
			if (itemsRead <= 0)
			{
				fclose(bmpFile);

				ok = false;
				theApp.App_Error(ALAES_COULD_NOT_OPEN_FILE);
			}
		}

		if (ok == true)
		{
			//If this is a bmp file
			if (bitmapFileHeader.bfType != BITMAP_ID)
			{
				fclose(bmpFile);

				ok = false;
				theApp.App_Error(ALAES_INVALID_FILE_TYPE);
			}
		}
		if (ok == true)
		{
			itemsRead = fread(&bitmapInfoHeader,
				sizeof(BITMAPINFOHEADER),
				1,
				bmpFile);

			if (itemsRead <= 0)
			{
				fclose(bmpFile);

				ok = false;
				theApp.App_Error(ALAES_COULD_NOT_OPEN_FILE);
			}
		}
		if (ok == true)
		{
			if (bitmapInfoHeader.biBitCount != 32)
			{
				fclose(bmpFile);

				ok = false;
				theApp.App_Error(ALAES_OUT_OF_MEMORY);
			}
		}
		if (ok == true)
		{
			bitmapInfoHeader.biSizeImage = bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight * bitmapInfoHeader.biBitCount/8;
			bitmapImage = new alaRawPixelData[bitmapInfoHeader.biSizeImage];

			if (bitmapImage == NULL)
			{
				fclose(bmpFile);

				ok = false;
				theApp.App_Error(ALAES_OUT_OF_MEMORY);
			}
		}

		if (ok == true)
		{
			fseek(bmpFile, bitmapFileHeader.bfOffBits, SEEK_SET);

			itemsRead = fread(bitmapImage, 
				1,
				bitmapInfoHeader.biSizeImage,
				bmpFile);

			if ((bitmapImage == NULL) || (itemsRead == 0))
			{
				fclose(bmpFile);

				ok = false;
				theApp.App_Error(ALAES_COULD_NOT_OPEN_FILE);
			}
			else
			{
				fileName = fn;
			}
		}

		return (ok);
	}

	bool alaBMPFile::Render()
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glDrawPixels(bitmapInfoHeader.biWidth,
			bitmapInfoHeader.biHeight,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			bitmapImage);

		return true;
	}

	int alaBMPFile::Height()
	{
		return (bitmapInfoHeader.biHeight);
	}

	int alaBMPFile::Width()
	{
		return (bitmapInfoHeader.biWidth);
	}

	alaRawPixelData * alaBMPFile::Pixel_Data()
	{
		return (bitmapImage);
	}

	int alaBMPFile::Image_Size()
	{
		return (bitmapInfoHeader.biSizeImage);
	}

	alaString alaBMPFile::File_Name()
	{
		return (fileName);
	}

}