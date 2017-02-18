
#ifndef _ALAMO_LEVEL_H_
#define _ALAMO_LEVEL_H_
#include "AlamoLevelFileBase.h"
#include "AlamoSprite.h"
#include "AlamoAnimation.h"
#include "AlamoAnimatedSprite.h"

namespace Alamo
{
	class alaLevel
	{
	public:
		alaLevel();
		~alaLevel();

		bool Load(alaString fileName, alaLevelFileBase::alaLevelFileFormat fileType);

		virtual bool Update();

		virtual bool Render();

		virtual bool Cleanup();


	protected:
		bool Parse_Level(FILE * levelFile);

		bool Parse_Sprite(FILE * levelFIle, alaSprite * sprite);

		bool Parse_Image_File_Name(FILE * levelFile, alaString &imageFileName);

		bool Parse_Transparent_Color(FILE * levelFile, alaColorRGB &color);

		bool Parse_XY(FILE * levelFile, int &xval, int & yval);

		bool Parse_Velocity(FILE * levelFile, alaVector2D & spriteVelocity);

		bool Parse_Bounding_Rectangle(FILE * levelFile,  alaBitmapRegion &theRectangle);

		bool Parse_Animated_Sprite(FILE * levelFile, alaAnimatedSprite *sprite);

		bool Parse_Animation(FILE * levelFile, alaAnimation * animation);

		bool Parse_Frames(FILE * levelFile, alaAnimation * animation);

		void Eliminate_White_Space(FILE * levelFile);

		alaString Read_Tag_Or_Value(FILE * levelFile);

		virtual bool Object_Factory(FILE * levelFile, alaString tagToParse);

		bool Is_Tag(alaString testStr, alaString tag);

		alaString Parse_Error();

	protected:
		std::vector<alaScreenObject *> allObjects;
	private:
		bool Load_From_XML(alaString fileName);

		alaString parseError;

	};
}



#endif