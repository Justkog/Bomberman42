#include "Game/Components/AudioManager.hpp"
#include "Game/Components/Settings.hpp"

namespace Game
{
	namespace Component
	{
    AudioManager::AudioManager(BeerEngine::GameObject *gameObject):
		Component(gameObject),
    srcAudio(BeerEngine::Audio::AudioSource(gameObject))
    { }

    AudioManager::~AudioManager()
    { }

		void AudioManager::start()
		{
			// setVolume();
			play();
		}

    void    AudioManager::play()
    {
      srcAudio.play();
    }

		void 		AudioManager::setPosition(float x, float y, float z)
		{
			srcAudio.setPosition(x, y, z);
		}

    void    AudioManager::setClip(std::string const &filename)
    {
        BeerEngine::Audio::AudioClip	clip(filename);
        srcAudio.setBuffer(clip.getBuffer());
    }

    void    AudioManager::setVolume()
    {
			// std::cout <<"=============================" << Game::Component::Settings::GetInstance().settingsContainer.musicVolume << std::endl;
      srcAudio.setVolume(Game::Component::Settings::GetInstance().settingsContainer.musicVolume / 100);
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
