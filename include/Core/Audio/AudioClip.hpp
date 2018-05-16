#ifndef AUDIOCLIP_HPP
# define AUDIOCLIP_HPP
/*!
 * \file AudioClip.hpp
 * \brief Fichier audio
 * \author stmartin
 */
#include <string>
#include <sndfile.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <vector>

namespace BeerEngine
{
	namespace Audio
	{
		/*! \class AudioClip
		* \brief classe de stockage des sources audio
		*/
		class AudioClip
		{

		public:

			AudioClip( const std::string& Filename );
			virtual ~AudioClip();

			void		cleanUp();
			ALuint	getBuffer();

		private:
			ALuint _buffer;

		};
	}
}
#endif
