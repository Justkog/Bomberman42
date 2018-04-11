#ifndef BE_CORE_ASCENE_HPP
#define BE_CORE_ASCENE_HPP 1

#include <map>
#include "Core.hpp"
#include "GameObject.hpp"

namespace BeerEngine
{
    class AScene
    {
    private:
        std::map<int, GameObject *> _gameObjects;
    
    public:
        AScene(void);
        ~AScene(void);

        void    fixedUpdate(void);
        void    update(void);
        void    renderUpdate(void);
        void    render(void);


        template<typename T, typename std::enable_if<std::is_base_of<GameObject, T>::value>::type* = nullptr>
		T	*instantiate(void)
		{
            int     uniqueID = 0; // TODO : GENERER UN ID
			T *c = new T(uniqueID);
			_gameObjects.insert(std::pair<int, GameObject *>(uniqueID, c));
			return (c);
		}
    };
}

#endif