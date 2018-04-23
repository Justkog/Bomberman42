#ifndef AUDIOLISTENER_HPP
#define AUDIOLISTENER_HPP

#include <AL/al.h>
#include <AL/alc.h>
#include <vector>

class AudioListener {

public:

	AudioListener( void );
	virtual ~AudioListener();

	void static	init();
	void static DestroyOpenAL();

	void		setListenerData(float x, float y, float z);

};


#endif
