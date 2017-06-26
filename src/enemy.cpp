#include "gameobject.hpp"
#include "components/image.hpp"
#include "log.h"
#include "vector.hpp"
#include "enemy.hpp"
#include "game.hpp"
#include "player.hpp"
#include "gameglobals.hpp"
#include <cmath>

using namespace engine;

bool Enemy::init()
{
    engine::GameObject::init(); 
    return true;
}

bool Enemy::shutdown()
{
    engine::GameObject::shutdown();
    return true;
}

bool Enemy::draw()
{
    engine::GameObject::draw();
    return true;
}

bool Enemy::update()
{
    engine::GameObject::update();
    Vector2D pos = m_target->physics.position;
    int distance = hypot(pos.getX() - physics.position.getX(), 
                         pos.getY() - physics.position.getY());
    if(distance <= 250 && life > 0){
        physics.velocity += pos - physics.position;
        physics.velocity.normalize();
        physics.velocity *=2;
    }

    if(distance > 250 && life > 0){
        Vector2D velocity(0,0);
        physics.velocity = velocity;
    }

    if(life <= 0) {
        m_state = State::disabled;
    }

    causeDamage();
    return true;
}

void Enemy::causeDamage(){

    physics.collisionBox.x = physics.position.getX();
    physics.collisionBox.y = physics.position.getY();
    physics.collisionBox.w = w;
    physics.collisionBox.h = h;
    
    if(physics.detectColision(m_target) && life > 0)
    {
        m_target->life -= 5;
        m_target->physics.velocity = (physics.velocity * 5); 
    }

    if(m_target->life <= 0)
    {
        engine::Game::instance.change_scene("Gameover");
        physics.position.setX(getInitialX());
        physics.position.setY(getInitialY());
        m_target->physics.position.setX(m_target->getInitialX());
        m_target->physics.position.setY(m_target->getInitialY());
        m_target->life = 100;
        life = 100;
    }
}