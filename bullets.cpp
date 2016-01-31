#include "bullets.h"
#include "gamedata.h"
#include"ioManager.h"
#include "fire.h"

Bullets::Bullets(const std::string n,  const std::list<Drawable*>& sprites): name(n),
 target(NULL),
 targets(sprites), 
 freeList(), 
 bulletList(), 
 ticksSinceLastFrame(0), 
 frameInterval(Gamedata::getInstance().getXmlInt(name+"/frameInterval")) 
 {

 }

Bullets::Bullets(const Bullets& b): name(b.name),
 target(b.target),
 targets(b.targets),
 freeList(b.freeList), bulletList(b.bulletList),
 ticksSinceLastFrame(b.ticksSinceLastFrame), 
 frameInterval(b.frameInterval)
 {

 } 

Bullets::~Bullets()
{
   std::list<Bullet*>::iterator ptr = bulletList.begin();
   while(ptr!=bulletList.end())
   {
    delete (*ptr);
    ++ptr;
   }
   ptr = freeList.begin();
   while(ptr!=freeList.end())
   {
    delete (*ptr);
    ++ptr;
   }
}

void Bullets::shoot(Vector2f position, Vector2f velocity )
{
 if(ticksSinceLastFrame>frameInterval)
 {
  if(freeList.empty())
  {
   Bullet* b = new Bullet(name, position, velocity, targets, target);
   bulletList.push_back(b);
  }
  else
  {
   Bullet* b = freeList.front();
   freeList.pop_front();
   b->reset();
   b->set(position, velocity);
   bulletList.push_back(b);
  }
  ticksSinceLastFrame=0;
 }
}


void Bullets::draw()
{
  std::list<Bullet*>::iterator ptr = bulletList.begin();
  //std::list<Drawable*>::const_iterator ptrx = targets.begin();
  while(ptr!=bulletList.end())
  {
   (*ptr)->draw();
   ++ptr;
 }
}

void Bullets::update(Uint32 ticks)
 {
  ticksSinceLastFrame+= ticks;
  std::list<Bullet*>::iterator ptr = bulletList.begin();
  while(ptr!=bulletList.end())
  {
     (*ptr)->update(ticks);
   if((*ptr)->getFar())
   {
    freeList.push_back(*ptr);
    ptr = bulletList.erase(ptr);
   }
   else ++ptr;
  }

}
