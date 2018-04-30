#include "Game/Assets.hpp"
#include <sys/types.h>
#include <dirent.h>

Assets	*Assets::_Instance = nullptr;

Assets	*Assets::GetInstance(void)
{
	if (_Instance == nullptr)
		_Instance = new Assets();
	return (_Instance);
}

static bool has_suffix(const std::string &str, const std::string &suffix)
{
    return (str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0);
}

void			Assets::autoload(std::string path)
{
	DIR* dirp = opendir(path.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL)
	{
		std::string name(dp->d_name);
		if (dp->d_type == DT_DIR)
		{
			if (name != "." && name != "..")
				autoload(path + "/" + name);
		}
		else if (dp->d_type == DT_REG)
		{
			std::string nameWithPath(path);
			nameWithPath.append("/");
			nameWithPath.append(dp->d_name);
			if (has_suffix(dp->d_name, ".ogg") || has_suffix(dp->d_name, ".wav"))
			{
				audioclips[nameWithPath] = new BeerEngine::Audio::AudioClip(nameWithPath);
				std::cout << "[SOUND] " << nameWithPath << std::endl;
			}
			else if (has_suffix(dp->d_name, ".png"))
			{
				textures[nameWithPath] = BeerEngine::Graphics::Texture::LoadPNG(nameWithPath.c_str());
				std::cout << "[TEXTURE] " << nameWithPath << std::endl;
			}
			else if (has_suffix(dp->d_name, ".bmp"))
			{
				textures[nameWithPath] = BeerEngine::Graphics::Texture::LoadBMP(nameWithPath.c_str());
				std::cout << "[TEXTURE] " << nameWithPath << std::endl;
			}
			else if (has_suffix(dp->d_name, ".tga"))
			{
				textures[nameWithPath] = BeerEngine::Graphics::Texture::LoadTGA(nameWithPath.c_str());
				std::cout << "[TEXTURE] " << nameWithPath << std::endl;
			}
			else if (has_suffix(dp->d_name, ".jpg") || has_suffix(dp->d_name, ".jpeg"))
			{
				textures[nameWithPath] = BeerEngine::Graphics::Texture::LoadJPG(nameWithPath.c_str());
				std::cout << "[TEXTURE] " << nameWithPath << std::endl;
			}
			else if (has_suffix(dp->d_name, ".obj"))
			{
				models[nameWithPath] = BeerEngine::Graphics::Graphics::OBJLoader(nameWithPath);
				std::cout << "[MODEL] " << nameWithPath << std::endl;
			}
		}
    }
    closedir(dirp);
}

void			Assets::load(void)
{
	autoload("assets");
}

void			Assets::unload(void)
{
	for (std::map<std::string, BeerEngine::Audio::AudioClip *>::iterator it = audioclips.begin(); it != audioclips.end(); ++it)
	{
		delete it->second;
	}
	for (std::map<std::string, BeerEngine::Graphics::Texture *>::iterator it = textures.begin(); it != textures.end(); ++it)
	{
		delete it->second;
	}
	for (std::map<std::string, BeerEngine::Graphics::Mesh *>::iterator it = models.begin(); it != models.end(); ++it)
	{
		delete it->second;
	}
}

BeerEngine::Audio::AudioClip		*Assets::GetAudioClip(std::string path)
{
	std::string name("assets/");
	name.append(path);
	return (Assets::GetInstance()->audioclips[name]);
}

BeerEngine::Graphics::Texture		*Assets::GetTexture(std::string path)
{
	std::string name("assets/");
	name.append(path);
	return (Assets::GetInstance()->textures[name]);
}

BeerEngine::Graphics::Mesh			*Assets::GetModel(std::string path)
{
	std::string name("assets/");
	name.append(path);
	return (Assets::GetInstance()->models[name]);
}

