
#include "Core/Audio/AudioListener.hpp"
#include "Core/Audio/AudioSource.hpp"

namespace BeerEngine
{
	namespace Audio
	{
        AudioListener::AudioListener()
        { }

        AudioListener::~AudioListener()
        { }

        void	   AudioListener::init()
        {
            int Choice = 0;
            // Recuperation des devices disponibles
            std::vector<std::string> Devices;
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
            // Ouverture du device
            ALCdevice* Device = alcOpenDevice(NULL);
            if (!Device)
                throw std::runtime_error("No device opened !");

            // Création du contexte
            ALCcontext* Context = alcCreateContext(Device, NULL);
            if (!Context)
                throw std::runtime_error("Context is empty !");

            // Activation du contexte
            if (!alcMakeContextCurrent(Context))
                throw std::runtime_error("Context activation failed !");
        }

        void		AudioListener::DestroyOpenAL()
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

        void		AudioListener::setListenerData(float x, float y, float z)
        {
            alListener3f(AL_POSITION, x, y, z);
            alListener3f(AL_VELOCITY, x, y, z);
        }
    }
}
