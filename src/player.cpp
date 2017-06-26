#include "gameobject.hpp"
#include "player.hpp"
#include "components/text.hpp"
#include "components/image.hpp"
#include "log.h"
#include "vector.hpp"
#include "keyword.hpp"
#include "gameglobals.hpp"
#include "components/animationcontroller.hpp"
#include <sstream>
#include "game.hpp"

using namespace engine;

bool Player::init()
{
    engine::GameObject::init();

    return true;
}

bool Player::shutdown()
{
    engine::GameObject::shutdown();
    return true;
}

bool Player::draw()
{
    engine::GameObject::draw();
    return true;
}

bool Player::update()
{
    atack();

    GameObject::update();
    
    int collisionAdjust = 0;
    physics.collisionBox.x = physics.position.getX() + collisionAdjust;
    physics.collisionBox.y = physics.position.getY() + collisionAdjust;
    physics.collisionBox.w = w - collisionAdjust;
    physics.collisionBox.h = h - collisionAdjust;

    return true;
}
bool Player::moveDown(){
    lastMove = 1;

    // Update Velocity
    int componentX = 0;
    int componentY = defaultVel;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
    // Update Frame
    auto animCtrl = get_component<AnimationControllerComponent>();
    animCtrl->changeAnimation("moveDown");
    return true;
}

bool Player::moveUp(){
    lastMove = 2;

    // Update Velocity
    int componentX = 0;
    int componentY = -1*defaultVel;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
    // Update Frame
    auto animCtrl = get_component<AnimationControllerComponent>();
    animCtrl->changeAnimation("moveUp");
    return true;
}

bool Player::moveLeft(){
    lastMove = 3;

    // Update Velocity
    int componentX = -1*defaultVel;

    int componentY = 0;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
    // Update Frame
    auto animCtrl = get_component<AnimationControllerComponent>();
    animCtrl->changeAnimation("moveLeft");
    return true;
}

bool Player::moveRight(){
    lastMove = 4;

    // Update Velocity
    int componentX = defaultVel;
    int componentY = 0;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
    // Update Frame
    auto animCtrl = get_component<AnimationControllerComponent>();
    animCtrl->changeAnimation("moveRight");
    return true;
}

bool Player::atack() {
    
    if(Input::keyPressed(Input::ONE)) {
        useSpell();
        if(lastMove == 3) {
            auto animCtrl = get_component<AnimationControllerComponent>();
            animCtrl->changeAnimation("atackLeft");
        }
        if(lastMove == 2) {
            auto animCtrl = get_component<AnimationControllerComponent>();
            animCtrl->changeAnimation("atackUp");    
        }
        if(lastMove == 1){
            auto animCtrl = get_component<AnimationControllerComponent>();
            animCtrl->changeAnimation("atackDown");
        }
        if(lastMove == 4) {
            auto animCtrl = get_component<AnimationControllerComponent>();
            animCtrl->changeAnimation("atackRight");
        }
    }
    return true;
}


bool Player::addSpell(std::string spell_name, Spell * spell) {
    INFO("Spell adicionada " << spell_name);
    spells[spell_name] = spell;
    return true;
}

bool Player::useSpell() {
    spells["atack"]->useSpell();
    INFO("Using atack from " << name());
    return true;
}