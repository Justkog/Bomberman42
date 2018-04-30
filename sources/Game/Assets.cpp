#include "Game/Assets.hpp"

Assets	*Assets::_Instance = nullptr;

Assets	*Assets::GetInstance(void)
{
	if (_Instance == nullptr)
		_Instance = new Assets();
	return (_Instance);
}

void			Assets::load(void)
{
	exempleAudio = new BeerEngine::Audio::AudioClip("assets/sounds/castle_wav.wav");
}

void			Assets::unload(void)
{
	delete exempleAudio;
}
