#ifndef AUDIOLISTENER_HPP
#define AUDIOLISTENER_HPP
/*!
 * \file AudioListener.hpp
 * \brief class d'ecoute audio
 * \author stmartin
 */

#include <AL/al.h>
#include <AL/alc.h>
#include <vector>
#include "Core/GameObject.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IStart.hpp"

namespace BeerEngine
{
	namespace Audio
	{
		/*! \class AudioListener
		* \brief classe d'ecoute d'audio par sa localition
		*/
		class AudioListener : public BeerEngine::Component::Component,
							public BeerEngine::Component::IStart,
							public BeerEngine::Component::IUpdate
		{

		public:
			AudioListener(BeerEngine::GameObject *gameObject);
			virtual ~AudioListener();

			void static	Load();
			void static DestroyOpenAL();

			void		setListenerData(float x, float y, float z, float dirX, float dirY, float dirZ);

			virtual void    start(void);
            virtual void    fixedUpdate(void);
       		virtual void    update(void);

			REGISTER_COMPONENT_HPP

		};
	}
}

#endif
