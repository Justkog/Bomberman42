
#include "Core/Audio/AudioSource.hpp"

namespace BeerEngine
{
	namespace Audio
	{
		AudioSource::AudioSource(ALuint buf): _Buffer(buf)
		{
			// Création d'une source
			alGenSources(1, &_Source);

		}

		AudioSource::~AudioSource()
		{ }

		void	   AudioSource::play()
		{
		    // arrete un son avant de jouant le suivant
		    stop();
		    //charge le son depuis le buffer source
		    alSourcei(_Source, AL_BUFFER, _Buffer);
			continuePlaying();
		}

		bool       AudioSource::isPlaying()
		{
			alGetSourcei(_Source, AL_SOURCE_STATE, &_Status);
			if (_Status == AL_PLAYING)
		    	return true;
			return false;
		}

		void	   AudioSource::pause()
		{
		    //mettre un son en pause
		    alSourcePause(_Source);
		}

		void	   AudioSource::continuePlaying()
		{
		    alSourcePlay(_Source);
		}

		void	   AudioSource::stop()
		{
		    alSourceStop(_Source);
		}

		void	   AudioSource::Delete()
		{
		    stop();
		    // Destruction du tampon
		    alDeleteBuffers(1, &_Buffer);

		    // Destruction de la source
		    alSourcei(_Source, AL_BUFFER, 0);
		    alDeleteSources(1, &_Source);
		}

		void	   AudioSource::setVolume(float volume)
		{
		    //change le volume du son (valeur normalisé)
		    alSourcef(_Source, AL_GAIN, volume);
		}

		void	   AudioSource::setPitch(float pitch)
		{
		    //change le ton du son (1 par defaut)
		    alSourcef(_Source, AL_PITCH, pitch);
		}

		void	   AudioSource::setPosition(float x, float y, float z)
		{
		    //change la position de la source sonore
		    alSource3f(_Source, AL_POSITION, x, y, z);
		}

		void	   AudioSource::setVelocity(float x, float y, float z)
		{
		    //change la vitesse de la source sonore
		    alSource3f(_Source, AL_VELOCITY, x, y, z);
		}

		void	   AudioSource::setLooping(bool loop)
		{
		    //active une boucle
		    alSourcei(_Source, AL_LOOPING, loop);
		}

		void		AudioSource::setBuffer(ALuint buf)
		{
			_Buffer = buf;
		}

		void		AudioSource::setSource(ALuint src)
		{
			_Source = src;
		}
	}
}
