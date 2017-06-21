#ifndef __COMPONENTS_MOVE__
#define __COMPONENTS_MOVE__

#include "sdl2include.h"
#include "components/code.hpp"
#include "player.hpp"
#include "gameobject.hpp"
#include "components/animationcontroller.hpp"


using namespace engine;

class MoveDirectionals : public CodeComponent {
public:
    MoveDirectionals(Player & game_object)
        : CodeComponent(game_object) {}
        
    MoveDirectionals() : CodeComponent() {}

    ~MoveDirectionals() {}

    bool update();

};

#endif