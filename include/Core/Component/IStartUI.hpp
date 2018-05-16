#ifndef BE_CORE_COMPONENT_ISTART_UI_HPP
#define BE_CORE_COMPONENT_ISTART_UI_HPP 1
/*!
 * \file IStartUI.hpp
 * \brief 
 * \author jblondea
 */
#include "Core/Core.hpp"

namespace BeerEngine
{
	namespace Component
	{
		/*! \class IStartUI
		* \brief 
		*/
		class IStartUI
		{
		public:
			 virtual void    startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts) = 0;
		};
	}
}

#endif