#ifndef GAME_HPP
# define GAME_HPP 1

#define GAME_DEBUG 1

namespace Game
{

	namespace Component
	{
		enum ItemType {SpeedBoost, AddBomb, ExplosionBoost};
		enum Objective {MoveTo, DropBomb, TakeBonus};

		class GameManager;

		class Bomb;
        class Breakable;
        class Character;
		class IA;
		class Item;
		class Map;
        class Player;

		class UIThemeManager;
		class SettingsMenu;
		class InGameMenu;

	}
}

#endif
