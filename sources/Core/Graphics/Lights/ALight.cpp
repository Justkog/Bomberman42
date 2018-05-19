#include "Core/Graphics/Lights/ALight.hpp"
#include "Core/Graphics/ShaderProgram.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		ALight::ALight(int id, AScene &scene)
			: ALight(1.0, glm::vec4(1.0f))
		{}

		ALight::ALight(float intensity, glm::vec4 color)
			: _intensity(intensity), _color(color), _shader(nullptr)
		{}

		ALight::ALight()
		{}

		ALight::ALight(const ALight &val)
		{
			*this = val;
		}
		
		ALight &ALight::operator=(const ALight &val)
		{
			if (this != &val)
			{
				_shader = val._shader;
				_intensity = val._intensity;
				_color = val._color;
				_colorShaderID = val._colorShaderID;
				_albedoID = val._albedoID;
				_hasAlbedoID = val._hasAlbedoID;
				_normalID = val._normalID;
				_hasNormalID = val._hasNormalID;
				_bumpID = val._bumpID;
				_hasBumpID = val._hasBumpID;
				_projectionShaderID = val._projectionShaderID;
				_viewShaderID = val._viewShaderID;
				_modelShaderID = val._modelShaderID;
				_viewPosID = val._viewPosID;
				_viewDirID = val._viewDirID;
				_lightPosID = val._lightPosID;
				_lightDirID = val._lightDirID;
				_lightIntensityID = val._lightIntensityID;
				_lightColorID = val._lightColorID;
				_envMapID = val._envMapID;
				_hasEnvMapID = val._hasEnvMapID;
			}
			return (*this);
		}

		void ALight::setupUniformIds()
		{
			_shader->bind();
			_projectionShaderID = _shader->getUniformLocation("projection");
			_viewShaderID = _shader->getUniformLocation("view");
			_modelShaderID = _shader->getUniformLocation("model");

			_viewPosID = _shader->getUniformLocation("viewPos");
			_viewDirID = _shader->getUniformLocation("viewDir");

			_colorShaderID = _shader->getUniformLocation("color");
			_albedoID = _shader->getUniformLocation("albedo");
			_hasAlbedoID = _shader->getUniformLocation("hasAlbedo");
			_normalID = _shader->getUniformLocation("normal");
			_hasNormalID = _shader->getUniformLocation("hasNormal");
			_bumpID = _shader->getUniformLocation("bump");
			_hasBumpID = _shader->getUniformLocation("hasBump");

			_envMapID = _shader->getUniformLocation("envMap");
			_hasEnvMapID = _shader->getUniformLocation("hasEnvMap");

			_lightPosID = _shader->getUniformLocation("light.position");
			_lightDirID = _shader->getUniformLocation("light.direction");
			_lightIntensityID = _shader->getUniformLocation("light.intensity");
			_lightColorID = _shader->getUniformLocation("light.color");
		}

		ALight			&ALight::setColor(glm::vec4 color)
		{
			_color = color;
			return (*this);
		}

		ALight			&ALight::setIntensity(float val)
		{
			_intensity = val;
			return (*this);
		}

		const glm::vec4		&ALight::getColor() const
		{
			return (_color);
		}

		float			ALight::getIntensity() const
		{
			return (_intensity);
		}

		ShaderProgram	&ALight::getShader() const
		{
			return *_shader;
		}

		nlohmann::json	ALight::serialize()
		{
			return {};
		}

		void ALight::deserialize(const nlohmann::json & j)
		{

		}

		ALight * ALight::Deserialize(const nlohmann::json & j)
		{
			return nullptr;
		}

		GLint ALight::get_colorShaderID() const {
			return _colorShaderID;
		}

		GLint ALight::get_albedoID() const {
			return _albedoID;
		}

		GLint ALight::get_hasAlbedoID() const {
			return _hasAlbedoID;
		}

		GLint ALight::get_normalID() const {
			return _normalID;
		}

		GLint ALight::get_hasNormalID() const {
			return _hasNormalID;
		}

		GLint ALight::get_bumpID() const {
			return _bumpID;
		}

		GLint ALight::get_hasBumpID() const {
			return _hasBumpID;
		}

		GLint ALight::get_projectionShaderID() const {
			return _projectionShaderID;
		}

		GLint ALight::get_viewShaderID() const {
			return _viewShaderID;
		}

		GLint ALight::get_modelShaderID() const {
			return _modelShaderID;
		}

		GLint ALight::get_viewPosID() const {
			return _viewPosID;
		}

		GLint ALight::get_viewDirID() const {
			return _viewDirID;
		}

		GLint ALight::get_lightPosID() const {
			return _lightPosID;
		}

		GLint ALight::get_lightDirID() const {
			return _lightDirID;
		}

		GLint ALight::get_envMapID() const {
			return _envMapID;
		}

		GLint ALight::get_hasEnvMapID() const {
			return _hasEnvMapID;
		}
	}
}
