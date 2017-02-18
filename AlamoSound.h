
#ifndef _ALAMO_SOUND_H_
#define _ALAMO_SOUND_H_
#include "AlamoType.h"

namespace Alamo
{
	class alaSound
	{
	public:
		alaSound();
		~alaSound();

		bool Load_WAV(alaString fileName, bool continuousLoop = false);

		bool Play();
		bool Pause();
		bool Stop();
		bool Rewind();

		void Gain(float gainLevel);
		float Gain();

	private:
		ALuint audioBuffer;
		ALuint audioSource;
	};

}
#endif // !_ALAMO_SOUND_H_