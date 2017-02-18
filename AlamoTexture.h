#pragma once
#ifndef _ALAMO_TEXTURE_H_
#define _ALAMO_TEXTURE_H_

//#include "Alamo.h"

#include "AlamoType.h"
#include "AlamoImageFileBase.h"
#include "AlamoPtr.h"

namespace Alamo
{

	static const alaColorRGB ALAMO_TEX_NO_TRANSPARENT_COLOR = alaColorRGB(-1.0f, -1.0f, -1.0f);

	class alaTexture
	{
	public:
		alaTexture();
		~alaTexture();

		bool Load_From_BMP(alaString fileName);
		bool Load_From_TGA(alaString fileName);

		int Total_Bytes();
		int Total_Texels();
		int Bytes_Per_Texel();


		int Height();
		int Width();

		void Transparent_Color(alaColorRGB color);
		alaColorRGB Transparent_Color();

		bool Pre_Render();
	private:
		class alaTextureData
		{
		public:
			alaTextureData();
			~alaTextureData();

			bool Load_From_BMP(alaString fileName);
			bool Load_From_TGA(alaString fileName);

			int Total_Bytes();
			int Total_Texels();
			int Bytes_Per_Texel();

			int Height();
			int Width();

			void Transparent_Color(alaColorRGB color);
			alaColorRGB Transparent_Color();

			bool Pre_Render();
		private:
			void Cleanup_Texture();

		private:
			alaRawPixelData *texelData;
			int totalBytes;
			int totalTexels;
			int bytesPerTexel;

			int height, width;
			alaColorRGB transparentColor;

			unsigned textureID;

		};

	private:
		alaPtr<alaTextureData> data;

	};


}


#endif /*_ALAMO_TEXTURE_H_*/