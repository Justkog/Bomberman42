/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AudioMaster.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <stmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:46:42 by stmartin          #+#    #+#             */
/*   Updated: 2018/04/18 19:20:02 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Audio/AudioMaster.hpp"

AudioMaster::AudioMaster()
{
	InitOpenAL();
}

AudioMaster::~AudioMaster()
{ }


bool		AudioMaster::InitOpenAL()
{
    // Ouverture du device
    ALCdevice* Device = alcOpenDevice(NULL);
    if (!Device)
        return false;

    // Création du contexte
    ALCcontext* Context = alcCreateContext(Device, NULL);
    if (!Context)
        return false;

    // Activation du contexte
    if (!alcMakeContextCurrent(Context))
        return false;

    return true;
}


void		AudioMaster::GetDevices(std::vector<std::string>& Devices)
{
    // Vidage de la liste
    Devices.clear();

    // Récupération des devices disponibles
    const ALCchar* DeviceList = alcGetString(NULL, ALC_DEVICE_SPECIFIER);

    if (DeviceList)
    {
        // Extraction des devices contenus dans la chaîne renvoyée
        while (strlen(DeviceList) > 0)
        {
            Devices.push_back(DeviceList);
            DeviceList += strlen(DeviceList) + 1;
        }
    }
}


void		AudioMaster::ShutdownOpenAL()
{
    // Récupération du contexte et du device
    ALCcontext* Context = alcGetCurrentContext();
    ALCdevice*  Device  = alcGetContextsDevice(Context);

    // Désactivation du contexte
    alcMakeContextCurrent(NULL);

    // Destruction du contexte
    alcDestroyContext(Context);

    // Fermeture du device
    alcCloseDevice(Device);
}

// void		AudioMaster::init()
// {
	// int channel, samplerate, bps, size;
	// unsigned int bufId, format, sourceId;

	// try
	// {
		// create();

        // ALCdevice * device = alcOpenDevice(NULL);
        // if (device == NULL)
        //     throw std::runtime_error("device is NULL !");
        // ALCcontext * context = alcCreateContext(device, NULL);
        // if (context == NULL)
        //     throw std::runtime_error("context is NULL !");
        // alcMakeContextCurrent(context);
        //
        // alGenBuffers(1, &bufId);
		// char * data = loadWAV("sample.wav", channel, samplerate, bps, size);
        // if (channel == 1) // it's mono
        // {
        //     if (bps == 8)
        //         format = AL_FORMAT_MONO8;
        //     else if (bps == 16)
        //         format = AL_FORMAT_MONO16;
        // }
        // else // it's stereo
        // {
        //     if (bps == 8)
        //         format = AL_FORMAT_STEREO8;
        //     else if (bps == 16)
        //         format = AL_FORMAT_STEREO16;
        // }
        // alBufferData(bufId, format, data, size, samplerate);
        // alGenSources(1, &sourceId);
        // alSourcei(sourceId, AL_BUFFER, bufId);
        // alSourcePlay(sourceId);
        //
        // // using namespace std::this_thread; // sleep_for, sleep_until
        // // using namespace std::chrono; // nanoseconds, system_clock, seconds
        // //
        // // sleep_for(nanoseconds(10));
        // // sleep_until(system_clock::now() + seconds(3));
        //
        // alDeleteSources(1, &sourceId);
        // alDeleteBuffers(1, &bufId);
        // alcDestroyContext(context);
        // alcCloseDevice(device);
        // delete [] data;
// 	}
// 	catch (std::runtime_error &e)
// 	{
// 		std::cout << e.what() << std::endl;
// 	}
// }

// int			AudioMaster::loadSound(std::string file)
// {
// 	unsigned int bufId, format, sourceId;
//
// 	alGenBuffers(1, &bufId);
//
// }
//
//
// bool		AudioMaster::isBigEndian()
// {
// 	int a = 1;
// 	return !((char *)&a)[0];
// }
//
// int		AudioMaster::convertToInt(char *buf, int len)
// {
// 	int a = 0;
// 	if (isBigEndian())
// 	{
// 		for (int i = 0; i < len;i++)
// 			((char *)&a)[i] = buf[i];
// 	}
// 	else
// 	{
// 		for (int i = 0; i < len;i++)
// 			((char *)&a)[i - 3] = buf[i];
// 	}
// 	return a;
// }
//
// char        *AudioMaster::loadWAV(const char * fn, int & chan, int & samplerate, int & bps, int & size)
// {
//     char buf[4];
//
//     std::ifstream in(fn, std::ios::binary);
//     in.read(buf, 4);
//     std::cout << buf[0] << buf[1] << buf[2] << buf[3] << std::endl;
// 	if (strncmp(buf, "RIFF", 4))
// 		throw std::runtime_error("not a wav file");
// 	in.read(buf, 4);
// 	// std::cout << buf[0] << buf[1] << buf[2] << buf[3] << std::endl;
// 	in.read(buf, 4); //wave
//     // std::cout << buf[0] << buf[1] << buf[2] << buf[3] << std::endl;
// 	in.read(buf, 4); //fmt
//     // std::cout << buf[0] << buf[1] << buf[2] << buf[3] << std::endl;
// 	in.read(buf, 4); // 16
// 	// std::cout << buf[0] << buf[1] << buf[2] << buf[3] << std::endl;
// 	in.read(buf, 2); //1
//     // std::cout << buf[0] << buf[1] << std::endl;
// 	in.read(buf, 2);
// 	chan = convertToInt(buf, 2);
//     std::cout << "chan : " <<chan << std::endl;
// 	in.read(buf, 4);
// 	samplerate = convertToInt(buf, 4);
//     std::cout << "samplerate : "<< samplerate << std::endl;
// 	in.read(buf, 4);
// 	// std::cout << buf[0] << buf[1] << buf[2] << buf[3] << std::endl;
// 	in.read(buf, 2);
// 	// std::cout << buf[0] << buf[1] << std::endl;
// 	in.read(buf, 2);
// 	bps = convertToInt(buf, 2);
//     std::cout << "bps : " << bps << std::endl;
// 	in.read(buf, 4); //data
// 	// std::cout << buf[0] << buf[1] << buf[2] << buf[3] << std::endl;
// 	in.read(buf, 4);
// 	size = convertToInt(buf, 4);
//     std::cout << "size : "<< size << std::endl;
// 	char *data = new char[size];
//     in.read(data, size);
// 	return (data);
// }
