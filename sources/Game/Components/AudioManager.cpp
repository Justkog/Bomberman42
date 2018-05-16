#include "Game/Components/AudioManager.hpp"

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

    void    AudioManager::play()
    {
      srcAudio.play();
    }

    void    AudioManager::setClip(std::string const &filename)
    {
        BeerEngine::Audio::AudioClip	clip(filename);
        srcAudio.setBuffer(clip.getBuffer());
    }

    void    AudioManager::setVolume(float volume)
    {
      srcAudio.setVolume(volume);
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
