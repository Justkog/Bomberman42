#ifndef BE_CORE_COMPONENT_IUI_HPP
#define BE_CORE_COMPONENT_IUI_HPP 1

#include "Core/Core.hpp"

namespace BeerEngine
{
	namespace Component
	{
		class IUI
		{
		public:
			 virtual void    renderUI(struct nk_context *ctx) = 0;
		};
	}
}

#endif