#ifndef AUDIOLISTENER_HPP
#define AUDIOLISTENER_HPP

#include <AL/al.h>
#include <AL/alc.h>
#include <vector>

class AudioListener {

public:

	AudioListener( void );
	virtual ~AudioListener();

	void		initDevices();
	bool		InitOpenAL(const char* DeviceName);
	void		GetDevices(std::vector<std::string>& Devices);
	void		ShutdownOpenAL();

	void		setListenerData(float x, float y, float z);

};


#endif
