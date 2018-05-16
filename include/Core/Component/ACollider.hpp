#ifndef BE_CORE_COMPONENT_ACOLLIDER_HPP
#define BE_CORE_COMPONENT_ACOLLIDER_HPP 1
/*!
 * \file ACollider.hpp
 * \brief Component de collision de base
 * \author qhonore
 */
#include "Core/Core.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"

namespace BeerEngine
{
	namespace Component
	{
		/*! \enum ColliderType
		* \brief enumerateur des types de collision
		*/
		enum ColliderType
		{
			ALL, /*!< Type de collision avec tous*/
			ONLY_OTHER, /*!< Type de Collision avec les autre met pas avec le meme type*/
			ONLY_THERE /*!< Type de collision que avec se type de collision*/
		};
		/*! \class ACollider
		* \brief classe gerent le system physique du projet
		*/
		class ACollider : public Component, public IStart
		{
		protected:

		public:
			ACollider(GameObject *gameObject);
			virtual ~ACollider();
			virtual void    start(void);

			virtual void    physicUpdate(void);
			virtual bool	hasException(ACollider *other);

			virtual bool 	checkCollision(ACollider *other) = 0;

			virtual bool collide_AABB2D(CircleCollider *other) = 0;
			virtual bool collide_AABB2D(BoxCollider2D *other) = 0;
			
			virtual bool contain(glm::vec2 other) = 0;
			virtual bool intersect(glm::vec2 origin, glm::vec2 dir) = 0;
			virtual bool intersect(glm::vec2 origin, glm::vec2 dir, glm::vec2 &outPosition) = 0;

			virtual void triggerStay(ACollider *other);
			virtual void triggerEnter(ACollider *other);
			virtual void triggerExit(ACollider *other);

			virtual void colliderStay(ACollider *other);
			virtual void colliderEnter(ACollider *other);
			virtual void colliderExit(ACollider *other);

			bool		isKinematic(void);

			void		response(ACollider *other, glm::vec3 move);

			static std::vector<ACollider*> _colliders;
			std::vector<ACollider*> _currentCollisions;
			std::vector<ACollider*> _exceptions;
			Transform	&_transform;
			glm::vec2	_offset;
			bool		_isTrigger;
			RigidBody2D *rb2d;
			ColliderType colliderType;

			virtual nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader);
		};
	}
}

#endif