#ifndef BE_CORE_COMPONENT_ISTART_UI_HPP
#define BE_CORE_COMPONENT_ISTART_UI_HPP 1

#include "Core/Core.hpp"

namespace BeerEngine
{
	namespace Component
	{
		class IStartUI
		{
		public:
			 virtual void    startUI(struct nk_context *ctx) = 0;
		};
	}
}

#endif