#include "Game/Components/AudioManager.hpp"
#include "Game/Components/Settings.hpp"
#include "Game/Assets.hpp"

namespace Game
{
	namespace Component
	{
	AudioManager		*AudioManager::instance = nullptr;
    AudioManager::AudioManager(BeerEngine::GameObject *gameObject):
		Component(gameObject),
			audioType(Sound),
    	srcAudio(BeerEngine::Audio::AudioSource(gameObject))
    {
		instance = this;
	}

    AudioManager::AudioManager(void)
    {
		instance = this;
	}

    AudioManager::AudioManager(const AudioManager &val)
    {
        *this = val;
    }

    AudioManager &AudioManager::operator=(const AudioManager &val)
    {
			(void) val;
        if (this != &val)
        { }
        return (*this);
    }

    AudioManager::~AudioManager()
    { }

		void AudioManager::start()
		{
			play();
		}

    void    AudioManager::play()
    {
      srcAudio.play();
    }

		void    AudioManager::pause()
    {
      srcAudio.pause();
    }

		void    AudioManager::continuePlaying()
		{
			srcAudio.continuePlaying();
		}

		void 		AudioManager::setPosition(float x, float y, float z)
		{
			srcAudio.setPosition(x, y, z);
		}

    void    AudioManager::setClip(std::string const &filename)
    {
        BeerEngine::Audio::AudioClip	*clip = Assets::GetAudioClip(filename);
        srcAudio.setBuffer(clip->getBuffer());
    }

    void    AudioManager::setVolume(float soundVolume, float musicVolume)
    {
		_musicVolume = musicVolume;
		_soundVolume = soundVolume;
		if (audioType == Music)
			srcAudio.setVolume(musicVolume);
		else if (audioType ==  Sound)
			srcAudio.setVolume(soundVolume);
    }

	void 	AudioManager::setLooping(bool b)
	{
		srcAudio.setLooping(b);
	}
	float		AudioManager::getSoundVolume()
	{
		return _soundVolume;
	}

	float		AudioManager::getMusicVolume()
	{
		return _musicVolume;
	}

    nlohmann::json	AudioManager::serialize()
    {
      auto j = Component::serialize();
      j.merge_patch({
        {"componentClass", type},
      });
      return j;
    }

    void AudioManager::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
    {
      Component::deserialize(j, loader);
    }

    REGISTER_COMPONENT_CPP(AudioManager)
  }
}
