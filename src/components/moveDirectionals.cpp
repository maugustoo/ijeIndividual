#include "log.h"
#include "components/moveDirectionals.hpp"
#include "gameobject.hpp"
#include "components/animationcontroller.hpp"
#include "keyword.hpp"
#include "vector.hpp"
#include "game.hpp"
#include "tilemap.hpp"

using namespace engine;

int keyActive = 2;

bool MoveDirectionals::update(){

    keyActive = keyActive;

	bool keyFlag = false;

    if(Input::keyPressed(Input::UP))
    {
        keyActive = 1;
        auto map = Game::instance.m_scene->get_game_object("mapa");
        if((dynamic_cast<TileMap *>(map))->at(((m_game_object->physics.position.getX()+20)/32),((m_game_object->physics.position.getY()+32)/32),2)==1)
           keyFlag = false;     
        else{
            keyFlag = true;
        }
        (dynamic_cast<Player *>(m_game_object))->moveUp();
    }
    if(Input::keyPressed(Input::DOWN))
    {
        keyActive = 2;
        auto map = Game::instance.m_scene->get_game_object("mapa");
        if((dynamic_cast<TileMap *>(map))->at(((m_game_object->physics.position.getX()+20)/32),((m_game_object->physics.position.getY()+42)/32),2)==1)
           keyFlag = false;     
        else{
            keyFlag = true;
        }
        (dynamic_cast<Player *>(m_game_object))->moveDown();
    }
    if(Input::keyPressed(Input::RIGHT))
    {
        keyActive = 3;
        auto map = Game::instance.m_scene->get_game_object("mapa");
        if((dynamic_cast<TileMap *>(map))->at(((m_game_object->physics.position.getX()+20)/32),((m_game_object->physics.position.getY()+42)/32),2)==1)
           keyFlag = false;     
        else{
            keyFlag = true;
        }
        (dynamic_cast<Player *>(m_game_object))->moveRight();
    }
    if(Input::keyPressed(Input::LEFT))
    {
        keyActive = 4;
        auto map = Game::instance.m_scene->get_game_object("mapa");
        if((dynamic_cast<TileMap *>(map))->at(((m_game_object->physics.position.getX())/32),((m_game_object->physics.position.getY()+42)/32),2)==1)
           keyFlag = false;     
        else{
            keyFlag = true;
        }
        (dynamic_cast<Player *>(m_game_object))->moveLeft();
    }

    if(Input::keyPressed(Input::ONE))
    {
        Vector2D nulo(0,0);
        m_game_object->physics.velocity = nulo;
        keyFlag = true;
    }

    if(!keyFlag){
        Vector2D nulo(0,0);
        m_game_object->physics.velocity = nulo;
        if(keyActive == 1) {
            auto animCtrl = m_game_object->get_component<AnimationControllerComponent>();
            animCtrl->changeAnimation("moveUpPause");
        }
        if(keyActive == 2) {
            auto animCtrl = m_game_object->get_component<AnimationControllerComponent>();
            animCtrl->changeAnimation("moveDownPause");
        }
        if(keyActive == 3) {
            auto animCtrl = m_game_object->get_component<AnimationControllerComponent>();
            animCtrl->changeAnimation("moveRightPause");
        }
        if(keyActive == 4) {
            auto animCtrl = m_game_object->get_component<AnimationControllerComponent>();
            animCtrl->changeAnimation("moveLeftPause");
        }
    }
	return true;
}