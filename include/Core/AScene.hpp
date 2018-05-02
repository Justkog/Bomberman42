#ifndef BE_CORE_ASCENE_HPP
#define BE_CORE_ASCENE_HPP 1

#include "Core.hpp"
#include "Core/Json/JsonSerializable.hpp"

namespace BeerEngine
{
    class AScene : public JsonSerializable, public JsonDeserializable
    {
    private:
        static int                  uniqueID;
        std::map<int, GameObject *> _gameObjects;
        std::vector<GameObject *>   _toDestroy;
        std::vector<GameObject *>   _toStart;
        std::mutex                  updateMutex;

        
    public:
        std::string                 filePath;

        AScene(void);
        virtual ~AScene(void);

        virtual void    init(void) = 0;

        void    mutexLock(bool lock);

        void    start(void);
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
            uniqueID++;
			return (c);
		}

        void debugTest(void);

        std::vector<GameObject *> getGameObjects();
        
        // void load(std::string filePath)
        // {
        //     std::string content = BeerEngine::IO::FileUtils::LoadFile(filePath);
        //     auto j = nlohmann::json::parse(content);
        //     // Game::SettingsContainer c;
        //     // this->settingsContainer = j;
        // }

        void save(std::string filePath);
        void load(std::string filePath);

        virtual nlohmann::json	serialize();
        virtual void deserialize(const nlohmann::json & j);

    };
}

#endif