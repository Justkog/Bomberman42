#ifndef BE_GAME_COMPONENT_IA_HPP
#define BE_GAME_COMPONENT_IA_HPP 1

#include "Core/Core.hpp"
#include "Game/Game.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/ITriggerStay.hpp"
#include "Core/Component/ITriggerEnter.hpp"
#include "Core/Component/ITriggerExit.hpp"
#include "Core/Component/IColliderStay.hpp"
#include "Core/Component/IColliderEnter.hpp"
#include "Core/Component/IColliderExit.hpp"
#include "Core/Component/IOnDestroy.hpp"
#include "Core/Component/IUI.hpp"
#include <queue>

namespace Game
{
	namespace Component
	{
		class IA : public BeerEngine::Component::Component,
						public BeerEngine::Component::IStart,
						public BeerEngine::Component::IUpdate,
						public BeerEngine::Component::IUI,
						public BeerEngine::Component::IOnDestroy
		{
		protected:
			BeerEngine::Transform	&_transform;
			Game::Component::Character *_character;
			bool _hasObjective;
			glm::vec2 _pos;
			ObjectiveType _type;
			std::vector<glm::vec2> _path;
			int _val;

			bool    canMove(glm::vec3 dir);
			bool    avoidExplosion(glm::vec3 pos, glm::vec3 dir, int offset = 0);
			bool    avoidAllExplosions(glm::vec2 pos, int offset = 0);
			int     checkExplosionRay(glm::vec3 pos, glm::vec3 dir, ObjectiveType &type);
			int     checkExplosionZone(glm::vec2 pos, ObjectiveType &type);
			int		findObjective(bool save = true);
			bool    moveToObjective(void);
			bool    moveToNextCell(void);

			//PATHFINDER
			bool	checkCell(glm::vec2 cur, std::vector<std::vector<int>> &mapCopy, int weight, std::queue<glm::vec2> &toCheck, glm::vec2 start);
			bool    analyzeMap(glm::vec2 start, std::vector<std::vector<int>> &mapCopy, glm::vec2 target);
			glm::vec2    getPath(glm::vec2 cur, std::vector<std::vector<int>> &mapCopy);
			bool    findPath(glm::vec2 target, std::vector<glm::vec2> *path = nullptr);

		public:
            IA(BeerEngine::GameObject *gameObject);
			~IA(void);

       		virtual void    onDestroy(void);
            virtual void    start(void);
            virtual void    fixedUpdate(void);
       		virtual void    update(void);
			virtual void    renderUI(struct nk_context *ctx);

			nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j);

			REGISTER_COMPONENT_HPP

			Game::Component::Map *map;
		};
	}
}

#endif
