#ifndef GAME_LEVEL1_HPP
#define GAME_LEVEL1_HPP 1

#include "Core/Core.hpp"
#include "Game/Game.hpp"
#include "Core/AScene.hpp"

class Level1 : public BeerEngine::AScene
{
public:
	void    init(void);

	static Level1 instance;
};

#endif
