#ifndef BE_CORE_TRANSFORM_HPP
#define BE_CORE_TRANSFORM_HPP 1

/*!
 * \file Transform.hpp
 * \brief Component de transformation d'un object
 * \author mgallo
 * \author jblondea
 */

#include "Core.hpp"
#include "Core/Json/JsonSerializable.hpp"
/*! \namespace BeerEngine
 * espace de nommage regroupant les fonctionnalité du moteur
 */
namespace BeerEngine
{
	/*! \class Transform
	* \brief classe representant la transformation d'un object, position, rotation...
	*/
    class Transform : public JsonSerializable
	{
	private:
		Transform(const Transform &val);

	public:
		Transform	*parent; /*!< Transform parent d'un objet*/
		glm::vec3	pivot; /*!< Offset du point de rotation de l'objet*/
		glm::vec3	position; /*!< Position de l'objet dans l'espace*/
		glm::quat	rotation; /*!< Rotation de l'objetr*/
		glm::vec3	scale; /*!< Taille de l'objet*/
		
		static Transform basic;

		/*!
		*  \brief Constructeur
		*  Constructeur de la classe Transform
		*/
		Transform();
		Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

		Transform &operator=(const Transform &val);

		/*!
		*  \brief deplacer l'objet
		*  Methode qui permet de deplacer l'objet grace a un vecteur
		*  \param pos : vecteur
		*/
		void		translate(glm::vec3 pos);
		/*!
		*  \brief deplacer l'objet
		*  Methode qui permet de deplacer l'objet grace au axe x, y et z
		*  \param x : axe x
		*  \param y : axe y
		*  \param z : axe z
		*/
		void		translate(float x, float y, float z);
		/*!
		*  \brief recuperer le vecteur d'avancement
		*  Methode qui permet de recuperer le vecteur d'avancement par rapport a la rotation de l'objet,
		*  \return vecteur d'avancement
		*/
		glm::vec3	forward(void);
		/*!
		*  \brief recuperer le vecteur de gauche
		*  Methode qui permet de recuperer le vecteur de gauche par rapport a la rotation de l'objet,
		*  \return vecteur de gauche
		*/
		glm::vec3	left(void);
		/*!
		*  \brief recuperer le vecteur de droite
		*  Methode qui permet de recuperer le vecteur de par rapport a la rotation de l'objet,
		*  \return vecteur de droite
		*/
		glm::vec3	right(void);
		/*!
		*  \brief recuperer le vecteur du haut
		*  Methode qui permet de recuperer le vecteur du haut par rapport a la rotation de l'objet,
		*  \return vecteur du haut
		*/
		glm::vec3	top(void);

		/*!
		*  \brief recuperer la position dans le monde
		*  Methode qui permet de recuperer le vecteur de position de l'objet dans le monde, en prenant en compte le parents
		*  \return vecteur de position
		*/
		glm::vec3	getWorldPosition();
		/*!
		*  \brief effecteur une rotation
		*  Methode qui permet d'effecter une rotation sur le vecteur donner par rapport a l'objet et ses parents.
		*  \param v : vecteur qui subira la rotation
		*  \return vecteur tourné
		*/
		glm::vec3	getWorldRotate(glm::vec3 v);
		/*!
		*  \brief recupere la matrice de l'objet
		*  Methode qui permet de recuperer la matrice de l'objet
		*  \param isCamera : permet de savoir si c'est une camera pour inverser la formule
		*  \return matrice 4 x 4
		*/
		glm::mat4	getMat4(bool isCamera = false);

		virtual nlohmann::json	serialize();
		virtual void deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader);

		static Transform Deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader);
		static Transform * DeserializePtr(const nlohmann::json & j, BeerEngine::JsonLoader & loader);

	};
}

#endif