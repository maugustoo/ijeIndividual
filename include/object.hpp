#ifndef __GAME_OBJECT_OBJECT__
#define __GAME_OBJECT_OBJECT__

#include <string>
#include <list>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include "vector.hpp"
#include "gameobject.hpp"
#include "components/image.hpp"
#include "player.hpp"
#include "components/text.hpp"

using namespace engine;

class Object : public GameObject {
public:
    Object() : GameObject() {}
    Object(std::string _name,int _x,int _y, Player * target, int object_life)
        : GameObject(_name,_x,_y), m_target(target), life(object_life) {}

    ~Object() {}

    int life = 100;

    virtual bool init();
    virtual bool shutdown();
    virtual bool update();
    virtual bool draw();
    
    private:
    Player* m_target;
};

#endif