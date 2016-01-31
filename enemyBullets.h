#ifndef ENEMYBULLETS_H
#define ENEMYBULLETS_H

#include<iostream>
#include<list>
#include "drawable.h"
#include "vector2f.h"
#include"enemyBullet.h"
#include "player.h"
#include<list>
class EnemyBullets
{
 public:
 EnemyBullets(const std::string n,  const std::list<Drawable*>& targets, Player * tr);
 EnemyBullets(const EnemyBullets&);
~EnemyBullets();
 void shoot(Vector2f position, Vector2f velocity);
 void draw();
 void update(Uint32 ticks);
 std::list<EnemyBullet*>& getBullets() { return bulletList; }
 std::list<EnemyBullet*>& getFreeBullets() { return freeList; }
 unsigned getBulletsSize() { return bulletList.size(); }
 unsigned getFreeBulletsSize() { return freeList.size(); }
 
 private:
 std::string name;
 Player * target;
 const std::list<Drawable*>& targets;
 std::list<EnemyBullet*> freeList;
 std::list<EnemyBullet*> bulletList;

 float ticksSinceLastFrame;
 float frameInterval;

 EnemyBullets& operator=(const EnemyBullets&);
};
#endif
