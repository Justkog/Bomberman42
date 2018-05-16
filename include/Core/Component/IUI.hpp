#ifndef BE_CORE_COMPONENT_IUI_HPP
#define BE_CORE_COMPONENT_IUI_HPP 1
/*!
 * \file IUI.hpp
 * \brief Interface de rendu de l'UI
 * \author mgallo
 */
#include "Core/Core.hpp"

namespace BeerEngine
{
	namespace Component
	{
		/*! \class IUI
		* \brief Interface de rendu de l'UI d'un component
		*/
		class IUI
		{
		public:
			 virtual void    renderUI(struct nk_context *ctx) = 0;
		};
	}
}

#endif