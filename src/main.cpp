#include "game.hpp"
#include "gameobject.hpp"
#include "scene.hpp"
#include "components/image.hpp"
#include "components/text.hpp"
#include "components/audio.hpp"
#include "components/animation.hpp"
#include "components/moveDirectionals.hpp"
#include "components/animationcontroller.hpp"
#include "components/pushenemy.hpp"
#include "customimagecomponent.hpp"
#include "object.hpp"
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
#include "enemy.hpp"

using namespace std;
using namespace engine;

int main(int, char**)
{
    // Configure game
    Game::instance.set_properties(globals::game_name, globals::window_size);

    MenuScene menu("Menu");
    GameScene room1("stage_1_room_1");
    MenuScene GameoverScene("Gameover");
    MenuScene VictoryScene("Victory");

    
    /* Gamescene*/
    Game::instance.add_scene(menu);
    Game::instance.add_scene(room1);
    Game::instance.add_scene(GameoverScene);
    Game::instance.add_scene(VictoryScene);

    Player player(globals::player, 100, 100);
    player.xF = 0; player.yF = 0;

    MoveDirectionals move(player);

    AnimationComponent walkLeft(player, "spritesLink3.png", 8, 4, 1000, 0, 7);
    AnimationComponent walkRight(player, "spritesLink3.png", 8, 4, 1000, 8, 15);
    AnimationComponent walkUp(player, "spritesLink3.png", 8, 4, 1000, 16, 23);
    AnimationComponent walkDown(player, "spritesLink3.png", 8, 4, 1000, 24, 31);

    AnimationComponent walkLeftPause(player, "spritesLink3.png", 8, 4, 1000, 0, 1);
    AnimationComponent walkRightPause(player, "spritesLink3.png", 8, 4, 1000, 8, 9);
    AnimationComponent walkUpPause(player, "spritesLink3.png", 8, 4, 1000, 16, 17);
    AnimationComponent walkDownPause(player, "spritesLink3.png", 8, 4, 1000, 24, 25);

    AnimationComponent linkAtackLeft(player, "atackLeft.png", 4, 1, 500, 0, 4);
    AnimationComponent linkAtackDown(player, "atackDown.png", 4, 1, 500, 0, 4);
    AnimationComponent linkAtackUp(player, "atackUp.png", 4, 1, 500, 0, 4);
    AnimationComponent linkAtackRight(player, "atackRight.png", 4, 1, 500, 0, 4);

    AnimationControllerComponent linkController(player);

    linkController.addAnimation("moveUp", walkUp);
    linkController.addAnimation("moveDown", walkDown);
    linkController.addAnimation("moveLeft", walkLeft);
    linkController.addAnimation("moveRight", walkRight);

    linkController.addAnimation("moveUpPause", walkUpPause);
    linkController.addAnimation("moveDownPause", walkDownPause);
    linkController.addAnimation("moveLeftPause", walkLeftPause);
    linkController.addAnimation("moveRightPause", walkRightPause);

    linkController.addAnimation("atackLeft", linkAtackLeft);
    linkController.addAnimation("atackDown", linkAtackDown);
    linkController.addAnimation("atackRight", linkAtackRight);
    linkController.addAnimation("atackUp", linkAtackUp);

    Spell atack("atack", &player, 500, 500, 500, 500);
    AudioComponent somAtack(atack, "pika.wav", false, false);

    PushEnemy pushAtack(atack);
    atack.xF = 0; atack.yF = 0;

    atack.add_component(pushAtack);
    
    player.addSpell("atack", &atack);

    player.add_component(linkController);
    player.add_component(move);

    HUDLife hudlife("hudlife", 0, 0, &player);
    hudlife.xF = 0; hudlife.yF = 0;
    ImageComponent lifeBar(hudlife, "hud_life.png", 1, 1);
    CustomImageComponent lifeBarContent(hudlife, "hud_life_full.png", 1, 1);
    hudlife.setLifeBar(&lifeBar);
    hudlife.setLifeBarContent(&lifeBarContent);
    hudlife.add_component(lifeBar);
    hudlife.add_component(lifeBarContent); 


    Object objeto("objeto", 600, 250, &player, 500);
    objeto.xF = 0; objeto.yF = 0;
    AnimationComponent objeto1(objeto, "girl.png", 4, 4, 500, 0, 3 ,-1);
    AnimationControllerComponent objetoController(objeto);
    objetoController.addAnimation("moveDown", objeto1);
    objeto.add_component(objetoController);


    Enemy enemy("enemy", 600, 250, &player, 100);
    enemy.xF = 0; enemy.yF = 0;
    AnimationComponent enemy1(enemy, "ghost.png", 4, 4, 500, 0, 3 ,-1);
    AnimationControllerComponent enemy1Controller(enemy);
    enemy1Controller.addAnimation("moveDown", enemy1);
    enemy.add_component(enemy1Controller);

    Enemy enemy2("enemy2", 300, 250, &player, 100);
    enemy2.xF = 0; enemy2.yF = 0;
    AnimationComponent enemy21(enemy2, "ghost.png", 4, 4, 500, 0, 3 ,-1);
    AnimationControllerComponent enemy21Controller(enemy2);
    enemy21Controller.addAnimation("moveDown", enemy21);
    enemy2.add_component(enemy21Controller);

    Enemy enemy3("enemy3", 600, 500, &player, 100);
    enemy3.xF = 0; enemy3.yF = 0;
    AnimationComponent enemy31(enemy3, "ghost.png", 4, 4, 500, 0, 3 ,-1);
    AnimationControllerComponent enemy31Controller(enemy3);
    enemy31Controller.addAnimation("moveDown", enemy31);
    enemy3.add_component(enemy31Controller);

    TileMap tilemap("assets/mapa1.txt", "mapa", 0, 0);
    TileSet tileset(32, 32, tilemap, "tilesheet.png", 1, 1);
    tilemap.setTileSet(tileset);
    tilemap.add_component(tileset);

    AudioComponent music(tilemap,"fase.mp3",true, true);
    tilemap.add_component(music);

    //add to scene
    room1.add_game_object(player);
    room1.add_game_object(tilemap);
    room1.add_game_object(enemy);
    room1.add_game_object(enemy2);
    room1.add_game_object(enemy3);
    room1.add_game_object(hudlife);
    room1.add_game_object(atack);
    room1.add_game_object(objeto);

    GameObject playbutton("playbutton",(globals::window_size.first/2)-512,(globals::window_size.second/2)-500);
    ImageComponent playImage(playbutton,"playbutton.png",1,1);
    playbutton.xF = 0; playbutton.yF = 0;
    playbutton.add_component(playImage);
    menu.add_game_object(playbutton);

    GameObject gameover("gameover",(globals::window_size.first/2)-100,(globals::window_size.second/2)-100);
    ImageComponent gameoverImage(gameover,"gameover.png",1,1);
    gameover.xF = 0; gameover.yF = 0;
    gameover.add_component(gameoverImage);
    GameoverScene.add_game_object(gameover);

    GameObject victory("victory",(globals::window_size.first/2)-100,(globals::window_size.second/2)-100);
    ImageComponent victoryImage(victory,"victory.png",1,1);
    victory.xF = 0; victory.yF = 0;
    victory.add_component(victoryImage);
    VictoryScene.add_game_object(victory);


    // Game loop
    Game::instance.run();
    return 0;
}
