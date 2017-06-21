#include "log.h"
#include "components/moveDirectionals.hpp"
#include "gameobject.hpp"
#include "components/animationcontroller.hpp"
#include "keyword.hpp"
#include "vector.hpp"
#include "game.hpp"
#include "tilemap.hpp"

bool MoveDirectionals::update(){

    int keyActive = -1;

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

    if(!keyFlag){
        Vector2D nulo(0,0);
        m_game_object->physics.velocity = nulo;
        switch(keyActive){
            case 1:
                auto animCtrl = get_component<AnimationControllerComponent>();
                animCtrl->changeAnimation("moveUpPause");
            break;
            case 2:
                auto animCtrl = get_component<AnimationControllerComponent>();
                animCtrl->changeAnimation("moveDownPause");
            break;
            case 3:
                auto animCtrl = get_component<AnimationControllerComponent>();
                animCtrl->changeAnimation("moveLeftPause");
            break;
            case 4:
                auto animCtrl = get_component<AnimationControllerComponent>();
                animCtrl->changeAnimation("moveRighPause");
        }
        keyActive = -1;
    }
	return true;
}