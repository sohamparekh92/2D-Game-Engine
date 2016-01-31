#include "enemyBullets.h"
#include "gamedata.h"
#include"ioManager.h"
#include "fire.h"

EnemyBullets::EnemyBullets(const std::string n,  const std::list<Drawable*>& sprites, Player * tr): name(n),
 target(tr),
 targets(sprites), 
 freeList(), 
 bulletList(), 
 ticksSinceLastFrame(0), 
 frameInterval(Gamedata::getInstance().getXmlInt(name+"/frameInterval"))

 {

 }

EnemyBullets::EnemyBullets(const EnemyBullets& b): name(b.name),
 target(b.target),
 targets(b.targets),
 freeList(b.freeList), bulletList(b.bulletList),
 ticksSinceLastFrame(b.ticksSinceLastFrame), 
 frameInterval(b.frameInterval)
 {

 } 

EnemyBullets::~EnemyBullets()
{
   std::list<EnemyBullet*>::iterator ptr = bulletList.begin();
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

void EnemyBullets::shoot(Vector2f position, Vector2f velocity )
{
 if(ticksSinceLastFrame>frameInterval)
 {
  if(freeList.empty())
  {
   EnemyBullet* b = new EnemyBullet(name, position, velocity, targets, target);
   bulletList.push_back(b);
  }
  else
  {
   EnemyBullet* b = freeList.front();
   freeList.pop_front();
   b->reset();
   b->set(position, velocity);
   bulletList.push_back(b);
  }
  ticksSinceLastFrame=0;
 }
}


void EnemyBullets::draw()
{
  std::list<EnemyBullet*>::iterator ptr = bulletList.begin();
  while(ptr!=bulletList.end())
  {
   (*ptr)->draw();
   ++ptr;
 }
}

void EnemyBullets::update(Uint32 ticks)
 {
  ticksSinceLastFrame+= ticks;
  std::list<EnemyBullet*>::iterator ptr = bulletList.begin();
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
