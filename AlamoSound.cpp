#include "Alamo.h"
#include "AlamoSound.h"
#include "AlamoError.h"
#include "AlamoApp.h"
namespace Alamo
{
	

	alaSound::alaSound()
	{
		audioBuffer = 0;
		audioSource = 0;
	}
	alaSound::~alaSound()
	{
		assert(theApp.openALInitialized == true);

		if (audioBuffer != 0)
		{
			alDeleteBuffers(1, &audioBuffer);
		}

		if (audioSource != 0)
		{
			alDeleteSources(1, &audioSource);
		}
	}
	bool alaSound::Load_WAV(alaString fileName, bool continuousLoop)
	{
		assert(theApp.openALInitialized == true);
		bool ok = true;

		ALenum format;
		ALsizei size;
		ALvoid *data;
		ALsizei freq;
		ALboolean loop;

		if (alGetError() != AL_NO_ERROR)
		{
			ok = false;
			theApp.App_Error(ALAES_CANT_LOAD_SOUND_FILE);
		}
		if (ok)
		{
			alGenBuffers(1, &audioBuffer);

			if (alGetError() != AL_NO_ERROR)
			{
				ok = false;
				theApp.App_Error(ALAES_CANT_LOAD_SOUND_FILE);
			}
		}

		if (ok)
		{
			char * s = (char*)fileName.c_str();

			alutLoadWAVFile((ALbyte*)s, 
				&format,
				&data,
				&size,
				&freq,
				&loop);

			ok = (data != NULL) ?true : false;
		}

		if (ok)
		{
			alBufferData(audioBuffer, format, data, size, freq);

			if (alGetError() != AL_NO_ERROR)
			{
				ok = false;
				theApp.App_Error(ALAES_CANT_LOAD_SOUND_FILE);
			}
		}

		if (ok)
		{
			alSourcei(audioSource,
				AL_BUFFER,
				audioBuffer);
			if (alGetError() != AL_NO_ERROR)
			{
				ok = false;
				theApp.App_Error(ALAES_CANT_LOAD_SOUND_FILE);
			}

		}
		if (ok)
		{
			ALfloat sourcePosition[] = { 0.0,0.0,0.0 };

			ALfloat sourceVelocity[] = { 0.0,0.0,0.0 };

			alSourcei(audioSource, AL_BUFFER, audioBuffer);
			alSourcef(audioSource, AL_PITCH, 1.0f);
			alSourcef(audioSource, AL_GAIN, 1.0f);
			alSourcefv(audioSource, AL_POSITION, sourcePosition);
			alSourcefv(audioSource, AL_VELOCITY, sourceVelocity);
			alSourcei(audioSource, AL_LOOPING, continuousLoop);

			if (alGetError() != AL_NO_ERROR)
			{
				ok = false;
				theApp.App_Error(ALAES_CANT_LOAD_SOUND_FILE);
			}
		}
		return ok;

		
		return false;
	}
	bool alaSound::Play()
	{
		assert(theApp.openALInitialized == true);
		alSourcePlay(audioSource);
		return (alGetError() == AL_NO_ERROR);
	}
	bool alaSound::Pause()
	{
		assert(theApp.openALInitialized == true);
		alSourcePause(audioSource);
		return (alGetError() == AL_NO_ERROR);;
	}
	bool alaSound::Stop()
	{
		assert(theApp.openALInitialized == true);
		alSourceStop(audioSource);
		return (alGetError() == AL_NO_ERROR);
		
	}
	bool alaSound::Rewind()
	{
		assert(theApp.openALInitialized == true);
		alSourceRewind(audioSource);
		return (alGetError() == AL_NO_ERROR);
		
	}
	void alaSound::Gain(float gainLevel)
	{
		assert(theApp.openALInitialized == true);
		assert(gainLevel >= 0.0 && gainLevel <= 1.0);

		alSourcef(audioSource, AL_GAIN, gainLevel);
	}
	float alaSound::Gain()
	{
		assert(theApp.openALInitialized == true);
		float gainLevel;
		alGetSourcef(audioSource, AL_GAIN, &gainLevel);
		return (gainLevel);
	}
}