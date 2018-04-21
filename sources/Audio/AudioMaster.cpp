
#include "Audio/AudioMaster.hpp"
#include "Audio/Source.hpp"

AudioMaster::AudioMaster()
{
        initDevices();
}

AudioMaster::~AudioMaster()
{
    ShutdownOpenAL();
}

void	   AudioMaster::initDevices()
{
    int Choice = 0;
    // Recuperation des devices disponibles
    std::vector<std::string> Devices;
    GetDevices(Devices);
    InitOpenAL(Devices[Choice].c_str());
}

bool		AudioMaster::InitOpenAL(const char* DeviceName = NULL)
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


ALuint      AudioMaster::LoadSound(const std::string& Filename)
{
    // Ouverture du fichier audio avec libsndfile
    SF_INFO FileInfos;
    SNDFILE* File = sf_open(Filename.c_str(), SFM_READ, &FileInfos);
    if (!File)
    {
        std::cerr << "Impossible d'ouvrir le fichier audio" << std::endl;
        return 0;
    }

    // Lecture du nombre d'Èchantillons et du taux d'Èchantillonnage (nombre d'Èchantillons ‡ lire par seconde)
    ALsizei NbSamples  = static_cast<ALsizei>(FileInfos.channels * FileInfos.frames);
    ALsizei SampleRate = static_cast<ALsizei>(FileInfos.samplerate);

    // Lecture des Èchantillons audio au format entier 16 bits signÈ (le plus commun)
    std::vector<ALshort> Samples(NbSamples);
    if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples)
    {
        std::cerr << "Impossible de lire les Èchantillons stockÈs dans le fichier audio" << std::endl;
        return 0;
    }

    // Fermeture du fichier
    sf_close(File);

    // DÈtermination du format en fonction du nombre de canaux
    ALenum Format;
    switch (FileInfos.channels)
    {
        case 1 : Format = AL_FORMAT_MONO16;   break;
        case 2 : Format = AL_FORMAT_STEREO16; break;
        default :
            std::cerr << "Format audio non supportÈ (plus de 2 canaux)" << std::endl;
            return 0;
    }

    // CrÈation du tampon OpenAL
    ALuint Buffer;
    alGenBuffers(1, &Buffer);

    // Remplissage avec les Èchantillons lus
    alBufferData(Buffer, Format, &Samples[0], NbSamples * sizeof(ALushort), SampleRate);
// std::cout << Buffer << " " << Format << " " << Samples[0] << " " << NbSamples * sizeof(ALushort) << " " << SampleRate << std::endl;
    // Verification des erreurs
    if (alGetError() != AL_NO_ERROR)
    {
        std::cerr << "Impossible de remplir le tampon OpenAL avec les Èchantillons du fichier audio" << std::endl;
        return 0;
    }

    return Buffer;
}


void		AudioMaster::setListenerData(float x, float y, float z)
{
    alListener3f(AL_POSITION, x, y, z);
    alListener3f(AL_VELOCITY, x, y, z);
}








//
//
// #include "Audio/AudioMaster.hpp"
//
// AudioMaster::AudioMaster()
// {
// 	entryPoint();
// }
//
// AudioMaster::~AudioMaster()
// { }
//
//
// bool		AudioMaster::InitOpenAL(const char* DeviceName = NULL)
// {
//     // Ouverture du device
//     ALCdevice* Device = alcOpenDevice(NULL);
//     if (!Device)
//         return false;
//
//     // Création du contexte
//     ALCcontext* Context = alcCreateContext(Device, NULL);
//     if (!Context)
//         return false;
//
//     // Activation du contexte
//     if (!alcMakeContextCurrent(Context))
//         return false;
//
//     return true;
// }
//
//
// void		AudioMaster::GetDevices(std::vector<std::string>& Devices)
// {
//     // Vidage de la liste
//     Devices.clear();
//
//     // Récupération des devices disponibles
//     const ALCchar* DeviceList = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
//
//     if (DeviceList)
//     {
//         // Extraction des devices contenus dans la chaîne renvoyée
//         while (strlen(DeviceList) > 0)
//         {
//             Devices.push_back(DeviceList);
//             DeviceList += strlen(DeviceList) + 1;
//         }
//     }
// }
//
//
// void		AudioMaster::ShutdownOpenAL()
// {
//     // Récupération du contexte et du device
//     ALCcontext* Context = alcGetCurrentContext();
//     ALCdevice*  Device  = alcGetContextsDevice(Context);
//
//     // Désactivation du contexte
//     alcMakeContextCurrent(NULL);
//
//     // Destruction du contexte
//     alcDestroyContext(Context);
//
//     // Fermeture du device
//     alcCloseDevice(Device);
// }
//
//
// ALuint		AudioMaster::LoadSound(const std::string& Filename)
// {
//     // Ouverture du fichier audio avec libsndfile
//     SF_INFO FileInfos;
//     SNDFILE* File = sf_open(Filename.c_str(), SFM_READ, &FileInfos);
//
// 	if (!File)
//     {
//         std::cerr << "Impossible d'ouvrir le fichier audio" << std::endl;
//         return 0;
//     }
//
// 	// Lecture du nombre d'échantillons et du taux d'échantillonnage (nombre d'échantillons à lire par seconde)
//     ALsizei NbSamples  = static_cast<ALsizei>(FileInfos.channels * FileInfos.frames);
//     ALsizei SampleRate = static_cast<ALsizei>(FileInfos.samplerate);
//
// 	// Lecture des échantillons audio au format entier 16 bits signé (le plus commun)
//     std::vector<ALshort> Samples(NbSamples);
// 	if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples)
//     {
//         std::cerr << "Impossible de lire les �chantillons stock�s dans le fichier audio" << std::endl;
//         return 0;
//     }
// 	// Fermeture du fichier
// 	sf_close(File);
// 	// Détermination du format en fonction du nombre de canaux
//     ALenum Format;
//     switch (FileInfos.channels)
//     {
//         case 1 :  Format = AL_FORMAT_MONO16;   break;
//         case 2 :  Format = AL_FORMAT_STEREO16; break;
// 		default :
//             std::cerr << "Format audio non support� (plus de 2 canaux)" << std::endl;
//             return 0;
//     }
//
// 	// Création du tampon OpenAL
// 	ALuint Buffer;
// 	alGenBuffers(1, &Buffer);
//
// 	// Remplissage avec les échantillons lus
//     alBufferData(Buffer, Format, &Samples[0], NbSamples * sizeof(ALushort), SampleRate);
//
//     // Vérification des erreurs
// 	if (alGetError() != AL_NO_ERROR)
//     {
//         std::cerr << "Impossible de remplir le tampon OpenAL avec les �chantillons du fichier audio" << std::endl;
//         return 0;
//     }
//
//     return Buffer;
// }
//
// int			AudioMaster::entryPoint()
// {
// 	int Choice = 0;
//
//     // Recuperation des devices disponibles
//     std::vector<std::string> Devices;
//     GetDevices(Devices);
//
//     // On affiche la liste de device de l'utilisateur
// 	if (Devices.size() > 1)
//     {
// 		std::cout << "Veuillez choisir un device :" << std::endl << std::endl;
//     	for (std::size_t i = 0; i < Devices.size(); ++i)
//         	std::cout << "[" << i << "] " << Devices[i] << std::endl;
//
// 	    // Et on le laisse choisir
// 	    std::cout << "choose the device : ";
// 		std::cin >> Choice;
// 	}
//
//     // Initialisation d'OpenAL
//     InitOpenAL(Devices[Choice].c_str());
//
//     // Chargement du fichier audio
//     ALuint Buffer = LoadSound("assets/sounds/ds_brush_snare.wav");
//     if (Buffer == 0)
//         return EXIT_FAILURE;
//
//     // Cr�ation d'une source
//     ALuint Source;
//     alGenSources(1, &Source);
//     alSourcei(Source, AL_BUFFER, Buffer);
//
//     // On joue le son
//
//     alSourcePlay(Source);
//
//     // On attend qu'il soit termin�
//     ALint Status;
//     do
//     {
//         // R�cup�ration de l'�tat du son
//
//
//
// 	    alGetSourcei(Source, AL_SOURCE_STATE, &Status);
//     }
//     while (Status == AL_PLAYING);
//
//     // Destruction du tampon
//     alDeleteBuffers(1, &Buffer);
//
//     // Destruction de la source
//     alSourcei(Source, AL_BUFFER, 0);
//     alDeleteSources(1, &Source);
//
//     // Fermeture d'OpenAL
//     ShutdownOpenAL();
//
//     return EXIT_SUCCESS;
// }
