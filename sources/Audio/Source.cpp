/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Source.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:19:07 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/20 17:39:06 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Audio/Source.hpp"

Source::Source(ALuint buf): _Buffer(buf)
{
	// Création d'une source
	alGenSources(1, &_Source);

}

Source::~Source()
{ }

void	   Source::play()
{
    stop();
    //charge le son depuis le buffer source
    alSourcei(_Source, AL_BUFFER, _Buffer);
    // On joue le son
    continuePlaying();
}

bool       Source::isPlaying()
{
    // Recuperation de l'etat du son
	alGetSourcei(_Source, AL_SOURCE_STATE, &_Status);
	if (_Status == AL_PLAYING)
    	return true;
	return false;
}

void	   Source::pause()
{
    //mettre un son en pause
    alSourcePause(_Source);
}

void	   Source::continuePlaying()
{
    alSourcePlay(_Source);
}

void	   Source::stop()
{
    alSourceStop(_Source);
}

void	   Source::Delete()
{
    stop();
    // Destruction du tampon
    alDeleteBuffers(1, &_Buffer);

    // Destruction de la source
    alSourcei(_Source, AL_BUFFER, 0);
    alDeleteSources(1, &_Source);

    // Fermeture d'OpenAL
}

void	   Source::setVolume(float volume)
{
    //change le volume du son (valeur normalisé)
    alSourcef(_Source, AL_GAIN, volume);
}

void	   Source::setPitch(float pitch)
{
    //change le ton du son (1 par defaut)
    alSourcef(_Source, AL_PITCH, pitch);
}

void	   Source::setPosition(float x, float y, float z)
{
    //change la position de la source sonore
    alSource3f(_Source, AL_POSITION, x, y, z);
}

void	   Source::setVelocity(float x, float y, float z)
{
    //change la vitesse de la source sonore
    alSource3f(_Source, AL_VELOCITY, x, y, z);
}

void	   Source::setLooping(bool loop)
{
    //active une boucle
    alSourcei(_Source, AL_LOOPING, loop);
}

void		Source::setBuffer(ALuint buf)
{
	_Buffer = buf;
}

void		Source::setSource(ALuint src)
{
	_Source = src;
}
