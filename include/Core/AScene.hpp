#ifndef BE_CORE_ASCENE_HPP
#define BE_CORE_ASCENE_HPP 1

#include <map>
#include <mutex>
#include "Core.hpp"
#include "GameObject.hpp"
#include "Component/Component.hpp"
#include "Component/MeshRenderer.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/MeshBuilder.hpp"
#include "Graphics/ShaderProgram.hpp"
#include "Graphics/Graphics.hpp"
#include "Graphics/AMaterial.hpp"

namespace BeerEngine
{
    class AScene
    {
    private:
        static int     uniqueID;
        std::map<int, GameObject *> _gameObjects;
        std::mutex                  updateMutex;
        
    public:
        AScene(void);
        virtual ~AScene(void);

        virtual void    init(void) = 0;

        void    mutexLock(bool lock);

        void    fixedUpdate(void);
        void    update(void);
        void    renderUpdate(void);
        void    render(void);

        template<typename T, typename std::enable_if<std::is_base_of<GameObject, T>::value>::type* = nullptr>
		T	*instantiate(void)
		{
            // while (_gameObjects.find(uniqueID = std::rand()) != _gameObjects.end());
             std::cout << "GameObject added : " << uniqueID << std::endl;
			T *c = new T(uniqueID++);
			_gameObjects.insert(std::pair<int, GameObject *>(uniqueID, c));
            c->start();
			return (c);
		}

        void debugTest(void)
        {
            std::cout << "GameObject List Size : " << _gameObjects.size() << std::endl;
        }
    };
}

#endif