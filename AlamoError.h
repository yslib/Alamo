
#ifndef _ALAMO_ERROR_H_
#define _ALAMO_ERROR_H_

namespace Alamo
{

	typedef std::string alaString;

	typedef unsigned int alaErrorStatus;

	//this is a platform dependent type define
	typedef DWORD alaOsErrorCode;

	//Error Codes

#define ALA_MAKE_EC_VALUE(vlu) (ALAES_FIRST+(vlu))

#define ALAES_FIRST                           0
#define ALAES_NO_ERROR                        ALAES_FIRST
#define ALAES_CANT_LOAD_BITMAP                ALA_MAKE_EC_VALUE(1)
#define ALAES_CANT_REGISTER_WINDOW_CLASS      ALA_MAKE_EC_VALUE(2)
#define ALAES_CANT_CREATE_WINDOW              ALA_MAKE_EC_VALUE(3)
#define ALAES_D3D_INIT_FAILED                 ALA_MAKE_EC_VALUE(4)
#define ALAES_DINPUT_INIT_FAILED              ALA_MAKE_EC_VALUE(5)
#define ALAES_CANT_INIT_GAME                  ALA_MAKE_EC_VALUE(6)
#define ALAES_FATAL_INPUT_ERROR               ALA_MAKE_EC_VALUE(7)
#define ALAES_FATAL_FRAME_ERROR               ALA_MAKE_EC_VALUE(8)
#define ALAES_FATAL_RENDERING_ERROR           ALA_MAKE_EC_VALUE(9)
#define ALAES_OUT_OF_MEMORY                   ALA_MAKE_EC_VALUE(10)
#define ALAES_OPENGL_INIT_FAILED              ALA_MAKE_EC_VALUE(11)
#define ALAES_OPENAL_INIT_FAILED              ALA_MAKE_EC_VALUE(12)
#define ALAES_CANT_CREATE_RAW_INPUT_BUFFER    ALA_MAKE_EC_VALUE(13)
#define ALAES_INVALID_BITMAP_DIMENSIONS       ALA_MAKE_EC_VALUE(14)
#define ALAES_COULD_NOT_OPEN_FILE             ALA_MAKE_EC_VALUE(15)
#define ALAES_INVALID_FILE_NAME               ALA_MAKE_EC_VALUE(16)
#define ALAES_INVALID_FILE_TYPE               ALA_MAKE_EC_VALUE(17)
#define ALAES_COULD_NOT_READ_FILE             ALA_MAKE_EC_VALUE(18)
#define ALAES_INVALID_SCREEN_RESOLUTION       ALA_MAKE_EC_VALUE(19)
#define ALAES_CANT_INIT_SOUND_SYSTEM          ALA_MAKE_EC_VALUE(20)
#define ALAES_CANT_LOAD_SOUND_FILE            ALA_MAKE_EC_VALUE(21)
#define ALAES_INDEX_OUT_OF_RANGE              ALA_MAKE_EC_VALUE(22)
#define ALAES_CANT_PARSE_LEVEL_FILE           ALA_MAKE_EC_VALUE(23)
#define ALAES_LAST                            ALA_MAKE_EC_VALUE(24)

#define ALAES_FIRST_GAME_ERROR  1000
#define ALAES_LAST_GAME_ERROR   65535

//#define MAKE_GAME_ERROR_CODE_VALUE(vlu) (ALAES_FIRST_GAME_ERROR+(vlu))

	//Error Message ----------------------------------------
static std::string errorString[24] =
	{
		"No error",                                     // 0
		"Can't load the specified bitmap.",             // 1
		"Can't register window class.",                 // 2
		"Can't create window.",                         // 3
		"Can't initialize Direct3D.",                   // 4
		"Can't initialize DirectInput.",                // 5
		"Can't initialize the game.",                   // 6
		"Can't get input from DirectInput.",            // 7
		"Can't update a frame.",                        // 8
		"Can't render a frame.",                        // 9
		"Can't continue. Out of memory.",               // 10
		"Can't initialize OpenGL.",                     // 11
		"Can't initialize OpenAL.",                     // 12
		"Can't allocate raw input buffer.",             // 13
		"The bitmap's height or width is <= 0.",        // 14
		"Could not open the file or file not found.",   // 15
		"The invalid file name or extension.",          // 16
		"The file type is invalid."                     // 17
		"Cannot read data from the file.",              // 18
		"Screen resolution not supported.",             // 19
		"Can't initialize sound subsystem",             // 20
		"The sound file is invalid or not found",       // 21
		"The index value is out of range.",             // 22
		"Can't parse level file."                       // 23
	};



	//Error Class-------------
	//
	class alaError
	{
	public:
		alaError()
		{
			Clear();
		}

		alaError(alaErrorStatus errorID, alaString errorMesaageString ="")
		{
			Set_Error(errorID, errorMesaageString);
		}
		~alaError()
		{

		}
		void Error(alaErrorStatus errorID,
			alaString errorMessageString = "")
		{
			Set_Error(errorID, errorMessageString);
		}

		alaErrorStatus Error_Number()
		{
			return (errorNumber);
		}
		alaString Error_Mesaage()
		{
			return (errorMessage);
		}

		static alaOsErrorCode Get_Last_OS_Error_Code();
		 static alaString Get_Last_OS_Error_Message();

		 void Clear()
		 {
			 errorNumber = ALAES_NO_ERROR;
		 }

	private:
		void Set_Error(alaErrorStatus errorID,
			alaString errorMessageString)
		{
			assert((errorID >= ALAES_FIRST) && (errorID <= ALAES_LAST_GAME_ERROR));

			errorNumber = errorID;

			if ((errorID >= ALAES_FIRST) && (errorID <= ALAES_LAST))
			{
				errorMessage = errorString[errorID];
			}
			else
			{
				errorMessage = errorMessageString;
			}
		}

	private:
		alaErrorStatus errorNumber;
		alaString errorMessage;

	};


	//Begin inline functions definition for alaError class-----------

	//End the inline function definition for the alaError class

}
// End namespace -----------------

#endif //_ALAMO_ERROR_H_