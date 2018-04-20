// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef CAMERACONTROLLER_HPP
# define CAMERACONTROLLER_HPP

namespace Game
{	namespace Component	{		class CameraController
		{
		public:

			CameraController( void );
			CameraController( CameraController const & src );
			virtual ~CameraController( void );

			CameraController & operator=( CameraController const & rhs );
			friend std::ostream & operator<<(std::ostream & o, CameraController const & i);

	
		};

	};

};

#endif
