// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef CAMERACONTROLLER_HPP
# define CAMERACONTROLLER_HPP

#include "Core/Component/Component.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/GameObject.hpp"

namespace Game
{	
	namespace Component	{		
		class CameraController : public BeerEngine::Component::Component, public BeerEngine::Component::IUpdate
		{
		public:

			// CameraController( void );
			// CameraController( CameraController const & src );
			CameraController(BeerEngine::GameObject *gameObject);

			virtual ~CameraController( void );

			CameraController & operator=( CameraController const & rhs );
			friend std::ostream & operator<<(std::ostream & o, CameraController const & i);

			virtual void    fixedUpdate(void);
       		virtual void    update(void);
		};

	};

};

#endif
