#ifndef BE_CORE_ASCENE_HPP
#define BE_CORE_ASCENE_HPP 1

#include "Core.hpp"
#include "Core/Json/JsonSerializable.hpp"

struct nk_font;

namespace BeerEngine
{
    class AScene : public JsonSerializable, public JsonDeserializable
    {
    private:
        static int                          uniqueID;
        std::map<int, GameObject *>         _gameObjects;
        std::map<int, Graphics::ALight *>   _lights;
        std::vector<GameObject *>           _toDestroy;
        std::vector<GameObject *>           _toStart;
        std::vector<GameObject *>           _toStartUI;
        std::mutex                          updateMutex;

        
    public:
        std::string                 filePath;

        AScene(void);
        virtual ~AScene(void);

        virtual void    init(void) = 0;

        void    mutexLock(bool lock);

        void    start(void);
        void    startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
        void    fixedUpdate(void);
        void    update(void);
        void    renderUpdate(void);
        void    render(void);
        void    renderUI(struct nk_context *ctx);
        void    physicUpdate(void);

        void    destroy(GameObject *go);
        void    destroyGameObjects(void);

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

        void debugTest(void);

        std::vector<GameObject *> getGameObjects();
        std::vector<Graphics::ALight *> getLights();
        
        void save(std::string filePath);
        void load(std::string filePath);

        virtual nlohmann::json	serialize();
        virtual void deserialize(const nlohmann::json & j);

    };
}

#endif