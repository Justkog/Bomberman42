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
