#ifndef CORE_GENERIC_HPP
#define CORE_GENERIC_HPP 1
/*!
 * \file GenericScene.hpp
 * \brief Scene generique du projet
 * \author jblondea
 */
#include "Core/Core.hpp"
#include "Core/AScene.hpp"
/*! \class GenericScene
* \brief Classe d'ine scene generique.
*/
class GenericScene : public BeerEngine::AScene
{
public:
	void    init(void);

};

#endif
