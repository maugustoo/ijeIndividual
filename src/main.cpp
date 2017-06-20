#include "game.hpp"
#include "gameobject.hpp"
#include "scene.hpp"
#include "components/image.hpp"
#include "components/text.hpp"
#include "components/audio.hpp"
#include "components/animation.hpp"
#include "components/moveDirectionals.hpp"
#include "components/moveSS.hpp"
#include "components/damageEnemy.hpp"
#include "components/follow.hpp"
#include "components/animationcontroller.hpp"
#include "components/changeroom.hpp"
#include "components/fragment.hpp"
#include "components/pushenemy.hpp"
#include "customimagecomponent.hpp"
#include "player.hpp"
#include "gamescene.hpp"
#include "menuscene.hpp"
#include "gameover.hpp"
#include "spell.hpp"
#include "tilemap.hpp"
#include "tileset.hpp"
#include "log.h"
#include "gameglobals.hpp"
#include "hudlife.hpp"
#include "hudinstrument.hpp"
#include "enemy.hpp"

using namespace std;
using namespace engine;

int main(int, char**)
{
    // Configure game
    Game::instance.set_properties(globals::game_name, globals::window_size);

    GameScene room1("stage_1_room_1");    
    
    /* Gamescene*/
    Game::instance.add_scene(room1);

    Player player(globals::player, 100, 100);
    player.xF = 0; player.yF = 0;

    MoveDirectionals move(player);

    //Declaring instruments
    //Instrument espada(globals::espada, 100, 100);
    //Instrument arco(globals::arco, 100, 100);
    //Instrument andar(globals::andar, 100, 100);
    
    //player.addInstrument(globals::espada, espada);
    //player.addInstrument(globals::arco, arco);
    //player.addInstrument(globals::andar, andar);

   //ImageComponent linkWalkImage(player, "spritesLink3.png", 8, 4);

    AnimationComponent linkAtackLeft(player, "atackLeft.png", 6, 1, 1000, 0, 5);

    AnimationComponent walkLeft(player, "spritesLink3.png", 8, 4, 1000, 0, 7);
    AnimationComponent walkRight(player, "spritesLink3.png", 8, 4, 1000, 8, 15);
    AnimationComponent walkUp(player, "spritesLink3.png", 8, 4, 1000, 16, 23);
    AnimationComponent walkDown(player, "spritesLink3.png", 8, 4, 1000, 24, 31);


    AnimationControllerComponent linkController(player);
    //linkController.addAnimation("atackLeft", linkAtackLeft);

    linkController.addAnimation("moveUp", walkUp);
    linkController.addAnimation("moveDown", walkDown);
    linkController.addAnimation("moveLeft", walkLeft);
    linkController.addAnimation("moveRight", walkRight);


    //player.addSprite(globals::andar, &linkWalkImage);
    //player.addSprite("atackLeft", &linkAtackLeft);

    //player.add_component(linkWalkImage);
    player.add_component(linkController);
    player.add_component(move);
    

    //add to scene
    room1.add_game_object(player);

    TileMap tilemap("assets/mapa1.txt", "mapa", 0, 0);
    TileSet tileset(32, 32, tilemap, "tilesheet.png", 1, 1);
    tilemap.setTileSet(tileset);
    tilemap.add_component(tileset); 
  

    AudioComponent music(tilemap,"fase.mp3",true, true);
    tilemap.add_component(music);

    room1.add_game_object(tilemap);


    // Game loop
    Game::instance.run();
    return 0;
}
