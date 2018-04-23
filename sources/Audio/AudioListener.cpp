
#include "Audio/AudioListener.hpp"
#include "Audio/AudioSource.hpp"

AudioListener::AudioListener()
{
    init();
}

AudioListener::~AudioListener()
{
    ShutdownOpenAL();
}

void	   AudioListener::init()
{
    initDevices();
}

void	   AudioListener::initDevices()
{
    int Choice = 0;
    // Recuperation des devices disponibles
    std::vector<std::string> Devices;
    GetDevices(Devices);
    InitOpenAL(Devices[Choice].c_str());
}

bool		AudioListener::InitOpenAL(const char* DeviceName = NULL)
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


void		AudioListener::GetDevices(std::vector<std::string>& Devices)
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


void		AudioListener::ShutdownOpenAL()
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
