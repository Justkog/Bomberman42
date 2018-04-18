/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AudioMaster.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:43:15 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/18 19:17:09 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUDIOMASTER_HPP
#define AUDIOMASTER_HPP

#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>
#include <fstream>
#include <sndfile.h>
#include <vector>

class AudioMaster {

public:

	AudioMaster( void );
	virtual ~AudioMaster();

	bool		InitOpenAL();
	void		GetDevices(std::vector<std::string>& Devices);
	void		ShutdownOpenAL();

	int			loadSound(std::string file);
	char        *loadWAV(const char * fn, int & chan, int & samplerate, int & bps, int & size);
	int			convertToInt(char *buf, int len);
	bool		isBigEndian();

// private:

};


#endif
