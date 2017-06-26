#include "gameobject.hpp"
#include "components/image.hpp"
#include "log.h"
#include "vector.hpp"
#include "enemy.hpp"
#include "game.hpp"
#include "player.hpp"
#include "gameglobals.hpp"
#include <cmath>
#include "object.hpp"

using namespace engine;

bool Object::init()
{
    engine::GameObject::init(); 
    return true;
}

bool Object::shutdown()
{
    engine::GameObject::shutdown();
    return true;
}

bool Object::draw()
{
    engine::GameObject::draw();
    return true;
}

bool Object::update()
{
    engine::GameObject::update();

    physics.collisionBox.x = physics.position.getX();
    physics.collisionBox.y = physics.position.getY();
    physics.collisionBox.w = w;
    physics.collisionBox.h = h;

    if(life <= 0) {
        m_state = State::disabled;
    }

    if(life >= 0) {
        physics.detectColision(m_target);
    }

    if(physics.detectColision(m_target) && life > 0)
    {   
        int m_target_moveX = 0, m_target_moveY = 0;
        if(m_target->lastMove == 1) {
            m_target_moveX = 0;
            m_target_moveY = -1;
        }
        if(m_target->lastMove == 2) {
            m_target_moveX = 0;
            m_target_moveY = 1;
        }
        if(m_target->lastMove == 3) {
            m_target_moveX = 1;
            m_target_moveY = 0;
        }
        if(m_target->lastMove == 4) {
            m_target_moveX = -1;
            m_target_moveY = 0;
        }
        Vector2D velocityStop(m_target_moveX, m_target_moveY);
        m_target->physics.velocity = velocityStop * 5;
    }

    return true;
}