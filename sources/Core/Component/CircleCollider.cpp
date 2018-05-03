#include "Core/Component/CircleCollider.hpp"
#include "Core/Component/BoxCollider2D.hpp"
#include "Core/GameObject.hpp"
#include "Core/Json/Json.hpp"
#include "Core/Component/Component.hpp"

namespace BeerEngine
{
	namespace Component
	{
		CircleCollider::CircleCollider(GameObject *gameObject) :
			ACollider(gameObject),
			_radius((gameObject->transform.scale.x + gameObject->transform.scale.z) / 4)
		{}

		CircleCollider::~CircleCollider()
		{}

		bool CircleCollider::checkCollision(ACollider *other)
		{
			if (other->collide_AABB2D(this))
				return (true);
			else
				return (false);
		}

		bool CircleCollider::contain(glm::vec2 other)
		{
			glm::vec2 thisPos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);

			if (glm::distance2(thisPos, other) < _radius * _radius)
				return (true);
			return (false);
		}

		bool CircleCollider::intersect(glm::vec2 origin, glm::vec2 dir)
		{
			return (false);
		}

		bool CircleCollider::intersect(glm::vec2 origin, glm::vec2 dir, glm::vec2 &outPosition)
		{
			return (false);
		}
/*
		bool CollisionDroite(Point A,Point B,Cercle C)
		{
			Vecteur u;
			u.x = B.x - A.x;
			u.y = B.y - A.y;
			Vecteur AC;
			AC.x = C.x - A.x;
			AC.y = C.y - A.y;
			float numerateur = u.x*AC.y - u.y*AC.x;   // norme du vecteur v
			if (numerateur <0)
				numerateur = -numerateur ;   // valeur absolue ; si c'est négatif, on prend l'opposé.
			float denominateur = sqrt(u.x*u.x + u.y*u.y);  // norme de u
			float CI = numerateur / denominateur;
			if (CI<C.rayon)
				return true;
			else
				return false;
		}


		bool CollisionSegment(Point A,Point B,Cercle C)
		{
			if (CollisionDroite(A,B,C) == false)
				return false;  // si on ne touche pas la droite, on ne touchera jamais le segment
			Vecteur AB,AC,BC;
			AB.x = B.x - A.x;
			AB.y = B.y - A.y;
			AC.x = C.x - A.x;
			AC.y = C.y - A.y;
			BC.x = C.x - B.x;
			BC.y = C.y - B.y;
			float pscal1 = AB.x*AC.x + AB.y*AC.y;  // produit scalaire
			float pscal2 = (-AB.x)*BC.x + (-AB.y)*BC.y;  // produit scalaire
			if (pscal1>=0 && pscal2>=0)
				return true;   // I entre A et B, ok.
			// dernière possibilité, A ou B dans le cercle
			if (CollisionPointCercle(A,C))
				return true;
			if (CollisionPointCercle(B,C))
				return true;
			return false;
		}
*/

		bool CircleCollider::collide_AABB2D(CircleCollider *other)
		{
			glm::vec2 thisPos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);
			glm::vec2 otherPos(other->_transform.position.x + other->_offset.x, other->_transform.position.z + other->_offset.y);

			if (glm::distance2(thisPos, otherPos) < (_radius + other->_radius) * (_radius + other->_radius))
			{
				if (!_isTrigger && !other->_isTrigger)
					response_AABB2D(other, thisPos, otherPos);
				return (true);
			}
			return (false);
		}

		bool CircleCollider::collide_AABB2D(BoxCollider2D *other)
		{
			return (other->collide_AABB2D(this));
		}

		void CircleCollider::response_AABB2D(CircleCollider *other, glm::vec2 &thisPos, glm::vec2 &otherPos)
		{
			float overlap = (_radius + other->_radius) - glm::distance(thisPos, otherPos);
			glm::vec3 dir(thisPos.x - otherPos.x, 0, thisPos.y - otherPos.y);
			dir = glm::normalize(dir);
			
			response(other, dir * overlap);
		}

		nlohmann::json	CircleCollider::serialize()
		{
			return {
				{"componentClass", typeid(CircleCollider).name()},
				{"radius", _radius},
			};
		}

		void CircleCollider::deserialize(const nlohmann::json & j)
		{
			this->_radius = j.at("radius");
		}

		REGISTER_COMPONENT_CPP(CircleCollider)
	}
}