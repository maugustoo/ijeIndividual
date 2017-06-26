#include "gamescene.hpp"
#include "scene.hpp"
#include "log.h"
#include <string>
#include "keyword.hpp"
#include "player.hpp"
#include "game.hpp"
#include "enemy.hpp"

using namespace engine;

bool GameScene::init(){
    Scene::init();
    return true;
}

bool GameScene::update()
{    
    Scene::update();
    bool isWinner = true;
    for (auto id_obj: m_objects)
    {
        auto obj = id_obj.second;
        if ((dynamic_cast<Enemy*>(obj))){
        	if(dynamic_cast<Enemy*>(obj)->life > 0){
        		isWinner = false;
        	}
        }
    }

    if(isWinner){
    	engine::Game::instance.change_scene("Victory");
    }

    return true;
}

bool GameScene::draw()
{
    Scene::draw();

    return true;
}