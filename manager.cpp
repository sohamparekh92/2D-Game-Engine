#include <iostream>
#include <string>
#include <iomanip>
#include "vector2f.h"
#include "multisprite.h"
#include "twoWayMultisprite.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"
#include "extractSurface.h"
#include "fire.h"
#include "scoreboard.h"
#include "sound.h"

Manager::~Manager() { 
  std::list<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    delete (*ptr);
    ++ptr;
  }
  delete hud;
  delete pool;
  delete bulls;
  delete enemyBulls;
  delete player;
  delete enemy;
  delete health;
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  world1("back1", Gamedata::getInstance().getXmlInt("back1/factor") ),
  world2("back2", Gamedata::getInstance().getXmlInt("back2/factor") ),
  world3("back3", Gamedata::getInstance().getXmlInt("back3/factor") ),
  hud(new HUD()),
  pool(new poolHUD()),
  viewport( Viewport::getInstance() ),
  bulls(NULL),
  enemyBulls(NULL),
  player(NULL),
  enemy(NULL),
  health(new Health()),
  sprites(),
  currentSprite(),
  reset(false),
  makeVideo( false ),
  toggleHUD(true),
  togglePoolHUD(true),
  frameCount(0), 
  title( Gamedata::getInstance().getXmlStr("screenTitle") ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") )
 {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  SDL_WM_SetCaption(title.c_str(), NULL);
  atexit(SDL_Quit);
  for(int i=0; i<35; ++i)
  sprites.push_back( new Fire("Fireball", 0.3));
  for(int i=0; i<35; ++i)
  sprites.push_back( new Fire("Fireball", 0.5));
  for(int i=0; i<35; ++i)
  sprites.push_back( new Fire("Fireball", 0.8));

   bulls = new Bullets("Firegust", sprites);
   player = new Player("Dragon", bulls); 
   enemyBulls = new EnemyBullets("EnemyBullet", sprites, player);
   enemy = new Enemy("Enemy", enemyBulls, player);
   bulls->setEnemy(enemy);
  currentSprite = sprites.end();
  currentSprite--;

  viewport.setObjectToTrack(player);
}

void Manager::draw() const {
  world3.draw();
  std::list<Drawable*>::const_iterator ptr = sprites.begin();
 int i=0;
  while ( i<35) {
    (*ptr)->draw();
    ++ptr;
    i++;
  }
  while ( i<70 ) {
    (*ptr)->draw();
    ++ptr;
    i++;
  }
  world1.draw();
  while ( i<105) {
    (*ptr)->draw();
    ++ptr;
    i++;
  }

  enemy->draw();
  enemyBulls->draw();
  player->draw();
  bulls->draw();
  
  world2.draw();

  if(Clock::getInstance().getSeconds()<=(hud->getTime()+2))
  hud->drawHUD(40, 40, screen, toggleHUD);
  pool->drawHUD(800, 50, screen, togglePoolHUD, bulls->getBulletsSize(), bulls->getFreeBulletsSize());
  health->draw();
  if(Scoreboard::getInstance().hasWon())
  io.printMessageCenteredAt("You win!", 150);

  if(Scoreboard::getInstance().hasLost())
  io.printMessageCenteredAt("You Lose!", 150);
  
  io.printMessageCenteredAt(title, 20);
  io.printMessageValueAt("Score: ", Scoreboard::getInstance().getScore(), 870, 20);
  if(player->getGod())
  io.printMessageAt("God Mode: ON ", 720, 20);
  else
  io.printMessageAt("God Mode: OFF ", 720, 20);
  SDL_Flip(screen);
}

void Manager::update() {
  clock.update();
  Uint32 ticks = clock.getTicksSinceLastFrame();
  bulls->update(ticks);
  enemyBulls->update(ticks);

  std::list<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    (*ptr)->update(ticks);
    ++ptr;
  }
  player->update(ticks);
  enemy->update(ticks);

  if ( makeVideo && frameCount<frameMax)
  frameCount = IOManager::getInstance().makeMyFrames();
  std::list<Bullet*> bulletList = bulls->getBullets();
  std::list<Drawable*>::const_iterator ptrx = sprites.begin();
  std::list<Bullet*>::iterator bptr = bulletList.begin();
  while(bptr!=bulletList.end())
  {
   while(ptrx!=sprites.end())
   {
    if((*bptr)->collidedWith(*ptrx))
    static_cast<Fire*>(*ptrx)->explode();
    ++ptrx;
   }
   ++bptr;
  }

  health->update();

  world1.update();
  world2.update();
  world3.update();

  viewport.update(); // always update viewport last
}

void Manager::play() {

  SDL_Event event;
  SDLSound sound;
  bool done = false;
  clock.start();

  while ( not done ) {
    while ( SDL_PollEvent(&event) ) {
      Uint8 *keystate = SDL_GetKeyState(NULL);

      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
          break;
        }
        if (keystate[SDLK_SPACE]) {
         player->shoot();
        }
        if (keystate[SDLK_g]) {
          player->toggleGod();
        }      
        if ( keystate[SDLK_p] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if (keystate[SDLK_a]) {
         player->pressed(1);
        }
        if (keystate[SDLK_s]) {
          player->pressed(2);
        }
        if (keystate[SDLK_d]) {
         player->pressed(3);
        }
        if (keystate[SDLK_w]) {
          player->pressed(4);
        }
        if (keystate[SDLK_a] && keystate[SDLK_w]) {
        player->pressed(8);
        }
        if (keystate[SDLK_a] && keystate[SDLK_s]) {
         player->pressed(7);
        }
        if (keystate[SDLK_s] && keystate[SDLK_d]) {
          player->pressed(6);
        }
        if (keystate[SDLK_w] && keystate[SDLK_d]) {
          player->pressed(5);
        }
        if (keystate[SDLK_a] && keystate[SDLK_d]) {
         player->pressed(0);
        }
        if (keystate[SDLK_w] && keystate[SDLK_s]) {
          player->pressed(0);
        }
	if (keystate[SDLK_F2]) {
          togglePoolHUD=!togglePoolHUD;
        }
	if (keystate[SDLK_r]) {
          reset=true;
          done=true;
          Scoreboard::getInstance().reset();
          Clock::getInstance().reset();
          break;
        }
	if (keystate[SDLK_F1]) {
          if(!toggleHUD)
          toggleHUD=!toggleHUD;
          hud->setTime();
        }
        if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }


      }
      else if((event.type == SDL_KEYUP)||(event.type == SDL_PRESSED)) 
      {
       if (keystate[SDLK_a] && keystate[SDLK_w]) {
          player->pressed(8);
        }
       else  if (keystate[SDLK_a] && keystate[SDLK_s]) {
         player->pressed(7);
        }
       else  if (keystate[SDLK_s] && keystate[SDLK_d]) {
          player->pressed(6);
        }
       else  if (keystate[SDLK_w] && keystate[SDLK_d]) {
         player->pressed(5);
        }
       else if (keystate[SDLK_a]) {
          player->pressed(1);
        }
       else  if (keystate[SDLK_s]) {
          player->pressed(2);
        }
       else  if (keystate[SDLK_d]) {
          player->pressed(3);
        }
       else if (keystate[SDLK_w]) {
          player->pressed(4);
        } 
 
       else  {
          player->pressed(0);
        }   
      }      
    }

    draw();
    update();
  }
}
