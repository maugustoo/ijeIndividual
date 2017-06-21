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


#define nframes 4

using namespace engine;

int lastMove = 1;

bool Player::init()
{
    engine::GameObject::init();

    //active_instrument = instruments[globals::andar];
    active_sprite = sprites[globals::andar];

    //sprites[globals::eletric_guitar]->setState(Component::State::disabled);
    //sprites[globals::accordion]->setState(Component::State::disabled);

    //INFO("x"<<physics.collisionBox.x<<"  y"<<physics.collisionBox.y <<"  w"<<physics.collisionBox.w<< "    h"<< physics.collisionBox.h)
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
    handlePlayer();

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

bool Player::changeSprite(std::string sprite_name){
    INFO("Changing Sprite to " << sprite_name);
    ImageComponent* sprite = sprites[sprite_name];
   
    active_sprite->setState(Component::State::disabled);
    sprite->setState(Component::State::enabled);
    active_sprite = sprite;

    return true;
}

bool Player::handlePlayer(){
    
    if(Input::keyPressed(Input::ONE))
    {
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

void Player::addSprite(std::string sprite_name, ImageComponent * sprite){
    sprites[sprite_name] = sprite;
}

void Player::addFragment(int _id){
    fragments.push_back(_id);
    if(fragments.size() == 4) {
        engine::Game::instance.change_scene("Victory");
        physics.position.setX(getInitialX());
        physics.position.setY(getInitialY());
        life = 100;

    }

    std::stringstream ss;
    ss << "Numero de fragmentos: " << fragments.size();
    

    nFragments->setText(ss.str());
    nFragments->init();
}
