#include "scene.hpp"
#include "menuscene.hpp"
#include "game.hpp"
#include "keyword.hpp"


using namespace engine;

bool MenuScene::update()
{
    if(Input::keyPressed(Input::ENTER))
    {
       engine::Game::instance.change_scene("stage_1_room_1");
    }
    
    return true;
}
