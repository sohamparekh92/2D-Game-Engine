#include <cmath>
#include "bullet.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "viewport.h"
#include "sprite.h"
#include "fire.h"
#include "enemy.h"
#include "scoreboard.h"

Bullet::Bullet(const string& name, Vector2f position, Vector2f velocity,  
               const std::list<Drawable*>& sprites, Drawable * t):
  Drawable(name, position, velocity),
  frame(FrameFactory::getInstance().getFrame(name)),
  target(t),
  targets(sprites),
  strategy(new PerPixelCollisionStrategy()),
  tooFar(false),
  ticksSinceLastFrame(0),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{
 Y(Y()+60);
 velocityY(0);
}



Bullet& Bullet::operator=(const Bullet& rhs) {
  Drawable::operator=( rhs );
  frame = rhs.frame;
  strategy = rhs.strategy;
  tooFar = rhs.tooFar;
  ticksSinceLastFrame = rhs.ticksSinceLastFrame;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}

bool Bullet::collidedWith(const Drawable * obj)
{
 Sprite bullet(getName(), getPosition(), getVelocity(), frame);
 return strategy->execute(bullet, *obj);
}

void Bullet::set(Vector2f pos, Vector2f vel)
{
  setPosition(pos);
  setVelocity(vel);
  Y(Y()+60);
  velocityY(0);
}
void Bullet::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y); 
}

void Bullet::reset() 
{ 
 tooFar = false; 
 ticksSinceLastFrame = 0;
}

bool Bullet::getFar() { return tooFar; }

int Bullet::getDistance(const Bullet *obj) const { 
  return hypot(X()-obj->X(), Y()-obj->Y());
}

void Bullet::update(Uint32 ticks) { 

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
  ticksSinceLastFrame += ticks;
  if(ticksSinceLastFrame > 750)
  tooFar = true;  

  std::list<Drawable*>::const_iterator ptr = targets.begin();
  while(ptr!=targets.end())
  {
   if((this)->collidedWith(target)) 
   {
    static_cast<Enemy*>(target)->explode();   
   }
   if((this)->collidedWith(*ptr)) 
   {
    static_cast<Fire*>(*ptr)->explode();
   }
   ++ptr;
  }
}

























