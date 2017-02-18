
#ifndef _ALAMO_SPRITE_H_
#define _ALAMO_SPRITE_H_
#include "Alamo.h"
#include "AlamoImageFileBase.h"
#include "AlamoSpriteBase.h"
#include "AlamoType.h"
#include "AlamoTexture.h"

namespace Alamo
{

	class alaSprite :public alaSpriteBase
	{
	public:
		alaSprite();
		~alaSprite();

		bool Load_Image(alaString fileName,alaImageFileBase::alaImageFileFormat fileFormat);

		bool Render();

		int Bitmap_Height();
		int Bitmap_Width();

		void Bitmap_Transparent_Color(alaColorRGB color);

		alaColorRGB Bitmap_Transparent_Color();


		virtual alaString Type();

	private:
		//////////////////////////////////////////////////////////////////////////
		//TODO:

		alaTexture spriteImage;


		GLuint displayListID;

	};

}

#endif /*_ALAMO_SPRITE_H_*/