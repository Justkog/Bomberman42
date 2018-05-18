#ifndef BE_GAME_COMPONENT_BREAKABLE_HPP
#define BE_GAME_COMPONENT_BREAKABLE_HPP

#include "Core/Core.hpp"
#include "Core/Component/Component.hpp"
/*!
 * \file Breakable.hpp
 * \brief Component breakable, pour les objets destructibles
 * \author stmartin
 */
namespace Game
{
	namespace Component
	{
		class Map;

		/*! \class Breakable
		* \brief La classe Breakable gère la destruction des objets et leurs events associés
		*/
		class Breakable : public BeerEngine::Component::Component
		{
		protected:
			BeerEngine::Transform	&_transform;

		public:
      Breakable(BeerEngine::GameObject *gameObject);
			~Breakable(void);

			Signal<glm::vec3, int> onDestruction;
			Signal<Breakable *> onDestructionSelf;

			void destroyed();

			REGISTER_COMPONENT_HPP
		};
	}
}

#endif
