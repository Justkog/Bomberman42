#ifndef BE_CORE_COMPONENT_PARTICLEEXPLODE_HPP
#define BE_CORE_COMPONENT_PARTICLEEXPLODE_HPP 1
/*!
 * \file ParticleExplode.hpp
 * \brief Systeme de particule qui represente une explosion
 * \author mgallo
 */
#include "ParticleBase.hpp"
/*! \namespace BeerEngine
 * espace de nommage regroupant les fonctionnalité du moteur
 */
namespace BeerEngine
{
	/*! \namespace Component
	* espace de nommage regroupant les fonctionnalité des Component du moteur
	*/
	namespace Component
	{
		/*! \class ParticleExplode
		* \brief System de particule qui permet au particule de se generer vers des directions autour d'un point
		*/
		class ParticleExplode : public ParticleBase
		{
		public:
			ParticleExplode(GameObject *gameObject);
			virtual void initParticle(Particle &particle);

			REGISTER_COMPONENT_HPP
		};
	}
}

#endif