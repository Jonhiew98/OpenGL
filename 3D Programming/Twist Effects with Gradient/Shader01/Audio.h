#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
#include <fstream>
#include <string>
#include <fmod.hpp>
#include <fmod_errors.h>

#define SPECTRUM_SIZE 128

float m_spectrumLeft[SPECTRUM_SIZE];
float m_spectrumRight[SPECTRUM_SIZE];

void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		std::cout << "EMOD error! :" << FMOD_ErrorString(result) << std::endl;
	}
}

class AudioVisualizer
{
private:
	//sound
	FMOD::System* m_fmodSystem;
	FMOD::Sound* m_music;
	FMOD::Channel *m_musicChannel;

public:
	void initFmod()
	{
		FMOD_RESULT		result;
		unsigned int	version;

		result = FMOD::System_Create(&m_fmodSystem);
		ERRCHECK(result);

		result = m_fmodSystem->getVersion(&version);
		ERRCHECK(result);

		if (version < FMOD_VERSION)
		{
			std::cout << "FMOD Error! You are using old version of FMOD" << std::endl;
		}

		//initialize fmod system
		result = m_fmodSystem->init(32, FMOD_INIT_NORMAL, 0);
		ERRCHECK(result);

		//load and set up music
		result = m_fmodSystem->createStream("../media/Deaf Kev - Invincible.mp3", FMOD_SOFTWARE, 0, &m_music);
		ERRCHECK(result);

		//play the loaded mp3 music
		result = m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_music, false, &m_musicChannel);
		ERRCHECK(result);
	}

	void init()
	{
		initFmod();
	}

	void deinit()
	{
	}

	void updateFmod()
	{
		m_fmodSystem->update();

		//Get spectrum for left and right stereo channels
		m_musicChannel->getSpectrum(m_spectrumLeft, SPECTRUM_SIZE, 0, FMOD_DSP_FFT_WINDOW_RECT);
		m_musicChannel->getSpectrum(m_spectrumRight, SPECTRUM_SIZE, 1, FMOD_DSP_FFT_WINDOW_RECT);

		//testing first frequency range
		//std::cout << "left : " << m_spectrumLeft[0] << ", right:" << m_spectrumRight[0] << std::endl;
	}
};


#endif