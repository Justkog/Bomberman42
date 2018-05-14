#include "Game/Assets.hpp"
#include <sys/types.h>
#include <dirent.h>
#include "Core/Audio/AudioClip.hpp"
#include "Core/Graphics/Texture.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/Graphics/AMaterial.hpp"

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
				std::cout << "[SOUND] " << nameWithPath << std::endl;
				audioclips[nameWithPath] = new BeerEngine::Audio::AudioClip(nameWithPath);
			}
			else if (has_suffix(dp->d_name, ".png"))
			{
				std::cout << "[TEXTURE] " << nameWithPath << std::endl;
				textures[nameWithPath] = BeerEngine::Graphics::Texture::LoadPNG(nameWithPath.c_str());
			}
			else if (has_suffix(dp->d_name, ".bmp"))
			{
				std::cout << "[TEXTURE] " << nameWithPath << std::endl;
				textures[nameWithPath] = BeerEngine::Graphics::Texture::LoadBMP(nameWithPath.c_str());
			}
			else if (has_suffix(dp->d_name, ".tga"))
			{
				std::cout << "[TEXTURE] " << nameWithPath << std::endl;
				textures[nameWithPath] = BeerEngine::Graphics::Texture::LoadTGA(nameWithPath.c_str());
			}
			else if (has_suffix(dp->d_name, ".jpg") || has_suffix(dp->d_name, ".jpeg"))
			{
				std::cout << "[TEXTURE] " << nameWithPath << std::endl;
				textures[nameWithPath] = BeerEngine::Graphics::Texture::LoadJPG(nameWithPath.c_str());
			}
			else if (has_suffix(dp->d_name, ".obj"))
			{
				std::cout << "[MODEL] " << nameWithPath << std::endl;
				models[nameWithPath] = BeerEngine::Graphics::Graphics::OBJLoader(nameWithPath);
			}
		}
    }
    closedir(dirp);
}

void			Assets::load(void)
{
	// autoload("assets");
	bombMaterial = new BeerEngine::Graphics::AMaterial(BeerEngine::Graphics::Graphics::defaultShader);
	// auto *bombTexture = Assets::GetTexture("assets/models/Bomb/bombbody_BaseColor.png");
	// bombMaterial->setAlbedo(bombTexture);
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
	// std::string name("assets/");
	// name.append(path);
	std::string name(path);
	// return (Assets::GetInstance()->audioclips[name]);
	if (Assets::GetInstance()->audioclips.find(name) != Assets::GetInstance()->audioclips.end())
		return (Assets::GetInstance()->audioclips[name]);
	else
	{
		std::cout << "[SOUND] " << name << std::endl;
		return Assets::GetInstance()->audioclips[name] = new BeerEngine::Audio::AudioClip(name);
	}
}

BeerEngine::Graphics::Texture		*Assets::GetTexture(std::string path)
{
	// std::string name("assets/");
	// name.append(path);
	std::string name(path);
	// return (Assets::GetInstance()->textures[name]);
	if (Assets::GetInstance()->textures.find(name) != Assets::GetInstance()->textures.end())
		return (Assets::GetInstance()->textures[name]);
	else
	{
		if (has_suffix(name, ".png"))
		{
			std::cout << "[TEXTURE] " << name << std::endl;
			return Assets::GetInstance()->textures[name] = BeerEngine::Graphics::Texture::LoadPNG(name.c_str());
		}
		else if (has_suffix(name, ".bmp"))
		{
			std::cout << "[TEXTURE] " << name << std::endl;
			return Assets::GetInstance()->textures[name] = BeerEngine::Graphics::Texture::LoadBMP(name.c_str());
		}
		else if (has_suffix(name, ".tga"))
		{
			std::cout << "[TEXTURE] " << name << std::endl;
			return Assets::GetInstance()->textures[name] = BeerEngine::Graphics::Texture::LoadTGA(name.c_str());
		}
		else if (has_suffix(name, ".jpg") || has_suffix(name, ".jpeg"))
		{
			std::cout << "[TEXTURE] " << name << std::endl;
			return Assets::GetInstance()->textures[name] = BeerEngine::Graphics::Texture::LoadJPG(name.c_str());
		}
		else
			return NULL;
	}
}

BeerEngine::Graphics::Mesh			*Assets::GetModel(std::string path)
{
	// std::string name("assets/");
	// name.append(path);
	std::string name(path);
	// return (Assets::GetInstance()->models[name]);
	if (Assets::GetInstance()->models.find(name) != Assets::GetInstance()->models.end())
		return (Assets::GetInstance()->models[name]);
	else
	{
		std::cout << "[MODEL] " << name << std::endl;
		return Assets::GetInstance()->models[name] = BeerEngine::Graphics::Graphics::OBJLoader(name);
	}
}

BeerEngine::Graphics::ShaderProgram			*Assets::GetShaderProgram(std::string pathVS, std::string pathFS)
{
	// std::string name("assets/");
	// name.append(path);
	std::string name = pathVS + pathFS;
	// return (Assets::GetInstance()->ShaderPrograms[name]);
	if (Assets::GetInstance()->shaderPrograms.find(name) != Assets::GetInstance()->shaderPrograms.end())
		return (Assets::GetInstance()->shaderPrograms[name]);
	else
	{
		std::cout << "[SHADER PROGRAM] " << name << std::endl;
		return Assets::GetInstance()->shaderPrograms[name] = BeerEngine::Graphics::ShaderProgram::LoadShader(pathVS, pathFS);
	}
}


