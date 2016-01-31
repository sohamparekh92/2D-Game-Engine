#include "enemy.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "scoreboard.h"
#include <cstdlib>
void Enemy::advanceFrame(Uint32 ticks) {
	    if(pressedKey!=0) ticks*=1.5; //Flaps wings faster if moving, slowler if still
            else ticks*=0.75;
            timeSinceLastFrame += ticks;
  if (timeSinceLastFrame > frameInterval ) {
    if(right)
    { 
     currentFrame = (currentFrame+1) % (numberOfFrames/2);
    }
    else
    {
     currentFrame = (currentFrame+1) % (numberOfFrames/2) + (numberOfFrames/2); 
    }
     timeSinceLastFrame = 0;
 }
}

 int Enemy::getSuperRandom()
{
 int number = Gamedata::getInstance().getRandInRange(40,140);
 number *= rand()%2?2:-5;
 number += rand()%2?7:-4;
 return number;
}

Enemy::Enemy( const std::string& name, EnemyBullets* bulls, Player* p):
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")+100),
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  enemy(name),
  player(p),
  originalVelocity(getVelocity()),
  frames(FrameFactory::getInstance().getFrames(name) ),
  explosion(NULL),
  strategy( new PerPixelCollisionStrategy),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  bullets(bulls),
  currentFrame(rand()%Gamedata::getInstance().getXmlInt(name+"/frames") ),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastShoot(0),
  timeSinceLastShift(0),
  timeSinceLastFrame(0),
  ticksSinceLastExplostion(0),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  right(true),
  shift(true),
  up(true),
  exploded(false),
  doNotShoot(false),
  pressedKey(0),
  randomFactor(getSuperRandom()%1000),
  speed(Gamedata::getInstance().getXmlInt(name+"/speed"))
{
  setPosition(player->getPosition() + Vector2f(850 ,0) );
  setVelocity(player->getOriginalVelocity()*0.5);
}

Enemy::~Enemy(){ 
 delete strategy;
}

void Enemy::pressed(int k)
{
 pressedKey = k;
}
void Enemy::shoot()
{
 if(!doNotShoot)
 {
  if(!right)
  bullets->shoot(getPosition()+Vector2f(190,10), -originalVelocity*7);
  else
  bullets->shoot(getPosition()-Vector2f(30,-10), originalVelocity*7);
 }
}

void Enemy::explode()
{
  if(exploded) return;
  exploded = true;
  doNotShoot = true;
  Sprite exp(getName(), getPosition(), originalVelocity*3, getFrame());
  explosion = new ExplodingSprite(exp);
}


void Enemy::draw() const { 
  if(exploded) {
   explosion->draw();
   return;
  }
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
}

void Enemy::update(Uint32 ticks) {

  if(exploded) { 
    ticksSinceLastExplostion += ticks;
    explosion->update(ticks);
    if ( ticksSinceLastExplostion > 3500) {
      delete explosion;
      explosion = NULL;
      exploded = false;
      doNotShoot = false;
      Scoreboard::getInstance().scoreUp(10); 
      ticksSinceLastExplostion = 0;
    }
    return;
  }
  
  if(player->X() - X() > 0)
  right=false;
  else
  right=true;

 if( (right && abs(player->X() - X()) < 550) || (!right && abs(player->X() - X()) < 450) )
  { 
   if(timeSinceLastShoot>400 )
   {
    shoot();
    timeSinceLastShoot = 0;
   }
  else 
    timeSinceLastShoot+=ticks;
  }

  advanceFrame(ticks);
  Vector2f incr;

   timeSinceLastShift += ticks;
   incr = player->getPosition() - getPosition();
   if( (right && abs(player->X() - X()) < 450) || (!right && abs(player->X() - X()) < 350) )
   {
    incr = Vector2f(0, player->Y() - Y());
    if(abs( (player->Y()) - Y()) < 100)
    {
     shift = true;
     timeSinceLastShift = 0;
    }
   }
   if(shift)
   {

    if(up)
    incr = Vector2f(0, -abs(speed) );
    else
    incr = Vector2f(0, abs(speed) );
    if(timeSinceLastShift > 550 || Y() > worldHeight-frameHeight || Y() < 0)
    {
     shift = false;
     up = !up;
    }
   } 
   incr /= 20;
   setPosition(getPosition() + incr);
}

















