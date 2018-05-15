#ifndef GAME_ASSETS_HPP
#define GAME_ASSETS_HPP 1

#include "Core/Core.hpp"

class Assets
{
private:
	static Assets	*_Instance;

public:
	static Assets	*GetInstance(void);

	std::map<std::string, BeerEngine::Audio::AudioClip *>			audioclips;
	std::map<std::string, BeerEngine::Graphics::Texture *>			textures;
	std::map<std::string, BeerEngine::Graphics::Mesh *>				models;
	std::map<std::string, BeerEngine::Graphics::ShaderProgram *>	shaderPrograms;

	BeerEngine::Graphics::AMaterial		*bombMaterial;

	void			autoload(std::string path);
	void			load(void);
	void			unload(void);
	
	static BeerEngine::Audio::AudioClip			*GetAudioClip(std::string path);
	static BeerEngine::Graphics::Texture		*GetTexture(std::string path);
	static BeerEngine::Graphics::Mesh			*GetModel(std::string path);
	static BeerEngine::Graphics::ShaderProgram	*GetShaderProgram(std::string pathVS, std::string pathFS);

};

#endif
