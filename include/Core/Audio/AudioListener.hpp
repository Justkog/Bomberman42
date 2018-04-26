#ifndef AUDIOLISTENER_HPP
#define AUDIOLISTENER_HPP

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
		class AudioListener : public BeerEngine::Component::Component, 
							public BeerEngine::Component::IStart,
							public BeerEngine::Component::IUpdate
		{

		public:

			AudioListener(BeerEngine::GameObject *gameObject);
			virtual ~AudioListener();

			void static	init();
			void static DestroyOpenAL();

			void		setListenerData(float x, float y, float z, float dirX, float dirY, float dirZ);

			virtual void    start(void);
            virtual void    fixedUpdate(void);
       		virtual void    update(void);
		};
	}
}

#endif
