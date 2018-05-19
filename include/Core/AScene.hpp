#ifndef BE_CORE_ASCENE_HPP
#define BE_CORE_ASCENE_HPP 1
/*!
 * \file AScene.hpp
 * \brief Composition des scenes
 * \author mgallo, jblondea, mploux, qhonore
 */
#include <Core/Graphics/Cubemap.hpp>
#include "Core.hpp"
#include "Core/Json/JsonSerializable.hpp"

struct nk_font;
/*! \namespace BeerEngine
 * 
 * espace de nommage regroupant les fonctionnalité du moteur
 */
namespace BeerEngine
{
    /*! \class AScene
	* \brief classe des scenes, toute scene herite de celle-ci pour le fonctionnement correct des scenes.
	*/
    class AScene : public JsonSerializable
    {
    private:
        static int                  uniqueID; /*!< Generation d'un id unique pour chaque objet de la scene*/
        std::map<int, GameObject *> _gameObjects; /*!< List des objets de la scne*/
        std::map<int, Graphics::ALight *>   _lights;
        std::vector<GameObject *>   _toDestroy; /*!< List des objets allant a la destruction*/
        std::vector<GameObject *>   _toStart; /*!< List des objets allant a l'initilisation*/
        std::vector<GameObject *>   _toStartUI; 
        std::mutex                  updateMutex; /*!< Protection pour le traitement de multiple thread*/
		Graphics::Cubemap					*_skyboxCubemap;
        
    public:
        std::string                 filePath; /*!< Chemin du fichier ou la scene est sauvegarder*/
        /*!
		*  \brief Constructeur
		*  Constructeur de la classe AScene
		*/
        AScene(void);
		AScene(const AScene &val);
		AScene &operator=(const AScene &val);

        /*!
		*  \brief Destructeur
		*  Destructeur de la classe AScene
		*/
        virtual ~AScene(void);
        /*!
		*  \brief initialisation
		*  Initialisation de la classe heritante.
		*/
        virtual void    init(void) = 0;
        /*!
		*  \brief gestion de la protection
		*  Activer ou desactiver la protection de la classe pour le multi thread
        *  \param lock : status du mutex
		*/
        void    mutexLock(bool lock);
        /*!
		*  \brief initialisation des objets
		*  Methode permettant d'initialiser les objets creer.
		*/
        void    start(void);
        void    startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
        /*!
		*  \brief update fix des objets
		*  Methode permettant de mettre a jour les objets de maniere fixe (60 fois pas seconde par defaut).
		*/
        void    fixedUpdate(void);
        /*!
		*  \brief update des objets
		*  Methode permettant de mettre a jour les objets.
		*/
        void    update(void);
        /*!
		*  \brief data de rendu des objets
		*  Methode permettant de mettre a jour les données de rendu des objets
		*/
        void    renderUpdate(void);
        /*!
		*  \brief rendu des objets
		*  Methode permettant de rendre l'objet a l'ecran
		*/
        void    render(void);
        void    renderForward(void);
		/*!
		*  \brief rendu de l'UI
		*  Methode permettant de rendre UI de l'objet a l'ecran
		*/
        void    renderUI(struct nk_context *ctx);

		/*!
		*  \brief Rendu des ombres
		*  Methode permettant de rendre les objets qui aurons des ombres 
		*/
        void    renderShadows(void);
        /*!
		*  \brief Mise a jour physique
		*  Methode permettant de mettre a jour la physique des objets (collision ...)
		*/
        void    physicUpdate(void);
        /*!
		*  \brief demande de destruction d'un objet
		*  Methode permettant d'ajouter dans la pile des destruction un objet
		*/
        void    destroy(GameObject *go);
        /*!
		*  \brief destruction des objets
		*  Methode permettant de detruire les objets de la pile de destruction, puis vite la pile
		*/
        void    destroyGameObjects(void);
        /*!
		*  \brief instancie un objet
		*  Methode permettant de creer un nouvelle objet dans la scene
        *  \return l'objet venant d'etre creer
		*/
        template<typename T, typename std::enable_if<std::is_base_of<GameObject, T>::value>::type* = nullptr>
		T	*instantiate(void)
		{
			std::cout << "GameObject added : " << uniqueID << std::endl;
			T *c = new T(uniqueID, *this);
			_gameObjects.insert(std::pair<int, GameObject *>(uniqueID, c));
            _toStart.push_back(c);
            _toStartUI.push_back(c);
            uniqueID++;
			return (c);
		}
        /*!
		*  \brief instancie un objet
		*  Methode permettant de creer un nouvelle objet dans la scene par rapport a un objet predefini
        *  \return l'objet venant d'etre creer
		*/
        template<typename T, typename std::enable_if<std::is_base_of<GameObject, T>::value>::type* = nullptr>
		T	*instantiate(std::string prefabPath)
		{
			// std::cout << "scene instantiating " << prefabPath << "\n";
			T *object = instantiate<T>();
			object->load(prefabPath);
			return (object);
		}

        template<typename T, typename std::enable_if<std::is_base_of<Graphics::ALight, T>::value>::type* = nullptr>
		T	*instantiateLight(void)
		{
			std::cout << "Light added : " << uniqueID << std::endl;
			T *c = new T(uniqueID, *this);
			_lights.insert(std::pair<int, Graphics::ALight *>(uniqueID, static_cast<Graphics::ALight *>(c)));
            // _toStart.push_back(c);
            // _toStartUI.push_back(c);
            uniqueID++;
			return (c);
		}

		void setSkybox(Graphics::Cubemap *cubemap);

        void debugTest(void);
		GameObject *find(std::string name);
		/*!
		*  \brief list d'objet
		*  Methode permettant de retourner la liste des objet
        *  \return list des objets
		*/
        std::vector<GameObject *> getGameObjects();
        std::vector<Graphics::ALight *> getLights();
        
        void save(std::string filePath);
        void load(std::string filePath);

        virtual nlohmann::json	serialize();
        virtual void deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader);
    };
}

#endif