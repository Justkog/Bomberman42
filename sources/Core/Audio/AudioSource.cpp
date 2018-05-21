#include "Core/Audio/AudioSource.hpp"

namespace BeerEngine
{
	namespace Audio
	{

		AudioSource::AudioSource(BeerEngine::GameObject *gameObject) :
			Component(gameObject)
		{
			// Création d'une source
			alGenSources(1, &_Source);
			alSourcef(_Source, AL_ROLLOFF_FACTOR, 1);
			alSourcef(_Source, AL_REFERENCE_DISTANCE, 120);
			alSourcef(_Source, AL_MAX_DISTANCE, 300);
        }

		AudioSource::AudioSource()
		{}

		AudioSource::AudioSource(const AudioSource &val)
		{
			*this = val;
		}

		AudioSource &AudioSource::operator=(const AudioSource &val)
		{
			if (this != &val)
			{
				_Buffer = val._Buffer;
				_Source = val._Source;
				_Status = val._Status;
			}
			return (*this);
		}

		AudioSource::~AudioSource()
		{
			Delete();
		}

		void	   AudioSource::play()
		{
		    // arrete un son avant de jouer le suivant
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
			if (alIsSource(_Source))
			{
		    	alDeleteSources(1, &_Source);
					if (alGetError() != AL_NO_ERROR)
						throw std::runtime_error("AudioSource delete source error");
			}
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
		    alSource3f(_Source, AL_POSITION, -x, -y, -z);
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

		ALuint	AudioSource::getBuffer()
		{
			return _Buffer;
		}

		void		AudioSource::start(void)
		{
			setPosition(_gameObject->transform.position.x, _gameObject->transform.position.y, _gameObject->transform.position.z);
		}

		void		AudioSource::fixedUpdate(void)
		{

		}

		void		AudioSource::update(void)
		{
			setPosition(_gameObject->transform.position.x, _gameObject->transform.position.y, _gameObject->transform.position.z);
		}

		nlohmann::json	AudioSource::serialize()
		{
			auto j = Component::serialize();
			j.merge_patch({
				{"componentClass", type},
			});
			return j;
		}

		void AudioSource::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
		{
			Component::deserialize(j, loader);
		}

		REGISTER_COMPONENT_CPP(AudioSource)
	}
}
