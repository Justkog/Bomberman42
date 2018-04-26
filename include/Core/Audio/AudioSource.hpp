#ifndef AUDIOSOURCE_HPP
# define AUDIOSOURCE_HPP

#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>
#include <fstream>
#include <sndfile.h>
#include <vector>
#include <iomanip>
#include "Core/GameObject.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IStart.hpp"

namespace BeerEngine
{
	namespace Audio
	{
		class AudioSource : public BeerEngine::Component::Component, 
							public BeerEngine::Component::IStart,
							public BeerEngine::Component::IUpdate
		{

		public:

			// AudioSource(ALuint buf);
			AudioSource(BeerEngine::GameObject *gameObject);
			~AudioSource( void );

			void	    play();
			bool        isPlaying();
			void	    pause();
			void		continuePlaying();
			void	    stop();

			void	    Delete();

			void		setVolume(float);
			void		setPitch(float);
			void		setPosition(float x, float y, float z);
			void		setVelocity(float x, float y, float z);
			void		setLooping(bool loop);
			void		setBuffer(ALuint);
			void		setSource(ALuint);

			virtual void    start(void);
            virtual void    fixedUpdate(void);
       		virtual void    update(void);

		private:
			ALuint		_Buffer;
			ALuint		_Source;
			ALint		_Status;
		};
	}
}

#endif
