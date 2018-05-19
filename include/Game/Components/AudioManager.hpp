#ifndef AUDIOMANAGER_HPP
# define AUDIOMANAGER_HPP

#include "Core/Core.hpp"
#include "Game/Game.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Audio/AudioSource.hpp"
#include "Core/Audio/AudioClip.hpp"

#include "Game/Components/Settings.hpp"

namespace Game
{
	namespace Component
	{
		enum SoundType {
			Music,
			Sound
		};

		class AudioManager : public BeerEngine::Component::Component,
		public BeerEngine::Component::IStart
		{
		private:
			float _soundVolume;
			float _musicVolume;

		public:
			SoundType audioType;

			AudioManager();
			AudioManager(const AudioManager &val);
			AudioManager &operator=(const AudioManager &val);

			AudioManager(BeerEngine::GameObject *gameObject);
			~AudioManager(void);

			void    play();
					void    pause();
					void    continuePlaying();
					void 		setPosition(float x, float y, float z);
			void    setClip(std::string const &filename);
			void    setVolume(float soundVolume, float musicVolume);
			float		getSoundVolume();
			float		getMusicVolume();

			BeerEngine::Audio::AudioSource      srcAudio;
			virtual void start();

			REGISTER_COMPONENT_HPP
		};

	};

};

#endif
