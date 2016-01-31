#include <cmath>
#include "fire.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "SDL/SDL_rotozoom.h"
#include "scoreboard.h"

int Fire::displacementFactor = 0;

 int Fire::getSuperRandom()
{
 int number = Gamedata::getInstance().getRandInRange(40,140);
 number *= rand()%2?2:-5;
 number += rand()%2?7:-4;
 return number;
}

Fire::Fire(const string& n, double factor):
  Drawable(n, 
  Vector2f( Gamedata::getInstance().getXmlInt(n+"/srcX")+getSuperRandom()+getSuperRandom()/2 + displacementFactor,
            Gamedata::getInstance().getXmlInt(n+"/srcY")+getSuperRandom()+getSuperRandom()/2 - Gamedata::getInstance().getXmlInt("world/height")-100),
  Vector2f( Gamedata::getInstance().getXmlInt(n+"/speedX"),//+getSuperRandom()/2,
            Gamedata::getInstance().getXmlInt(n+"/speedY"))//+getSuperRandom()/2)
  ),
  frame( FrameFactory::getInstance().getFrame(n) ),
  scaleFactor(factor),
  scaledSurface(rotozoomSurface(frame->getSurface(), 0, scaleFactor, SMOOTHING_ON)),
  ticksSinceLastExplostion(0),
  exploded(false),
  lock(false),
  explosion(NULL),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ 
 if(displacementFactor>0 || X()<worldWidth )
 displacementFactor += getSuperRandom() + worldWidth/4; 
 velocityY(scaleFactor*velocityY()); //Nearby objects appear to move at a faster rate
 }

Fire::~Fire() {
 SDL_FreeSurface(scaledSurface);
}


Fire& Fire::operator=(const Fire& rhs) {
  Drawable::operator=( rhs );
  frame = rhs.frame;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}

void Fire::explode()
{
 if(exploded) return;
 exploded = true;
 if(!lock)
 {
  Scoreboard::getInstance().increaseHealth();
  Scoreboard::getInstance().scoreUp(5);
  lock = true;
 }
 Sprite exp(getName(), getPosition(), getVelocity()+Vector2f(150,0), getFrame());
 explosion = new ExplodingSprite(exp);
}

void Fire::draw() const { 
  if(exploded) {
   explosion->draw();
   return;
  }
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y, scaledSurface); 
}

int Fire::getDistance(const Fire *obj) const { 
  return hypot(X()-obj->X(), Y()-obj->Y());
}

void Fire::update(Uint32 ticks) { 
   if(exploded) { 
    ticksSinceLastExplostion += ticks;
    explosion->update(ticks);
    if ( ticksSinceLastExplostion > 4000) {
      delete explosion;
      explosion = NULL;
      exploded = false;
      lock = false;
      ticksSinceLastExplostion = 0;
    }
    return;
  }
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
    Y( Y()+worldHeight );
  }
  if ( Y() - frameHeight > worldHeight-frameHeight) {
    Y( Y() - worldHeight );
    if(X()>0 && X()<worldWidth)
    X(X()+getSuperRandom()+getSuperRandom()/2+getSuperRandom()/4+worldWidth/10);
  }

  if ( X() < 0) {
    X( X()+worldWidth );
  }
  if ( X() > worldWidth-frameWidth) {
    X( X() - (worldWidth-frameWidth) );
  }  
}
