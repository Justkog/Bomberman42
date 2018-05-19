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

			CameraController();
			CameraController(const CameraController &val);
			CameraController & operator=( CameraController const & rhs );

		public:
			CameraController(BeerEngine::GameObject *gameObject);
			virtual ~CameraController( void );

			friend std::ostream & operator<<(std::ostream & o, CameraController const & i);

			virtual void    start(void);
			virtual void    fixedUpdate(void);
       		virtual void    update(void);

			BeerEngine::Camera	*cam;
			glm::vec2			lastMousePos;

			bool				tpsCamera;

			REGISTER_COMPONENT_HPP
		};

	};

};

#endif
