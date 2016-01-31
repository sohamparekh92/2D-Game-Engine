#include <list>
#include <vector>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "HUD.h"
#include "poolHUD.h"
#include "bullets.h"
#include "enemyBullets.h"
#include "player.h"
#include "enemy.h"
#include "health.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();
  bool getRestart() { return reset; }

private:
  const bool env;
  const IOManager& io;
  Clock& clock;

  SDL_Surface * const screen;
  World world1;
  World world2;
  World world3;
  HUD* hud;
  poolHUD * pool;
  Viewport& viewport;
  Bullets* bulls;
  EnemyBullets* enemyBulls;
  Player * player;
  Enemy * enemy;
  Health * health;

  std::list<Drawable*> sprites;
  std::list<Drawable*>::iterator currentSprite;
  bool reset;
  bool makeVideo;
  bool toggleHUD;
  bool togglePoolHUD;
  int frameCount;
  const std::string title;
  const int frameMax;

  void draw() const;
  void update();

  Manager(const Manager&);
  Manager& operator=(const Manager&);

};
