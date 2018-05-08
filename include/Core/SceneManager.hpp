#ifndef BE_CORE_SCENEMANAGER_HPP
#define BE_CORE_SCENEMANAGER_HPP 1
/*!
 * \file SceneManager.hpp
 * \brief Gestionaire des Scene du projet
 * \author mgallo
 */
#include "Core.hpp"
#include "AScene.hpp"
/*! \namespace BeerEngine
 * espace de nommage regroupant les fonctionnalité du moteur
 */
namespace BeerEngine
{
    /*! \class SceneManager
	* \brief classe manager qui permet de gerer les scenes du projet
	*/
    class SceneManager
    {
    private:
        static AScene      *_Current; /*!< Scene actuellement utiliser*/

    public:
        /*!
		*  \brief recuperer la scene courent
		*  Methode qui permet de recuperer la scene actuellement utiliser sur le projet
		*  \return scene
		*/
        static AScene       *GetCurrent(void);
        /*!
		*  \brief changer de scene
		*  Methode qui permet de changer de scene par le biais du template
		*/
        template<typename T, typename std::enable_if<std::is_base_of<AScene, T>::value>::type* = nullptr>
        static void         LoadScene(void)
        {
            if (_Current != nullptr)
                delete _Current;
            _Current = new T();
            _Current->init();
            _Current->debugTest();
            // _Current->start();
        }
    };
}

#endif