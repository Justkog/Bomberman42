#ifndef GAME_ASSETS_HPP
#define GAME_ASSETS_HPP 1

#include "Core/BeerEngine.hpp"

class Assets
{
private:
	static Assets	*_Instance;

public:
	static Assets	*GetInstance(void);
	void			load(void);
	void			unload(void);

	 BeerEngine::Audio::AudioClip	*exempleAudio;

};

#endif
