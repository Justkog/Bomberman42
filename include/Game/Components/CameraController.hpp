// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef CAMERACONTROLLER_HPP
# define CAMERACONTROLLER_HPP

/*!
 * \file CameraController.hpp
 * \brief Controleur de la camera
 * \author jblondea
 */

#include "Core/Core.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IUpdate.hpp"

namespace Game
{	
	namespace Component	{		
		class CameraController : public BeerEngine::Component::Component, public BeerEngine::Component::IUpdate, public BeerEngine::Component::IStart
		{
		private:
			void syncCam();

		public:

			// CameraController( void );
			// CameraController( CameraController const & src );
			CameraController(BeerEngine::GameObject *gameObject);

			virtual ~CameraController( void );

			CameraController & operator=( CameraController const & rhs );
			friend std::ostream & operator<<(std::ostream & o, CameraController const & i);

			virtual void    start(void);
			virtual void    fixedUpdate(void);
       		virtual void    update(void);

			BeerEngine::Camera	*cam;
			glm::vec2			lastMousePos;

			REGISTER_COMPONENT_HPP
		};

	};

};

#endif
