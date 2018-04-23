#ifndef AUDIOCLIP_HPP
# define AUDIOCLIP_HPP

#include <string>
#include <sndfile.h>
#include <AL/al.h>
#include <vector>

namespace BeerEngine
{
	namespace Audio
	{
		class AudioClip
		{

		public:

			AudioClip( const std::string& Filename );
			virtual ~AudioClip();

			ALuint	getBuffer();

		private:
			ALuint _buffer;

		};
	}
}
#endif
