#include <stdexcept>
#include "Core/Audio/AudioClip.hpp"

namespace BeerEngine
{
	namespace Audio
	{
		AudioClip::AudioClip(const std::string& Filename)
		{
			// Ouverture du fichier audio avec libsndfile
			SF_INFO FileInfos;
			SNDFILE* File = sf_open(Filename.c_str(), SFM_READ, &FileInfos);
			if (!File)
				throw std::runtime_error("Impossible d'ouvrir le fichier audio");

			// Lecture du nombre d'Èchantillons et du taux d'Èchantillonnage (nombre d'Èchantillons ‡ lire par seconde)
			ALsizei NbSamples  = static_cast<ALsizei>(FileInfos.channels * FileInfos.frames);
			ALsizei SampleRate = static_cast<ALsizei>(FileInfos.samplerate);

			// Lecture des Èchantillons audio au format entier 16 bits signÈ (le plus commun)
			std::vector<ALshort> Samples(NbSamples);
			if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples)
				throw std::runtime_error("Impossible de lire les Èchantillons stockÈs dans le fichier audio");

			// Fermeture du fichier
			sf_close(File);

			// DÈtermination du format en fonction du nombre de canaux
			ALenum Format;
			switch (FileInfos.channels)
			{
				case 1 : Format = AL_FORMAT_MONO16;   break;
				case 2 : Format = AL_FORMAT_STEREO16; break;
				default :
					throw std::runtime_error("Format audio non supportÈ (plus de 2 canaux)");
			}

			// CrÈation du tampon OpenAL
			ALuint Buffer;
			alGenBuffers(1, &Buffer);

			// Remplissage avec les Èchantillons lus
			alBufferData(Buffer, Format, &Samples[0], NbSamples * sizeof(ALushort), SampleRate);
			// Verification des erreurs
			if (alGetError() != AL_NO_ERROR)
				throw std::runtime_error("Impossible de remplir le tampon OpenAL avec les Èchantillons du fichier audio");
			_buffer = Buffer;
		}

		AudioClip::~AudioClip()
		{ }

		ALuint		AudioClip::getBuffer()
		{
			return _buffer;
		}
	}
}
