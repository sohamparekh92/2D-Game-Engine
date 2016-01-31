#include "player.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "scoreboard.h"
#include "ioManager.h"
//#include "viewport.h"
#include <cstdlib>
void Player::advanceFrame(Uint32 ticks) {
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

 int Player::getSuperRandom()
{
 int number = Gamedata::getInstance().getRandInRange(40,140);
 number *= rand()%2?2:-5;
 number += rand()%2?7:-4;
 return number;
}

Player::Player( const std::string& name, Bullets* bulls):
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")+100),
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  player(name),
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
  timeSinceLastFrame(0),
  ticksSinceLastExplostion(0),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  health(10),
  right(true),
  exploded(false),
  doNotShoot(false),
  god(false),
  pressedKey(0),
  speed(Gamedata::getInstance().getXmlInt(name+"/speed"))
{
  
}

Player::~Player(){ 
 delete strategy;
}

void Player::pressed(int k)
{
 pressedKey = k;
}
void Player::shoot()
{
 if(!doNotShoot)
 {
  if(!right)
  bullets->shoot(getPosition()+Vector2f(275,15), -originalVelocity*7);
  else
  bullets->shoot(getPosition()-Vector2f(20,-15), originalVelocity*7);
 }
}

void Player::explode()
{
 if(!god)
 {
  if(exploded) return;
  Scoreboard::getInstance().decreaseHealth(5);
  if(Scoreboard::getInstance().getHealth()== 0)
  {
   exploded = true;
   doNotShoot = true;
   Sprite exp(getName(), getPosition(), originalVelocity*3, getFrame());
   explosion = new ExplodingSprite(exp);
  }
 }
}


void Player::draw() const { 

  if(exploded) {
   explosion->draw();
   return;
  }
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
}

void Player::update(Uint32 ticks) {

  if(exploded) { 
    ticksSinceLastExplostion += ticks;
    explosion->update(ticks);
    if ( ticksSinceLastExplostion > 4000) {
      delete explosion;
      explosion = NULL;
      exploded = false;
      doNotShoot = false;
      Scoreboard::getInstance().resetHealth();
      ticksSinceLastExplostion = 0;
      Scoreboard::getInstance().lost();
    }
    return;
  }

 //if(Viewport::getInstance().X() >= worldWidth)
 //Scoreboard::getInstance().won();

  advanceFrame(ticks);
   Vector2f incr;
 if(X()>worldWidth-frameWidth)
 {
  velocityX(0);
  X(X()-5);
 }
 else if(Y()>worldHeight-frameHeight)
 {
  velocityY(0);
  Y(Y()-5);
 }
 else if(Y()<0)
 {
  velocityY(0);
  Y(Y()+5);
 }
 else if(X()<0)
 {
  velocityX(0);
  X(X()+5);
 }
 else
 {
  if (pressedKey==1) {
    right = true;//
    velocityX(-speed);
    velocityY(0);
    incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  }
  if (pressedKey==2) {
    velocityX(0);
    velocityY(speed);
    incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  }
  if (pressedKey==3) {
    right = false;
    velocityX(speed);
    velocityY(0);
    incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  }
  if (pressedKey==4) {
    velocityX(0);
    velocityY(-speed);
    incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  }
   if (pressedKey==5) {
    right = false;
    velocityX(speed);
    velocityY(-speed);
    incr = getVelocity() * static_cast<float>(ticks) * 0.001;
    
  }
   if (pressedKey==6) {
    right = false;
    velocityX(speed);
    velocityY(speed);
    incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  }
   if (pressedKey==7) {
    right = true;//
    velocityX(-speed);
    velocityY(speed);
    incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  }
   if (pressedKey==8) {
    right = true;//
   velocityX(-speed);
   velocityY(-speed);
    incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  }
 if (pressedKey==0) {
   velocityX(0);
   velocityY(0);
   incr = getVelocity() * static_cast<float>(ticks) * 0.00;
  }
 }
   setPosition(getPosition() + incr);
}
