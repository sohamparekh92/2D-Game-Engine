#ifndef BULLETS_H
#define BULLETS_H

#include<iostream>
#include<list>
#include "drawable.h"
#include "vector2f.h"
#include"bullet.h"

#include<list>
class Bullets
{
 public:
 Bullets(const std::string n,  const std::list<Drawable*>& targets);
 Bullets(const Bullets&);
~Bullets();
 void shoot(Vector2f position, Vector2f velocity);
 void setEnemy(Drawable * t) { target = t; }
 void draw();
 void update(Uint32 ticks);
 std::list<Bullet*>& getBullets() { return bulletList; }
 std::list<Bullet*>& getFreeBullets() { return freeList; }
 unsigned getBulletsSize() { return bulletList.size(); }
 unsigned getFreeBulletsSize() { return freeList.size(); }
 
 private:
 std::string name;
 Drawable * target;
 const std::list<Drawable*>& targets;
 std::list<Bullet*> freeList;
 std::list<Bullet*> bulletList;

 float ticksSinceLastFrame;
 float frameInterval;
 Bullets& operator=(const Bullets&);
};
#endif
