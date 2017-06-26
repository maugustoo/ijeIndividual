#ifndef __GAME_PLAYER_OBJECT__
#define __GAME_PLAYER_OBJECT__

#include <string>
#include <list>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include "vector.hpp"
#include "gameobject.hpp"
#include "components/image.hpp"
#include "spell.hpp"
#include "components/text.hpp"

using namespace engine;

class Player : public GameObject {
public:
    Player() : GameObject() {}
    Player(std::string _name,int _x,int _y)
        : GameObject(_name,_x,_y) {}

    ~Player() {}
    int life = 100;
    int lastMove = 1;
    virtual bool init();
    virtual bool shutdown();
    virtual bool update();
    virtual bool draw();

    bool moveDown();
    bool moveUp();
    bool moveRight();
    bool moveLeft();
    bool atack();
    bool addSpell(std::string name, Spell * spell);
    bool useSpell();

private:
    std::unordered_map<std::string, Spell*> spells;
    int defaultVel = 5;
};

#endif
