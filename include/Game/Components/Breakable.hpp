#ifndef BE_GAME_COMPONENT_BREAKABLE_HPP
#define BE_GAME_COMPONENT_BREAKABLE_HPP

#include "Core/Core.hpp"
#include "Core/Component/Component.hpp"
// #include "Core/GameObject.hpp"
// #include "Game/Components/Map.hpp"

// #include "Core/Component/IUpdate.hpp"
// #include "Core/Component/IStart.hpp"
// #include "Core/Component/ITriggerStay.hpp"
// #include "Core/Component/ITriggerEnter.hpp"
// #include "Core/Component/ITriggerExit.hpp"
// #include "Core/Component/IColliderStay.hpp"
// #include "Core/Component/IColliderEnter.hpp"
// #include "Core/Component/IColliderExit.hpp"
// #include "Core/Component/IUI.hpp"

namespace Game
{
	namespace Component
	{
		class Map;

		class Breakable : public BeerEngine::Component::Component
						// public BeerEngine::Component::IStart
						// public BeerEngine::Component::IUpdate,
						// public BeerEngine::Component::IUI
		{
		protected:
			BeerEngine::Transform	&_transform;

		public:
            Breakable(BeerEngine::GameObject *gameObject);
			~Breakable(void);

			Signal<float, float> onDestruction;

			void destroyed();
			// void	updateMap(int **map);
			BeerEngine::GameObject	*_crateDestoyed;
			// Map			*_map;

		private:
			int		_posX;
			int		_posY;

            // virtual void    start(void);
            // virtual void    fixedUpdate(void);
       		// virtual void    update(void);
			// virtual void    renderUI(struct nk_context *ctx);
       		// virtual void    onTriggerStay(BeerEngine::Component::ACollider *other);
       		// virtual void    onTriggerEnter(BeerEngine::Component::ACollider *other);
       		// virtual void    onTriggerExit(BeerEngine::Component::ACollider *other);
       		// virtual void    onColliderStay(BeerEngine::Component::ACollider *other);
       		// virtual void    onColliderEnter(BeerEngine::Component::ACollider *other);
       		// virtual void    onColliderExit(BeerEngine::Component::ACollider *other);

			nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j);

			REGISTER_COMPONENT_HPP
		};
	}
}

#endif
