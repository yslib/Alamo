#include "AlamoSprite.h"
#include "AlamoApp.h"
namespace Alamo
{
	
	
	alaSprite::alaSprite()
	{
		displayListID = 0;
	}

	alaSprite::~alaSprite()
	{
		glDeleteLists(displayListID, 1);
	}

	alaColorRGB alaSprite::Bitmap_Transparent_Color()
	{
		//return spriteImage.Transparent_Color();
		return alaColorRGB();
	}

	alaString alaSprite::Type()
	{
		return ("alaSprinte");
	}

	bool alaSprite::Load_Image(alaString fileName,
		alaImageFileBase::alaImageFileFormat fileFormat)
	{
		
		bool ok = true;
		
		switch (fileFormat)
		{
		case Alamo::alaImageFileBase::ALAIFF_WINDOWS_BMP:
			ok = spriteImage.Load_From_BMP(fileName);
			break;
		case Alamo::alaImageFileBase::ALAIFF_TGA:
			ok = spriteImage.Load_From_TGA(fileName);
			break;
		default:
			ok = false;
			theApp.App_Error(ALAES_INVALID_FILE_TYPE);
			break;
		}

		displayListID = glGenLists(1);

		glNewList(displayListID, GL_COMPILE);

		spriteImage.Pre_Render();

		glBegin(GL_QUADS);

		//Lower left corner
		glTexCoord2f(0.0f, 1.0f);
		glVertex2i(0, 0);

		glTexCoord2f(1.0f, 1.0f);
		glVertex2i(spriteImage.Width(), 0);

		glTexCoord2f(1.0f, 1.0f);
		glVertex2i(spriteImage.Width(), spriteImage.Height());

		glTexCoord2f(1.0f, 1.0f);
		glVertex2i(0, spriteImage.Height());

		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(0, spriteImage.Height());
		glEnd();
		glEndList();

		return (ok);
	}

	bool alaSprite::Render()
	{
		bool ok = true;

		glPushMatrix();
		glTranslatef((float)x, (float)y, 0.0f);
		glCallList(displayListID);
		ok = (glGetError() == GL_NO_ERROR);
		glPushMatrix();

		return ok;
	}
	int alaSprite::Bitmap_Height()
	{
		return spriteImage.Height();
		//return 1;
	}
	int alaSprite::Bitmap_Width()
	{
		return spriteImage.Width();
		//return -1;
	}
	void alaSprite::Bitmap_Transparent_Color(alaColorRGB color)
	{
		spriteImage.Transparent_Color(color);
	}
}