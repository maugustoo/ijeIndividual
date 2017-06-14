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

    // Setup scenes
    MenuScene menu("Menu");
    MenuScene GameoverScene("Gameover");
    MenuScene VictoryScene("Victory");
    GameScene room1("stage_1_room_1");
    GameScene room2("stage_1_room_2");
    
    
    /* Gamescene*/
    Game::instance.add_scene(menu);
    Game::instance.add_scene(room1);
    Game::instance.add_scene(GameoverScene);
    Game::instance.add_scene(VictoryScene);

    Player player(globals::player,100,100);
    player.xF = 0; player.yF = 0;

    MoveDirectionals move(player);

    //Declaring instruments
    Instrument espada(globals::espada, 100, 100);
    Instrument arco(globals::arco, 100, 100);
    Instrument andar(globals::andar, 100, 100);

    //AudioComponent somQ(spellQBanjo, "pika.wav", false, false);
    
    player.addInstrument(globals::espada, espada);
    player.addInstrument(globals::arco, arco);
    player.addInstrument(globals::andar, andar);

    //ImageComponent espadaImage(player, "girl2.png", 4, 4);
    //ImageComponent arcoImage(player, "girl3.png", 4, 4);

    ImageComponent linkWalkImage(player, "spritesLink.png", 8, 8);
    /*
    ImageComponent linkWalkDown(player, "linkWalkDown.png", 1, 8);
    ImageComponent linkWalkUp(player, "linkWalkUp.png", 1, 8);
    ImageComponent linkWalkRight(player, "linkWalkRight.png", 1, 8);
    ImageComponent linkWalkLeft(player, "linkWalkLeft.png", 1, 8);*/

    /*HUDInstrument HUDInstrument("hudinstrument", globals::window_size.first-250, globals::window_size.second-120, &player);
    HUDInstrument.xF = 0; HUDInstrument.yF = 0;
    ImageComponent banjoActiveHUD(HUDInstrument, "hud_instruments_0.png", 1, 1);
    ImageComponent eletricGuitarActiveHUD(HUDInstrument, "hud_instruments_1.png", 1, 1);
    ImageComponent accordionActiveHUD(HUDInstrument, "hud_instruments_2.png", 1, 1);

    HUDInstrument.addHUD(globals::banjo, &banjoActiveHUD);
    HUDInstrument.addHUD(globals::eletric_guitar, &eletricGuitarActiveHUD);
    HUDInstrument.addHUD(globals::accordion, &accordionActiveHUD);

    HUDInstrument.add_component(banjoActiveHUD);
    HUDInstrument.add_component(eletricGuitarActiveHUD);
    HUDInstrument.add_component(accordionActiveHUD);*/

    //player.addSprite(globals::espada, &espadaImage);
    //player.addSprite(globals::arco, &arcoImage);
    player.addSprite(globals::andar, &linkWalkImage);

    player.add_component(linkWalkImage);
    //player.add_component(eletricGuitarImage);
    //player.add_component(accordionImage);

    player.add_component(move);

    GameObject nFragments("nFragments",10,40);
    TextComponent fragmentText(nFragments,"Numero de fragmentos: ","font.ttf",20);
    nFragments.add_component(fragmentText);
    player.nFragments = &fragmentText;
    
    //ghost1

    Enemy ghost("ghost", 800, 200);
    ghost.xF = 0; ghost.yF = 0;
    AnimationComponent ghostI(ghost, "ghost.png", 4, 4, 500, 0, 3 ,-1);
    FollowPlayer moveGhost(ghost);
    AnimationControllerComponent ghostController(ghost);
    ghostController.addAnimation("moveDown", ghostI);
    DamageEnemy damage(ghost);
    ghost.add_component(damage);
    ghost.add_component(ghostController);
    ghost.add_component(moveGhost);

    //change room handler
    GameObject goRightRoom1("goRightRoom1", 925,200);
    goRightRoom1.xF = 0; goRightRoom1.yF = 0;
    ChangeRoom goRightRoom1Component(goRightRoom1,room2.name(),ChangeRoom::Direction::Right);
    goRightRoom1.add_component(goRightRoom1Component); 
    goRightRoom1.w = 100; goRightRoom1.h = 100;
    

    //add to scene
    room1.add_game_object(andar);
    room1.add_game_object(player);
    room1.add_game_object(ghost);
    room1.add_game_object(goRightRoom1);


    room1.add_game_object(nFragments);
    

    //Fragmento sala 1

    GameObject fragmento("fragmento",16*32,12*32);
    fragmento.xF = 0; fragmento.yF = 0;
    FragmentComponent obtainFrag(fragmento,1);
    ImageComponent guitarFrag(fragmento, "guitar.png", 1, 3);
    fragmento.add_component(obtainFrag);
    fragmento.add_component(guitarFrag);
    room1.add_game_object(fragmento);


    GameObject playbutton("playbutton",(globals::window_size.first/2)-50,(globals::window_size.second/2)-50);
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

    TileMap tilemap("assets/mapa1.txt", "mapa", 0, 0);
    TileSet tileset(32, 32, tilemap, "tilesheet.png", 1, 1);
    tilemap.setTileSet(tileset);
    tilemap.add_component(tileset);
  


    HUDLife hudlife("hudlife", 0, 0, &player);
    hudlife.xF = 0; hudlife.yF = 0;
    ImageComponent lifeBar(hudlife, "hud_life.png", 1, 1);
    CustomImageComponent lifeBarContent(hudlife, "hud_life_full.png", 1, 1);
    hudlife.setLifeBar(&lifeBar);
    hudlife.setLifeBarContent(&lifeBarContent);
    hudlife.add_component(lifeBar);
    hudlife.add_component(lifeBarContent); 

    AudioComponent music(tilemap,"fase.mp3",true, true);
    tilemap.add_component(music);

    room1.add_game_object(tilemap);
    room1.add_game_object(hudlife);
    //room1.add_game_object(HUDInstrument);


    // Game loop
    Game::instance.run();
    return 0;
}
