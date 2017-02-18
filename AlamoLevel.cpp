#include "Alamo.h"
#include "AlamoLevel.h"
#include "AlamoApp.h"

namespace Alamo
{
	alaLevel::alaLevel()
	{

	}


	alaLevel::~alaLevel()
	{
		Cleanup();
	}


	bool alaLevel::Load(alaString fileName, alaLevelFileBase::alaLevelFileFormat fileType)
	{
		bool ok = false;

		if (fileType == alaLevelFileBase::ALALFF_XML)
		{
			ok = Load_From_XML(fileName);
			if (ok == false)
			{
				theApp.App_Error(ALAES_CANT_PARSE_LEVEL_FILE,parseError);
			}
		}
		else if (fileType == alaLevelFileBase::ALALFF_SIMPLEBINARY)
		{
			ok = false;
		}
		return ok;
	}


	bool alaLevel::Update()
	{
		return false;
	}


	bool alaLevel::Render()
	{
		bool ok = true;

		int n = allObjects.size();
		for (int i = 0; i < n && ok == true; i++)
		{
			ok = allObjects[i]->Render();
		}
		return ok;
	}
	bool alaLevel::Cleanup()
	{
		int n = allObjects.size();
		for (int i = 0; i < n; i++) {
			if (allObjects[i] != nullptr)
			{
				delete allObjects[i];
				allObjects[i] = nullptr;
			}
		}
		allObjects.clear();
		return true;
	}
	bool alaLevel::Parse_Level(FILE * levelFile)
	{
		bool ok = true;
		alaString str;

		bool levelCloseTagFound = false;

		while ((!feof(levelFile)) && 
			(levelCloseTagFound == false) && 
			(ok == true))
		{
			Eliminate_White_Space(levelFile);

			str = Read_Tag_Or_Value(levelFile);

			if (Is_Tag(str, "alaSprite"))
			{
				alaSprite * sp = new alaSprite;

				if (sp != nullptr)
				{
					ok = Parse_Sprite(levelFile, sp);
					if (ok == true)
					{
						allObjects.push_back((alaScreenObject *)sp);
					}
				}
				else
				{
					ok = false;
					theApp.App_Error(ALAES_OUT_OF_MEMORY);
				}
			}
			else if (Is_Tag(str, "alaAnimatedSprite"))
			{
				alaAnimatedSprite * asp = new alaAnimatedSprite;
				if (asp != nullptr)
				{
					ok = Parse_Animated_Sprite(levelFile, asp);

					if (ok)
					{
						allObjects.push_back((alaScreenObject *)asp);
					}
				}
				else
				{
					ok = false;
					theApp.App_Error(ALAES_OUT_OF_MEMORY);
				}
			}
			else if (Is_Tag(str, "/Level"))
			{
				levelCloseTagFound = true;
			}
			else if (Is_Tag(str, "Level") == false)
			{
				ok = Object_Factory(levelFile, str);
			}
		}

		if (levelCloseTagFound == false)
		{
			ok = false;
			parseError = "</Level> not found.";
		}
		return ok;

	}
	bool alaLevel::Parse_Sprite(FILE * levelFile, 
		alaSprite * sprite)
	{
		assert(sprite != nullptr);

		alaString str;
		bool ok = true;
		bool spriteCloseTagFound = false;

		while ((!feof(levelFile)) &&
			(spriteCloseTagFound == false) &&
			(ok == true))
		{
			Eliminate_White_Space(levelFile);
			str = Read_Tag_Or_Value(levelFile);

			if (Is_Tag(str, "ImageFileName"))
			{
				alaString imageFileName;

				ok = Parse_Image_File_Name(levelFile, imageFileName);

				if (ok)
				{
					ok = sprite->Load_Image(imageFileName,
						alaImageFileBase::ALAIFF_WINDOWS_BMP);

				}
			}
			else if (Is_Tag(str, "TransparentColor"))
			{
				alaColorRGB color;
				ok = Parse_Transparent_Color(levelFile, color);
				if (ok == true)
				{
					sprite->Bitmap_Transparent_Color(color);
				}
			}
			else if (Is_Tag(str, "Velocity"))
			{
				alaVector2D spriteVelocity;

				ok = Parse_Velocity(levelFile, spriteVelocity);
				if (ok)
				{
					sprite->Movement(spriteVelocity);
				}
			}
			else if (Is_Tag(str, "XY"))
			{
				int xval, yval;
				ok = Parse_XY(levelFile, xval, yval);

				if (ok)
				{
					sprite->X(xval);
					sprite->Y(yval);
				}
			}
			else if (Is_Tag(str, "BoundingRectangle"))
			{
				alaBitmapRegion rect;

				ok = Parse_Bounding_Rectangle(levelFile, rect);

				if (ok)
				{
					sprite->Bounding_Rectangle(rect);
				}
			}
			else if (Is_Tag(str, "/Sprite"))
			{
				spriteCloseTagFound = true;
			}
		}

		if (spriteCloseTagFound == false)
		{
			ok = false;
			parseError = "</Sprite> not found.";
		}

		return ok;
	}
	bool alaLevel::Parse_Image_File_Name(FILE * levelFile, alaString & imageFileName)
	{
		alaString str;
		bool ok = true;

		Eliminate_White_Space(levelFile);
		str = Read_Tag_Or_Value(levelFile);

		imageFileName = str;

		Eliminate_White_Space(levelFile);
		str = Read_Tag_Or_Value(levelFile);

		if (Is_Tag(str, "/ImageFileName") == false)
		{
			parseError = "</ImageFileName> not found.";
			ok = false;
		}
		return ok;
	}
	bool alaLevel::Parse_Transparent_Color(FILE * levelFile, alaColorRGB & color)
	{
		alaString str;

		bool ok = true;

		bool transparentColorCloseTagFound = false;
		while ((!feof(levelFile)) &&
			(transparentColorCloseTagFound == false) &&
			(ok))
		{
			Eliminate_White_Space(levelFile);

			str = Read_Tag_Or_Value(levelFile);

			if (Is_Tag(str, "Red"))
			{
				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);
				color.R = atof(str.c_str());

				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);

				if (Is_Tag(str, "/Red"))
				{
					parseError = "</Red> not found.";
					ok = false;
				}
			}
			else if (Is_Tag(str, "Green"))
			{
				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);

				color.G = atof(str.c_str());

				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);

				if (Is_Tag(str, "/Green") == false)
				{
					parseError = "</Green> not found.";
					ok = false;
				}
			}
			else if (Is_Tag(str, "Blue"))
			{
				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);
				color.B = atof(str.c_str());

				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);
				if (Is_Tag(str, "/Blue") == false)
				{
					parseError = "</Blue> not found.";
					ok = false;
				}
			}
			else if (Is_Tag(str, "/TransparentColor"))
			{
				transparentColorCloseTagFound = true;
			}

			
		}
		if (transparentColorCloseTagFound == false)
		{
			parseError = "</TransparentColor> not found.";
			ok = false;
		}
		return ok;

	}
	bool alaLevel::Parse_XY(FILE * levelFile, int & xval, int & yval)
	{
		alaString str;
		bool ok = true;
		bool xyCloseTagFound = false;

		while ((!feof(levelFile)) &&
			(!xyCloseTagFound) &&
			(ok))
		{
			Eliminate_White_Space(levelFile);
			str = Read_Tag_Or_Value(levelFile);

			if (Is_Tag(str, "X"))
			{
				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);
				xval = atoi(str.c_str());

				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);

				if (Is_Tag(str, "/X") == false)
				{
					parseError = "</X> not found.";
					ok = false;
				}
			}
			else if (Is_Tag(str, "Y"))
			{
				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);

				yval = atoi(str.c_str());

				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);

				if(Is_Tag(str, "/Y") == false)
				{
					parseError = "</Y> not found.";
					ok = false;
				}
			}
			else if (Is_Tag(str, "/XY"))
			{
				xyCloseTagFound = true;
			}
		}
		if (xyCloseTagFound == false)
		{
			parseError = "</XY> not found.";
			ok = false;
		}
		return ok;
	}
	bool alaLevel::Parse_Velocity(FILE * levelFile, alaVector2D & spriteVelocity)
	{
		alaString str;
		bool ok = true;
		bool velocityCloseTagFound = false;

		while ((!feof(levelFile)) &&
			(!velocityCloseTagFound) &&
			(ok))
		{
			Eliminate_White_Space(levelFile);
			str = Read_Tag_Or_Value(levelFile);

			if (Is_Tag(str, "X"))
			{
				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);
				spriteVelocity.X(atoi(str.c_str()));

				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);
				if (!Is_Tag(str, "/X"))
				{
					parseError = "</X> not found.";
					ok = false;
				}
			}
			else if (Is_Tag(str, "Y"))
			{
				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);
				spriteVelocity.Y(atoi(str.c_str()));

				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);
				if (!Is_Tag(str, "/Y"))
				{
					parseError = "</Y> not found.";
					ok = false;
				}
			}
			else if (Is_Tag(str, "/Velocity"))
			{
				velocityCloseTagFound = true;
			}
		}

		if (!velocityCloseTagFound)
		{
			parseError = "</Velocity> not found.";
			ok = false;
		}
		return (ok);
	}
	bool alaLevel::Parse_Bounding_Rectangle(FILE * levelFile, alaBitmapRegion &theRectangle)
	{
		alaString str;
		bool ok = true;
		bool boundingRectangleCloseTagFound = false;

		while ((!feof(levelFile)) &&
			(!boundingRectangleCloseTagFound) &&
			(ok))
		{
			Eliminate_White_Space(levelFile);
			str = Read_Tag_Or_Value(levelFile);

			if (Is_Tag(str, "Top"))
			{
				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);
				theRectangle.top = atoi(str.c_str());

				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);
				if (!Is_Tag(str, "/Top"))
				{
					parseError = "</Top> not found.";
					ok = false;
				}
			}
			else if (Is_Tag(str, "Bottom"))
			{
				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);
				theRectangle.bottom = atoi(str.c_str());

				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);
				if (!Is_Tag(str, "/Bottom"))
				{
					parseError = "</Bottom> not found.";
					ok = false;
				}
			}
			else if (Is_Tag(str, "Left"))
			{
				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);
				theRectangle.left = atoi(str.c_str());

				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);
				if (!Is_Tag(str, "/Left"))
				{
					parseError = "</Left> not found.";
					ok = false;
				}
			}
			else if (Is_Tag(str, "Right"))
			{
				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);
				theRectangle.right = atoi(str.c_str());

				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);
				if (!Is_Tag(str, "/Right"))
				{
					parseError = "</Right> not found.";
					ok = false;
				}
			}
			else if (Is_Tag(str, "/BoundingRectangle"))
			{
				boundingRectangleCloseTagFound = true;
			}
		}

		if (!boundingRectangleCloseTagFound)
		{
			parseError = "</BoundingRectangle> not found.";
			ok = false;
		}
		return (ok);
	}
	bool alaLevel::Parse_Animated_Sprite(FILE * levelFile, alaAnimatedSprite * sprite)
	{
		alaString str;
		bool ok = true;
		bool animatedSpriteCloseTagFound = false;

		while ((!feof(levelFile)) &&
			(!animatedSpriteCloseTagFound) &&
			(ok))
		{
			Eliminate_White_Space(levelFile);
			str = Read_Tag_Or_Value(levelFile);

			if (Is_Tag(str, "Animation"))
			{
				alaAnimation *theAnimation = new alaAnimation;
				if (theAnimation != NULL)
				{
					ok =
						Parse_Animation(
							levelFile,
							theAnimation);
				}
				else
				{
					ok = false;
					theApp.App_Error(ALAES_OUT_OF_MEMORY);
				}

				if (ok)
				{
					sprite->Animation(theAnimation);
				}
			}
			else if (Is_Tag(str, "CurrentAnimation"))
			{
				int currentAnimation;

				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);
				currentAnimation = atoi(str.c_str());
				sprite->Current_Animation(currentAnimation);

				Eliminate_White_Space(levelFile);
				str = Read_Tag_Or_Value(levelFile);
				if (!Is_Tag(str, "/CurrentAnimation"))
				{
					parseError = "</CurrentAnimation> not found.";
					ok = false;
				}
			}
			else if (Is_Tag(str, "XY"))
			{
				int xValue, yValue;
				ok = Parse_XY(levelFile, xValue, yValue);
				if (ok)
				{
					sprite->X(xValue);
					sprite->Y(yValue);
				}
			}
			else if (Is_Tag(str, "Velocity"))
			{
				alaVector2D spriteVelocity;

				ok = Parse_Velocity(levelFile, spriteVelocity);
				if (ok)
				{
					sprite->Movement(spriteVelocity);
				}
			}
			else if (Is_Tag(str, "BoundingRectangle"))
			{
				alaBitmapRegion theRectangle;
				ok = Parse_Bounding_Rectangle(levelFile, theRectangle);
				if (ok)
				{
					sprite->Bounding_Rectangle(theRectangle);
				}
			}
			else if (Is_Tag(str, "/AnimatedSprite"))
			{
				animatedSpriteCloseTagFound = true;
			}
		}

		if (!animatedSpriteCloseTagFound)
		{
			ok = false;
			parseError = "</AnimatedSprite> not found.";
		}

		return (ok);
	}
	bool alaLevel::Parse_Animation(FILE * levelFile, alaAnimation * theAnimation)
	{
		std::string temp;
		bool ok = true;
		bool animationCloseTagFound = false;

		while ((!feof(levelFile)) &&
			(!animationCloseTagFound) &&
			(ok))
		{
			Eliminate_White_Space(levelFile);
			temp = Read_Tag_Or_Value(levelFile);

			if (Is_Tag(temp, "Frames"))
			{
				ok = Parse_Frames(levelFile, theAnimation);
			}
			else if (Is_Tag(temp, "TransparentColor"))
			{
				alaColorRGB theColor;
				ok =
					Parse_Transparent_Color(levelFile, theColor);

				if (ok)
				{
					theAnimation->Bitmap_Transparent_Color(theColor);
				}
			}
			else if (Is_Tag(temp, "CurrentFrame"))
			{
				int currentFrame;

				Eliminate_White_Space(levelFile);
				temp = Read_Tag_Or_Value(levelFile);
				currentFrame = atoi(temp.c_str());
				theAnimation->Current_Frame(currentFrame);

				Eliminate_White_Space(levelFile);
				temp = Read_Tag_Or_Value(levelFile);
				if (!Is_Tag(temp, "/CurrentFrame"))
				{
					parseError = "</CurrentFrame> not found.";
					ok = false;
				}
			}
			else if (Is_Tag(temp, "LoopStyle"))
			{
				alaAnimation::alaLoopStyle loopStyle;

				Eliminate_White_Space(levelFile);
				temp = Read_Tag_Or_Value(levelFile);

				char arrayString[20];

				for (int i = 0; i < temp.length(); i++)
				{
					temp[i] = toupper(temp[i]);
				}

				if (temp == alaString("FORWARD"))
				{
					loopStyle = alaAnimation::AN_FORWARD;
				}
				else if (temp == std::string("REVERSE"))
				{
					loopStyle = alaAnimation::AN_REVERSE;
				}
				else if (temp == std::string("FORWARD_THEN_REVERSE"))
				{
					loopStyle = alaAnimation::AN_FORWARD_THEN_REVERSE;
				}

				theAnimation->Loop_Animation(true, loopStyle);

				Eliminate_White_Space(levelFile);
				temp = Read_Tag_Or_Value(levelFile);

				if (!Is_Tag(temp, "/LoopStyle"))
				{
					parseError = "</LoopStyle> not found.";
					ok = false;
				}
			}
			else if (Is_Tag(temp, "/Animation"))
			{
				animationCloseTagFound = true;
			}
		}

		if (!animationCloseTagFound)
		{
			ok = false;
			parseError = "</Animation> not found.";
		}

		return (ok);
	}
	bool alaLevel::Parse_Frames(FILE * levelFile, alaAnimation * theAnimation)
	{
		alaString str;
		bool ok = true;
		bool framesCloseTagFound = false;

		while ((!feof(levelFile)) &&
			(!framesCloseTagFound) &&
			(ok))
		{
			Eliminate_White_Space(levelFile);
			str = Read_Tag_Or_Value(levelFile);

			if (Is_Tag(str, "ImageFileName"))
			{
				std::string imageFileName;
				ok =
					Parse_Image_File_Name(
						levelFile,
						imageFileName);
				if (ok)
				{
					ok =theAnimation->Load_Image(
							imageFileName,
							alaImageFileBase::ALAIFF_WINDOWS_BMP);
				}
			}
			else if (Is_Tag(str, "/Frames"))
			{
				framesCloseTagFound = true;
			}
		}

		if (!framesCloseTagFound)
		{
			ok = false;
			parseError = "</Frames> not found.";
		}

		return (ok);
	}
	void alaLevel::Eliminate_White_Space(FILE * levelFile)
	{
		bool done = false;
		char ch = '\0';

		while (done == false)
		{
			if (feof(levelFile) || ch == '<')
			{
				done = true;
			}
			else if(ch != ' ' && ch != '\n' && ch != '\0' && ch != 9)
			{
				ungetc(ch, levelFile);
				done = true;
			}
			else
			{
				ch = fgetc(levelFile);
			}
		}

		if (feof(levelFile))
		{
			parseError = "> charater not found";
		}

	}
	alaString alaLevel::Read_Tag_Or_Value(FILE * levelFile)
	{
		alaString inputStr;

		char ch = '\0';

		bool done = false;

		while ((!feof(levelFile)) &&
			done == false)
		{
			ch = fgetc(levelFile);
			if (ch != '>' && ch != '<')
			{
				if (ch != ' ' &&
					ch != '\n' &&
					ch != '\0' &&
					ch != 9)		//tabs \t
				{
					inputStr.append(1, ch);
				}
			}
			else
			{
				done = true;
			}
		}
		if (feof(levelFile))
		{
			parseError = "Could not parse string";
		}
		return inputStr;

	}
	bool alaLevel::Object_Factory(FILE * levelFile, alaString tagToParse)
	{
		return false;
	}
	bool alaLevel::Is_Tag(alaString testStr, alaString tag)
	{
		for (int i = 0; i < testStr.length(); i++) {
			testStr[i] = toupper(testStr[i]);
		}
		for (int i = 0; i < tag.length(); i++) {
			tag[i] = toupper(tag[i]);
		}
		return testStr == tag;
	}
	alaString alaLevel::Parse_Error()
	{
		return parseError;
	}
	bool alaLevel::Load_From_XML(alaString fileName)
	{
		bool ok = true;
		FILE * file = fopen(fileName.c_str(), "r");

		if (file != nullptr)
		{
			ok = Parse_Level(file);
			fclose(file);
		}
		else
		{
			ok = false;
		}
		return ok;
	}
}