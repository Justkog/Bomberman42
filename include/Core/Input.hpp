#ifndef BE_CORE_INPUT_HPP
#define BE_CORE_INPUT_HPP 1

/*!
 * \file Input.hpp
 * \brief Gestion des entrees, clavier, souris...
 * \author mgallo, jblondea
 */
#include "Core.hpp"
#include "KeyCode.hpp"
/*! \namespace BeerEngine
 * 
 * espace de nommage regroupant les fonctionnalité du moteur
 */
namespace BeerEngine
{
	/*! \class Input
	* \brief classe contenant tout les inputs
	*/
	class Input
	{
	private:
		static std::map<int, int>			mouseButton; /*!< Status des boutons de la souris*/
		static std::map<int, int>			key; /*!< Status des touches du clavier*/
		static std::map<std::string, float> axis; /*!< Valeur des axes*/

	public:
		static std::function<void (int)>	onKeyPushed;
		static glm::vec2	mousePosition; /*!< Position de la souris*/
		static glm::vec2	mouseScroll; /*!< roulette de la souris*/
		/*!
		*  \brief Evenement Clavier
		*  Defini le status de la touche du clavier.
		*  \param keycode : touche du clavier
		*  \param status : status de la touche
		*/
		static void			SetKey(int keycode, int status);
		/*!
		*  \brief Touche appuyer
		*  retourne le status d'un touche
		*  \param keycode : touche du clavier
		*  \retrun true si la touche est appuyer
		*/
		static bool			GetKey(KeyCode keycode);
		/*!
		*  \brief Touche presser
		*  retourne le status d'un touche
		*  \param keycode : touche du clavier
		*  \retrun true si la touche vien d'etre presser
		*/
		static bool			GetKeyDown(KeyCode keycode);
		/*!
		*  \brief Touche relacher
		*  retourne le status d'un touche
		*  \param keycode : touche du clavier
		*  \retrun true si la touche d'etre relacher
		*/
		static bool			GetKeyUp(KeyCode keycode);
		/*!
		*  \brief Touche appuyer
		*  retourne le status d'un touche
		*  \param keycode : touche du clavier
		*  \retrun true si la touche est appuyer
		*/
		static int			GetKeyStatus(KeyCode keycode);
		/*!
		*  \brief Evenement Souris
		*  Defini le status du bouton de la souris.
		*  \param mouseButton : bouton de la souris
		*  \param status : status du bouton
		*/
		static void			SetMouseButton(int mouseButton, int status);
		/*!
		*  \brief bouton appuyer
		*  retourne le status d'un bouton
		*  \param mouseButton : bouton de la souris
		*  \retrun true si le bouton est appuyer
		*/
		static bool			GetMouseButton(int mouseButton);
		/*!
		*  \brief bouton presser
		*  retourne le status d'un bouton
		*  \param mouseButton : bouton de la souris
		*  \retrun true si le bouton est presser
		*/
		static bool			GetMouseButtonDown(int mouseButton);
		/*!
		*  \brief bouton relacher
		*  retourne le status d'un bouton
		*  \param mouseButton : bouton de la souris
		*  \retrun true si le bouton est relacher
		*/
		static bool			GetMouseButtonUp(int mouseButton);
		/*!
		*  \brief Evenement des axes
		*  Defini le status de l'axe
		*  \param name : nom de l'axe
		*  \param value : status de l'axe
		*/
		static void			SetAxis(std::string name, float value);
		/*!
		*  \brief valeur d'un axe
		*  retourne la valeur d'un axe
		*  \param name : nom de l'axe
		*  \retrun la valeur floatante de l'axe
		*/
		static float		GetAxis(std::string name);
		
		static std::function<void (int)> onKeyPushedDefault();

		/*!
		*  \brief mise a jour des entrer
		*  Methode appeler pour mettre a jour les entree. appeler une fois par boucle principal.
		*/
		static void			Update(void);
	};
}

#endif