#ifndef GAME_HPP
# define GAME_HPP 1

#define GAME_DEBUG 1

namespace Game
{

	namespace Component
	{
		enum ItemType {SpeedBoost, AddBomb, ExplosionBoost, Antidote};
		enum ObjectiveType {MoveTo, DropBomb, TakeBonus, KillEnemy};

		class GameManager;

		class Bomb;
        class Breakable;
        class Character;
		class IA;
		class Item;
		class Map;
        class Player;

		class MainMenu;
		class UIThemeManager;
		class VersusMenu;
		class SettingsMenu;
		class InGameMenu;
		class GameOverMenu;
		class VictoryMenu;
		class TimeUI;
		class StartTimerUI;

		class AudioManager;

	}
}

#endif
