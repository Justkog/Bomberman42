
#include <cstring>
#include "Core/Audio/AudioListener.hpp"
#include "Core/Audio/AudioSource.hpp"

namespace BeerEngine
{
	namespace Audio
	{
        AudioListener::AudioListener(BeerEngine::GameObject *gameObject) :
			Component(gameObject)
		{ 

        }

        AudioListener::~AudioListener()
        { 
			
        }

        void	   AudioListener::init()
        {
            // int Choice = 0;
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

        void		AudioListener::setListenerData(float x, float y, float z, float dirX, float dirY, float dirZ)
        {
            (void) x;
            (void) y;
            (void) z;
            (void) dirX;
            (void) dirY;
            (void) dirZ;
            // std::cout << "position x = " << x << " y = " << y << " z = " << z << "\n";
            // std::cout << "orientation x = " << dirX << " y = " << dirY << " z = " << dirZ << "\n";
            // ALfloat values[6];
            // values[0] = dirX;
            // values[1] = dirY;
            // values[2] = -dirZ;
            // values[3] = 0;
            // values[4] = 1;
            // values[5] = 0;
            // alListener3f(AL_POSITION, -x, y, z);
            // alListenerfv(AL_ORIENTATION, values);
        }

        void		AudioListener::start(void)
		{
            setListenerData(_gameObject->transform.position.x, _gameObject->transform.position.y, _gameObject->transform.position.z,
                            _gameObject->transform.forward().x, _gameObject->transform.forward().y, _gameObject->transform.forward().z);
		}
	
		void		AudioListener::fixedUpdate(void)
		{

		}

		void		AudioListener::update(void)
		{
            setListenerData(_gameObject->transform.position.x, _gameObject->transform.position.y, _gameObject->transform.position.z,
                            _gameObject->transform.forward().x, _gameObject->transform.forward().y, _gameObject->transform.forward().z);
		}

		nlohmann::json	AudioListener::serialize()
		{
			auto j = Component::serialize();
			j.merge_patch({
				{"componentClass", type},
			});
			return j;
		}

		void AudioListener::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
		{
			Component::deserialize(j, loader);
		}

		REGISTER_COMPONENT_CPP(AudioListener)
    }
}
