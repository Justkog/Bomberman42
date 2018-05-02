#include "Core/Component/RaysRenderer.hpp"
#include "Core/Input.hpp"
#include "Core/Window.hpp"
#include "Core/Camera.hpp"
#include "Core/Graphics/MeshBuilder.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/Graphics/Mesh.hpp"
#include "Core/Component/MeshRenderer.hpp"
#include "Core/IO/FileUtils.hpp"
#include "Core/Graphics/AMaterial.hpp"
#include "Core/Physics/Physics.hpp"

namespace BeerEngine
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

/*RaysRenderer::RaysRenderer ( void )
{
	return ;
}*/

/*RaysRenderer::RaysRenderer ( RaysRenderer const & src )
{
	*this = src;
	return ;
}*/

RaysRenderer &				RaysRenderer::operator=( RaysRenderer const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

RaysRenderer::~RaysRenderer ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

RaysRenderer::RaysRenderer(BeerEngine::GameObject *gameObject) :
MeshRenderer(gameObject)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, RaysRenderer const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void RaysRenderer::start()
{
	std::cout << "RaysRenderer start" << std::endl;
	old_size = 0;

	BeerEngine::Graphics::AMaterial *material = new BeerEngine::Graphics::AMaterial(BeerEngine::Graphics::Graphics::loadLineShader());
	material->setColor(glm::vec4(0.5f, 1.0f, 1.0f, 1.0f));
	this->setMaterial(material);
	this->renderMode = GL_LINES;
}

void RaysRenderer::RebuildMesh()
{
	BeerEngine::Graphics::MeshBuilder builder;
	for (int i = 0; i < rays.size(); i++)
	{
		auto rayEndPos = rays[i].origin + rays[i].direction;
		builder
		.addVertice(rays[i].origin)
		.addVertice(rayEndPos)
		;
	}

	auto lines = builder.build();
	this->setMesh(lines);
}

void RaysRenderer::renderUpdate(void)
{
	MeshRenderer::renderUpdate();
	if (old_size != rays.size())
	{
		RebuildMesh();
		old_size = rays.size();
	}
}

void RaysRenderer::addRay(Physics::Ray ray)
{
	rays.push_back(ray);
}

// ###############################################################

// GETTER METHOD #################################################

// ###############################################################

// SETTER METHOD #################################################

// ###############################################################

// PRIVATE METHOD ################################################

// ###############################################################

// EXCEPTION METHOD ##############################################

// ###############################################################

// EXTERNAL ######################################################

// ###############################################################
	}
}
