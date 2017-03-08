#include "Alamo.h"
#include "AlamoApp.h"
#include "AlamoTexture.h"
#include "AlamoBMPFile.h"

namespace Alamo
{
	

	alaTexture::alaTextureData::alaTextureData()
	{
		texelData = NULL;
		totalBytes = 0;
		texelData = NULL;
		totalBytes = 0;
		totalTexels = 0;
		bytesPerTexel = 0;
		height = 0;
		width = 0;
		textureID = 0;
		transparentColor = ALAMO_TEX_NO_TRANSPARENT_COLOR;
	}

	alaTexture::alaTextureData::~alaTextureData()
	{
		Cleanup_Texture();
	}

	bool alaTexture::alaTextureData::Load_From_BMP(alaString fileName)
	{
		bool ok = true;

		alaRawPixelData * td;

		alaBMPFile imageFile;

		ok = imageFile.Load(fileName);

		if (ok)
		{
			alaRawPixelData swap;
			td = imageFile.Pixel_Data();


			//convert bgr to rgb 
			for (int i = 0; i < imageFile.Image_Size(); i += 3)
			{
				swap = td[i];
				td[i] = td[i + 2];
				td[i + 2] = swap;
			}

			bytesPerTexel = 4;

			totalTexels = imageFile.Image_Size() / 3;

			totalBytes = totalTexels * 4;
			texelData = new alaRawPixelData[totalBytes];

			if (texelData != NULL)
			{
				for (int i = 0, j = 0; i < totalBytes; i += 4, j += 3)
				{
					texelData[i] = td[j];       // Red
					texelData[i + 1] = td[j + 1];   // Green.
					texelData[i + 2] = td[j + 2];   // Blue.



					if (alaColorRGB(texelData[i],
						texelData[i + 1],
						texelData[i + 2]) == transparentColor)
					{
						texelData[i + 3] = 0;
					}

					else
					{
						texelData[i + 3] = 255;
					}
				}
			}
			else
			{
				ok = false;
				theApp.App_Error(ALAES_OUT_OF_MEMORY);
			}

		}

		if (ok)
		{
			height = imageFile.Height();
			width = imageFile.Width();
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			GLenum en = glGetError();
			glGenTextures(1, &textureID);
			en = glGetError();
			assert(en == GL_NO_ERROR);
		}
		
		return ok;
	}

	bool alaTexture::alaTextureData::Load_From_TGA(alaString fileName)
	{
		bool ok = true;
		return ok;
	}

	int alaTexture::alaTextureData::Total_Bytes()
	{
		return totalBytes;
	}

	int alaTexture::alaTextureData::Total_Texels()
	{
		return totalTexels;
	}

	int alaTexture::alaTextureData::Bytes_Per_Texel()
	{
		return bytesPerTexel;
	}

	int alaTexture::alaTextureData::Height()
	{
		return height;
	}

	int alaTexture::alaTextureData::Width()
	{
		return width;
	}

	void alaTexture::alaTextureData::Transparent_Color(alaColorRGB color)
	{
		transparentColor = color;
	}

	alaColorRGB alaTexture::alaTextureData::Transparent_Color()
	{
		return transparentColor;
	}

	bool alaTexture::alaTextureData::Pre_Render()
	{
		bool ok = true;
		glBindTexture(GL_TEXTURE_2D, textureID);
		ok = (glGetError() == GL_NO_ERROR);

		if (ok == true)
		{
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					4,
					width,
					height,
					0,
					GL_RGBA,
					GL_UNSIGNED_BYTE,
					texelData);

				ok = glGetError() == GL_NO_ERROR;
		}
		return ok;
	}

	void alaTexture::alaTextureData::Cleanup_Texture()
	{
		if (texelData != NULL)
		{
			delete[] texelData;
			texelData = NULL;
		}

		totalBytes = 0;
		totalTexels = 0;
		bytesPerTexel = 0;
		height = width = 0;

		glDeleteTextures(1, &textureID);
	}

	alaTexture::alaTexture() :data(new alaTextureData)
	{

		if (!data)
		{
			alaError err(ALAES_OUT_OF_MEMORY);
			throw alaError(ALAES_OUT_OF_MEMORY);
		}
	}

	alaTexture::~alaTexture()
	{

	}

	bool alaTexture::Load_From_BMP(alaString fileName)
	{
		assert(!data == false);
		return (data->Load_From_BMP(fileName));
	}

	bool alaTexture::Load_From_TGA(alaString fileName)
	{
		assert(!data == false);
		return (data->Load_From_TGA(fileName));
	}

	int alaTexture::Total_Bytes()
	{
		assert(!data == false);
		return (data->Total_Bytes());
	}

	int alaTexture::Total_Texels()
	{
		assert(!data == false);
		return data->Total_Texels();
	}

	int alaTexture::Bytes_Per_Texel()
	{
		assert(!data == false);
		return data->Bytes_Per_Texel();
	}

	int alaTexture::Height()
	{
		assert(!data == false);
		return data->Height();
	}

	int alaTexture::Width()
	{
		assert(!data == false);
		return data->Width();
	}

	void alaTexture::Transparent_Color(alaColorRGB color)
	{
		assert(!data == false);
		data->Transparent_Color(color);
	}

	alaColorRGB alaTexture::Transparent_Color()
	{
			assert(!data == false);
		return data->Transparent_Color();
	}

	bool alaTexture::Pre_Render()
	{
		assert(!data == false);
		return data->Pre_Render();
	}

}