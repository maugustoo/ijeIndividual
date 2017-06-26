#include "gameobject.hpp"
#include "components/image.hpp"
#include "components/audio.hpp"
#include "log.h"
#include "vector.hpp"
#include "spell.hpp"
#include "timer.hpp"
#include "game.hpp"

#define nframes 10

using namespace engine;

bool Spell::init()
{
    engine::GameObject::init();
    setState(State::disabled);

    return true;
}

bool Spell::shutdown()
{
    engine::GameObject::shutdown();
    return true;
}

bool Spell::draw()
{
    engine::GameObject::draw();

    return true;
}

bool Spell::update()
{
  GameObject::update();

  if(durationTimer.getTime()< duration){
    
    
  }else{
    //quita do scene
    INFO("Finish spell");
    setState(State::disabled);

    //Game::instance.m_scene->remove_game_object(name());
   }

  return true;
}

bool Spell::useSpell()
{
  if(countdownTimer.getTime() > countdown){
      INFO("Start atack");
      setState(State::enabled);

      physics.position = player->physics.position;
      Vector2D velocityAtack(1,1); 
      physics.velocity += player->physics.velocity;

      durationTimer.startTimer();
      countdownTimer.startTimer();
      setup();
  }else{
    INFO("on countdown");
  }
  return true;
}

void Spell::setup()
{
  xF = 0;
  yF = 0;
  GameObject::setup();
}
