#ifndef BULLET__H
#define BULLET__H
#include <string>
#include <list>
#include "drawable.h"
#include "collisionStrategy.h"

class Bullet : public Drawable {
public:
  Bullet(const std::string&, Vector2f position, Vector2f velocity,  const std::list<Drawable*>& sprites, Drawable * t);
  virtual ~Bullet() { delete strategy; } 
  Bullet& operator=(const Bullet&);

  virtual const Frame* getFrame() const { return frame; }
  virtual bool collidedWith(const Drawable * obj);
  virtual void set(Vector2f,  Vector2f);  
  virtual void reset();
  virtual bool getFar();
  virtual void draw() const;
  virtual void update(Uint32 ticks);

private:
  Bullet(const Bullet& s);
  const Frame * frame;
  Drawable * target;
  const std::list<Drawable*>& targets;
  CollisionStrategy* strategy;
  bool tooFar;
  float ticksSinceLastFrame;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  int getDistance(const Bullet*) const;
  int getSuperRandom();
};
#endif
