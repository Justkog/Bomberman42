#ifndef AUDIOSOURCE_HPP
# define AUDIOSOURCE_HPP

#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>
#include <fstream>
#include <sndfile.h>
#include <vector>
#include <iomanip>

class AudioSource
{

public:

	AudioSource(ALuint buf);
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

private:
	ALuint		_Buffer;
	ALuint		_Source;
	ALint		_Status;
};

#endif
