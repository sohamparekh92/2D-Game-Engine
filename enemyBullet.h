#ifndef ENEMYBULLET__H
#define ENEMYBULLET__H
#include <string>
#include <list>
#include "drawable.h"
#include "collisionStrategy.h"
#include "player.h"

class EnemyBullet : public Drawable {
public:
  EnemyBullet(const std::string&, Vector2f position, Vector2f velocity,  const std::list<Drawable*>& sprites, Player * tr);
  virtual ~EnemyBullet() { delete strategy; } 
  EnemyBullet& operator=(const EnemyBullet&);

  virtual const Frame* getFrame() const { return frame; }
  virtual bool collidedWith(const Drawable * obj);
  virtual void set(Vector2f,  Vector2f);  
  virtual void reset();
  virtual bool getFar();
  virtual void draw() const;
  virtual void update(Uint32 ticks);

private:
  EnemyBullet(const EnemyBullet& s);
  const Frame * frame;
  Player * target;
  const std::list<Drawable*>& targets;
  CollisionStrategy* strategy;
  bool tooFar;
  bool lock;
  float ticksSinceLastFrame;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  int getDistance(const EnemyBullet*) const;
  int getSuperRandom();
};
#endif
