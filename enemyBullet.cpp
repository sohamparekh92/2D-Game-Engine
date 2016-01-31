#include <cmath>
#include "enemyBullet.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "viewport.h"
#include "sprite.h"
#include "fire.h"
#include "scoreboard.h"

EnemyBullet::EnemyBullet(const string& name, Vector2f position, Vector2f velocity,  
               const std::list<Drawable*>& sprites, Player * tr):
  Drawable(name, position, velocity),
  frame(FrameFactory::getInstance().getFrame(name)),
  target(tr),
  targets(sprites),
  strategy(new PerPixelCollisionStrategy()),
  tooFar(false),
  lock(false),
  ticksSinceLastFrame(0),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{
 Y(Y()+60);
 velocityY(0);
}



EnemyBullet& EnemyBullet::operator=(const EnemyBullet& rhs) {
  Drawable::operator=( rhs );
  frame = rhs.frame;
  strategy = rhs.strategy;
  tooFar = rhs.tooFar;
  lock = rhs.lock;
  ticksSinceLastFrame = rhs.ticksSinceLastFrame;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}

bool EnemyBullet::collidedWith(const Drawable * obj)
{
 Sprite EnemyBullet(getName(), getPosition(), getVelocity(), frame);
 return strategy->execute(EnemyBullet, *obj);
}

void EnemyBullet::set(Vector2f pos, Vector2f vel)
{
  setPosition(pos);
  setVelocity(vel);
  Y(Y()+60);
  velocityY(0);
}
void EnemyBullet::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y); 
}

void EnemyBullet::reset() 
{ 
 tooFar = false; 
 lock = false;
 ticksSinceLastFrame = 0;
}

bool EnemyBullet::getFar() { return tooFar; }

int EnemyBullet::getDistance(const EnemyBullet *obj) const { 
  return hypot(X()-obj->X(), Y()-obj->Y());
}

void EnemyBullet::update(Uint32 ticks) { 

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
  ticksSinceLastFrame += ticks;

  if(ticksSinceLastFrame > 750)
  tooFar = true;  

  if((this)->collidedWith(target) && !lock)
  { 
   target->explode();
   lock = true;
  }
}

























