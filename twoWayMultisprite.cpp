#include "twoWayMultisprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include <cstdlib>
void TwoWayMultiSprite::advanceFrame(Uint32 ticks) {
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

 int TwoWayMultiSprite::getSuperRandom()
{
 int number = Gamedata::getInstance().getRandInRange(40,140);
 number *= rand()%2?2:-5;
 number += rand()%2?7:-4;
 return number;
}

TwoWayMultiSprite::TwoWayMultiSprite( const std::string& name):
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x")+getSuperRandom()+getSuperRandom()/2, 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")+getSuperRandom()+getSuperRandom()/2), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX")+getSuperRandom()/2,
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  frames(FrameFactory::getInstance().getFrames(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),

  currentFrame(rand()%Gamedata::getInstance().getXmlInt(name+"/frames") ),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  right(true)
{ }

void TwoWayMultiSprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
}

void TwoWayMultiSprite::update(Uint32 ticks) { 
  advanceFrame(ticks);
   Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    right = false;
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
   right = true;
    velocityX( -abs( velocityX() ) );
  }  
}
