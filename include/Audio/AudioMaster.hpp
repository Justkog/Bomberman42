/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AudioMaster.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:43:15 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/21 15:55:16 by stmartin         ###   ########.fr       */
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
#include <iomanip>

class AudioMaster {

public:

	AudioMaster( void );
	virtual ~AudioMaster();

	bool		InitOpenAL(const char* DeviceName);
	void		GetDevices(std::vector<std::string>& Devices);
	void		ShutdownOpenAL();
	ALuint		LoadSound(const std::string& Filename);

	void		setListenerData(float x, float y, float z);

	int			entryPoint();

	// std::list<ALuint> bufList;

};


#endif
